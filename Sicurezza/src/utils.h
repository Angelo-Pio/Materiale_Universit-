#ifndef UTILS_H
#define UTILS_H

#include "common.h"

int list_botnet(int active);
int botExists(int bot_id);
int initializeSemaphores();
int closeSemaphores();
int registerBot(const char *bot_ip, const char *bot_port);
int findBot(struct in_addr, long port);
int setBotInfo(long *bot_port, char *bot_ip, int bot_id);
void updateBotInfo(int bot_id, const char *target_ip,const  char *command);
int fromHostnameToIp(char * target_ip, char * hostname);
void getTargetIp(char * target_ip);
void getBotID(const char * bot_ip, const char * bot_port, int * bot_id);
#endif