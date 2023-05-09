#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
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
#include <semaphore.h>
#include<netdb.h>	//hostent
#include <signal.h>
#include <curl/curl.h>
#include <microhttpd.h>
#include <pthread.h>

// macros for handling errors
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(-1);                \
    } while (0)
#define handle_error(msg) \
    do                    \
    {                     \
        perror(msg);      \
        exit(-1);         \
    } while (0)

/* Configuration parameters */
#define DEBUG 0          // display debug messages
#define MAX_CONN_QUEUE 5 // max number of connections the server can queue
#define QUIT "QUIT\n"
#define SERVER_PORT 8888
#define LIST "list\n"
#define SELF "self"
#define SYS_INFO "sys_info\n"
#define HTTP_REQ "http_req\n"
#define C_PORT "PORT"
#define C_IP "IP"
#define PROTOCOL "http://"
#define MAX_REQ_SIZE 1000
#define HTTP_REQ_ENDPOINT "/http_req?request="
#define SHM_NAME "/botnet"


typedef struct bot
{
    int bot_id;
    long port;
    struct in_addr bot_address; // in_addr ?
    // If these two fields are not null the bot is active else not
    struct in_addr target_address;
    char action[10];
    struct bot *next;
} active_bots;

extern active_bots *botnet;
extern sem_t r, w;
extern int readcount, ret;
extern struct MHD_Daemon *mhd_daemon;






#endif
