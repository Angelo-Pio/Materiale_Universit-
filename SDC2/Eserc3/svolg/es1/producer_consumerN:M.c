#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // nanosleep()
#include "common.h"

#define BUFFER_SIZE         128
#define INITIAL_DEPOSIT     0
#define MAX_TRANSACTION     1000
#define NUM_CONSUMERS       12
#define NUM_PRODUCERS       6
#define PRNG_SEED           0

#define NUM_OPERATIONS      400
#define OPS_PER_CONSUMER    (NUM_OPERATIONS/NUM_CONSUMERS)
#define OPS_PER_PRODUCER    (NUM_OPERATIONS/NUM_PRODUCERS)

// we use the preprocessor to check if our parameters are okay
#if OPS_PER_CONSUMER*NUM_CONSUMERS != OPS_PER_PRODUCER*NUM_PRODUCERS
#error "Choose NUM_CONSUMERS and NUM_PRODUCERS so that we get exactly NUM_OPERATIONS operations"
#endif

// struct used to specify arguments for a thread
typedef struct {
    int threadId;
    int numOps;
} thread_args_t;

// shared data
int transactions[BUFFER_SIZE];
int deposit = INITIAL_DEPOSIT;
int read_index, write_index;
sem_t e,s,n,c ;

// generates a number between -MAX_TRANSACTION and +MAX_TRANSACTION
static inline int performRandomTransaction() {
    return 1;
}

// producer thread
void* performTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting producer thread %d\n", args->threadId);


    while (args->numOps > 0) {
        // produce the item
        if(sem_wait(&e) == -1) handle_error("Error in producer, wait sem e");
        if(sem_wait(&s) == -1) handle_error("Error in producer, wait sem s");

        int currentTransaction = performRandomTransaction();
        // write the item and update write_index accordingly
        transactions[write_index] = currentTransaction;
        write_index = (write_index + 1) % BUFFER_SIZE;
        
        if(sem_post(&s) == -1) handle_error("Error in producer, wait sem s");
        if(sem_post(&n) == -1) handle_error("Error in producer, post sem n");
        args->numOps--;

        //printf("P %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

// Consumer
void* processTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting consumer thread %d\n", args->threadId);

    while (args->numOps > 0) {

        if(sem_wait(&n) == -1) handle_error("Error in producer, wait sem n");
        if(sem_wait(&c) == -1) handle_error("Error in producer, wait sem c");

        // consume the item and update (shared) variable deposit
        deposit += transactions[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
        
        if (read_index % 100 == 0)
			printf("After the last 100 transactions balance is now %d.\n", deposit);
        
        if(sem_post(&c) == -1) handle_error("Error in producer, post sem c");
        if(sem_post(&e) == -1) handle_error("Error in producer, post sem e");

        args->numOps--;
        //printf("C %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    printf("Welcome! This program simulates financial transactions on a deposit.\n");
    printf("\nThe maximum amount of a single transaction is %d (negative or positive).\n", MAX_TRANSACTION);
    printf("\nInitial balance is %d. Press CTRL+C to quit.\n\n", INITIAL_DEPOSIT);

    // initialize read and write indexes
    read_index  = 0;
    write_index = 0;

    if(sem_init(&s,0,1) == -1){
        handle_error("Errore init sem s");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&e,0,BUFFER_SIZE) == -1){
        handle_error("Errore init sem e");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&n,0,0) == -1){
        handle_error("Errore init sem n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&c,0,1) == -1){
        handle_error("Errore init sem s");
        exit(EXIT_FAILURE);
    }
    



    // set seed for pseudo-random number generator: we use this to make
    // this code yield the same result across different runs, as long
    // as they are race-free and you make no mistakes :-)
    srand(PRNG_SEED);

    int ret;
    pthread_t producer[NUM_PRODUCERS], consumer[NUM_CONSUMERS];

    int i;
    for (i=0; i<NUM_PRODUCERS; ++i) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = i;
        arg->numOps = OPS_PER_PRODUCER;

        ret = pthread_create(&producer[i], NULL, performTransactions, arg);
        if (ret != 0)  handle_error_en(ret,"Error in pthread create (producer)");
    }

    int j;
    for (j=0; j<NUM_CONSUMERS; ++j) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = j;
        arg->numOps = OPS_PER_CONSUMER;

        ret = pthread_create(&consumer[j], NULL, processTransactions, arg);
        if (ret != 0) handle_error_en(ret,"Error in pthread create (consumer)");
    }

    // join on threads
    for (i=0; i<NUM_PRODUCERS; ++i) {
        ret = pthread_join(producer[i], NULL);
        if (ret != 0) handle_error_en(ret,"Error in pthread join (producer)");
    }

    for (j=0; j<NUM_CONSUMERS; ++j) {
        ret = pthread_join(consumer[j], NULL);
        if (ret != 0) handle_error_en(ret,"Error in pthread join (consumer)");
    }

    printf("Final value for deposit: %d\n", deposit);

    if(sem_destroy(&s)) handle_error("Error destroy sem s");
    if(sem_destroy(&n)) handle_error("Error destroy sem n");
    if(sem_destroy(&e)) handle_error("Error destroy sem e");
    if(sem_destroy(&c)) handle_error("Error destroy sem c");

    exit(EXIT_SUCCESS);
}
