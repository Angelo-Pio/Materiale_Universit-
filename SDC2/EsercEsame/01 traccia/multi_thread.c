#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 5
#define THREAD_COUNT 4
#define ITERATION_COUNT 10
#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    int idx;
    int role;
} thread_args_t;

int buffer[BUFFER_LENGTH];
int write_index, read_index;

/**
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */


/***/

sem_t e ,s1, s2, n ;

void producer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {
        int value = idx*ITERATION_COUNT + i;

        ret = sem_wait(&e);
        if(ret < 0) handle_error("error waiting for sem e");

        ret = sem_wait(&s1);
        if(ret < 0) handle_error("error waiting for sem s1");

        buffer[write_index] = value;
        write_index = (write_index + 1) % BUFFER_LENGTH;

        ret = sem_post(&s1);
        if(ret < 0) handle_error("error post for sem s1");

        ret = sem_post(&n);
        if(ret < 0) handle_error("error post for sem n");

        printf("[Thread #%d] inserito %d nel buffer\n", idx, value);
     }
}

void consumer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {

        ret = sem_wait(&n);
        if(ret < 0) handle_error("error waiting for sem n");

        ret = sem_wait(&s2);
        if(ret < 0) handle_error("error waiting for sem s2");

        int value = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_LENGTH;

         ret = sem_post(&s2);
        if(ret < 0) handle_error("error post for sem s2");

        ret = sem_post(&e);
        if(ret < 0) handle_error("error post for sem e");


        printf("[Thread #%d] letto %d dal buffer\n", idx, value);
     }
}


void *thread_routine(void *args) {

    thread_args_t *thread_args = (thread_args_t*)args;
    if (thread_args->role == PROD_ROLE) {
        producer_routine(thread_args->idx);
    } else if (thread_args->role == CONS_ROLE) {
        consumer_routine(thread_args->idx);
    } else {
        printf("[Thread #%d] ruolo sconosciuto: %d\n", thread_args->idx, thread_args->role);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    int ret;

    // inizializzazioni
    read_index = write_index = 0;

    /**
     * COMPLETARE QUI
     *
     * Obiettivi
     * - inizializzare i semafori dichiarati
     * - gestire gli errori
     */

    /***/


    ret = sem_init(&e,0,BUFFER_LENGTH);
    if(ret < 0) handle_error("Error init semaphore e");

    ret = sem_init(&s1,0,THREAD_COUNT/2);
    if(ret < 0) handle_error("Error init semaphore s1");

    ret = sem_init(&s2,0,THREAD_COUNT/2);
    if(ret < 0) handle_error("Error init semaphore s2");

    ret = sem_init(&n,0,0);
    if(ret < 0) handle_error("Error init semaphore n");

    puts("HERE");

    /**
     * COMPLETARE QUI
     *
     * Obiettivi: creazione thread
     * - ogni thread deve invocare la funzione thread_routine()
     * - gli argomenti per il thread devono essere specificati
     *   all'interno di una struttura thread_args_t
     * - il campo role può assumere come valori PROD_ROLE o CONS_ROLE
     * - ogni thread ha un valore di idx diverso tra 0 e THREAD_COUNT-1
     * - ci dovranno essere THREAD_COUNT/2 thread con ruolo produttore
     *   ed altrettanti con ruolo consumatore (THREAD_COUNT è pari)
     * - gestire glie errori
     * - N.B.: si tenga presente che successivamente il programma
     *   dovrà attendere la terminazione di ogni thread
     * 
     */
    puts("HERE");
    pthread_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread_args_t* thread_args = (thread_args_t *) malloc(sizeof(thread_args_t));
        thread_args->idx = i;
        if(i >= THREAD_COUNT/2){

            thread_args->role = PROD_ROLE;
        }else{
            thread_args->role = CONS_ROLE;
        }

        ret = pthread_create(&threads[i],0,thread_routine,thread_args);
        if(ret != 0) handle_error("Error in creating threads");
    }

    


    /***/


    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - attendere la terminazione dei thread lanciati in precedenza
     * - gestire gli errori
     */

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        ret = pthread_join(threads[i],NULL);
        if(ret != 0) handle_error("Error in joining threads");
    }
    
   
    


    


    /***/

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - rilasciare i semafori inizializzati in precedenza
     * - gestire gli errori
     */


    /***/

    ret = sem_destroy(&e);
    if(ret < 0) handle_error("Error destroying sem e ");

    ret = sem_destroy(&s1);
    if(ret < 0) handle_error("Error destroying sem s1");

    ret = sem_destroy(&s2);
    if(ret < 0) handle_error("Error destroying sem s2 ");

    ret = sem_destroy(&n);
    if(ret < 0) handle_error("Error destroying sem n ");
  

    printf("[Main Thread] operazioni completate\n");

    return EXIT_SUCCESS;
}
