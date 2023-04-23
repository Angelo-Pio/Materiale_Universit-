#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <semaphore.h>

int initializeSemaphores();
int closeSemaphores();
int concurrentWRDecorator(int (*function)(int), int readcount, sem_t *r, sem_t *w);

#endif