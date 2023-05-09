/*
    active == true -> list active bots
    active == false -> list all registered bots
*/
#include "utils.h"

sem_t r, w;
int readcount = 0, ret = 0;

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
        if(bot->bot_id == 0){
            bot = bot->next;
            continue;
        }
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

    while (bot->next != NULL)
    {
        bot = bot->next;
    }

    bot->next = (active_bots *)malloc(sizeof(active_bots));

    ret = inet_pton(AF_INET, bot_ip, &(bot->next->bot_address));
    if (ret == 0)
    {
        handle_error("Could not parse bot_ip to in_addr");
        res = -1;
    }

    bot->next->bot_id = bot->bot_id + 1;
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

            *bot_port = bot->port;
            inet_ntop(AF_INET, &(bot->bot_address), bot_ip, INET_ADDRSTRLEN);

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

void updateBotInfo(int bot_id, const char *target_ip, const char *command)
{
    int ret = sem_wait(&w);
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }

    active_bots *bot = botnet;

    while (bot != NULL)
    {
        if (bot->bot_id == bot_id)
        {

            if (strcmp(target_ip, "void") == 0)
            {
                ret = inet_pton(AF_INET, "0.0.0.0", &(bot->target_address));
            }
            else
            {

                ret = inet_pton(AF_INET, target_ip, &(bot->target_address));
            }

            if (ret == 0)
            {
                printf("Not a valid address\n");
                break;
            }

            if (strcmp(command, "void") == 0)
            {

                strcpy(bot->action, "\0");
            }
            else
            {

                strcpy(bot->action, command);
            }

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

void getBotID(const char *bot_ip, const char *bot_port, int * bot_id)
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

    active_bots *bot = botnet;

    *bot_id = -1;
    while (bot != NULL)
    {
        
        char ip[INET_ADDRSTRLEN] = {0};
        char port[6] = {0};

        inet_ntop(AF_INET, &(bot->bot_address), ip, INET_ADDRSTRLEN);
        snprintf(port, sizeof(port), "%ld", bot->port);

        if (strcmp(ip, bot_ip) == 0 && strcmp(port, bot_port) == 0)
        {

            *bot_id = bot->bot_id;
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

}

int fromHostnameToIp(char *target_ip, char *hostname)
{

    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(hostname)) == NULL)
    {
        // get the host info
        printf("\nNot valid hostname");
        return -1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    inet_ntop(AF_INET, addr_list[0], target_ip, INET_ADDRSTRLEN);
    printf("\n Target ip : %s \n", target_ip);

    return 1;
}

void getTargetIp(char *target_ip)
{
    printf("\n Do you want insert target.s ip by hostname? [Y,n]\n");
    char byHostName[3] = {0};
    fgets(byHostName, sizeof(char) * 3, stdin);
    fflush(stdin);

    if (strcmp(byHostName, "n\n") == 0)
    {
        printf("\nSubmit target's ip in dot decimal notation:");
        fgets(target_ip, sizeof(target_ip), stdin);
        fflush(stdin);
    }
    else
    {
        printf("\nSubmit target's hostname: ");
        char hostname[255] = {0};
        fflush(stdin);
        fgets(hostname, sizeof(char) * 255, stdin);
        hostname[strcspn(hostname, "\n")] = 0;
        if (fromHostnameToIp(target_ip, hostname) < 0)
        {
            printf("Could not send command, wrong hostname");
            return;
        }
    }

    target_ip[strcspn(target_ip, "")] = 0;
}