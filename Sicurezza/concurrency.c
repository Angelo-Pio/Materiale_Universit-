
#include "common.h"

int initializeSemaphores(sem_t *r, sem_t *w)
{

    int ret;

    ret = sem_init(r, 1, 1);
    if (ret < 0)
    {
        handle_error("Failed to initialize sem r");
        return -1;
    }

    ret = sem_init(w, 1, 1);
    if (ret < 0)
    {
        handle_error("Failed to initialize sem w");
        return -1;
    }

    return 0;
}

int closeSemaphores(sem_t *r, sem_t *w)
{

    int ret;

    ret = sem_close(r);
    if (ret < 0)
    {
        handle_error("Failed to close sem r");
        return -1;
    }

    ret = sem_close(w);
    if (ret < 0)
    {
        handle_error("Failed to close sem w");
        return -1;
    }

    return 0;
}

int concurrentWRDecorator(int (*fun)(), int readcount, sem_t *r, sem_t *w)
{

    int ret = sem_wait(r), val;
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }

    readcount++;

    if (readcount == 1)
    {

        ret = sem_wait(w);
        if (ret < 0)
        {
            handle_error("Error in wait sem w");
        }
    }

    ret = sem_post(r);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }

    val = fun();

    ret = sem_wait(r);
    if (ret < 0)
    {
        handle_error("Error in wait sem w");
    }
    readcount--;
    if (readcount == 0)
        ret = sem_post(w);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }
    ret = sem_post(r);
    if (ret < 0)
    {
        handle_error("Error in post sem w");
    }

    return val;
}