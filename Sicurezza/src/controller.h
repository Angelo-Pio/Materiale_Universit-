#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"
#include "utils.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/utsname.h>

void sendCommand(char *command, int bot_id,char * target_ip);
void broadcastCommand(char *command, char* target_ip);
void parent(/*int pid*/);
void child();
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls);



#endif