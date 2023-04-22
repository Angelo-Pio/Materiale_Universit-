#ifndef COMMON_H
#define COMMON_H

// macros for handling errors
#define handle_error_en(en, msg)    do { errno = en; perror(msg); exit(-1); } while (0)
#define handle_error(msg)           do { perror(msg); exit(-1); } while (0)

/* Configuration parameters */
#define DEBUG           1   // display debug messages
#define MAX_CONN_QUEUE  3   // max number of connections the server can queue
#define SERVER_ADDRESS  "127.0.0.1"
#define SERVER_COMMAND  "QUIT\n"
#define SERVER_PORT     2015
#define LIST     "list"
#define EMAIL     "email"
#define SYS_INFO     "sys_info"
#define HTTP_REQ     "http_req"
#endif
