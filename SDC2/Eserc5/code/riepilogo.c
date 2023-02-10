#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

// macros for error handling
#include "common.h"

#define N 100 // child process count
#define M 10  // thread per child process count
#define T 3   // time to sleep for main process
#define SEM1 "/sem1"
#define SEM2 "/sem2"
#define SHM_NAME "/shm"
#define SIZE N *M
#define FILENAME "accesses.log"

/*
 * data structure required by threads
 */
typedef struct thread_args_s
{
    unsigned int child_id;
    unsigned int thread_id;
} thread_args_t;

/*
 * parameters can be set also via command-line arguments
 */
int n = N, m = M, t = T;

/* TODO: declare as many semaphores as needed to implement
 * the intended semantics, and choose unique identifiers for
 * them (e.g., "/mysem_critical_section") */

/* TODO: declare a shared memory and the data type to be placed
 * in the shared memory, and choose a unique identifier for
 * the memory (e.g., "/myshm")
 * Declare any global variable (file descriptor, memory
 * pointers, etc.) needed for its management
 */
int *data;
int fd;
sem_t *s , *n;

/*
 * Ensures that an empty file with given name exists.
 */
void init_file(const char *filename)
{
    printf("[Main] Initializing file %s...", FILENAME);
    fflush(stdout);
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
        handle_error("error while initializing file");
    close(fd);
    printf("closed...file correctly initialized!!!\n");
}

/*
 * Create a named semaphore with a given name, mode and initial value.
 * Also, tries to remove any pre-existing semaphore with the same name.
 */
sem_t *create_named_semaphore(const char *name, mode_t mode, unsigned int value)
{
    printf("[Main] Creating named semaphore %s...", name);
    fflush(stdout);

    // TODO
    if (sem_unlink(SEM1) == -1)
        handle_error("Error unlinking sem1");

    s = sem_open(SEM1, O_CREAT | O_EXCL, 0666, 1);
    if (s == SEM_FAILED)
        handle_error("Error creating semaphore s");

    printf("done!!!\n");
    return NULL;
}

void parseOutput()
{
    // identify the child that accessed the file most times
    int *access_stats = calloc(n, sizeof(int)); // initialized with zeros
    printf("[Main] Opening file %s in read-only mode...", FILENAME);
    fflush(stdout);
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0)
        handle_error("error while opening output file");
    printf("ok, reading it and updating access stats...");
    fflush(stdout);

    size_t read_bytes;
    int index;
    do
    {
        read_bytes = read(fd, &index, sizeof(int));
        if (read_bytes > 0)
            access_stats[index]++;
    } while (read_bytes > 0);
    printf("ok, closing it...");
    fflush(stdout);

    close(fd);
    printf("closed!!!\n");

    int max_child_id = -1, max_accesses = -1;
    for (int i = 0; i < n; i++)
    {
        printf("[Main] Child %d accessed file %s %d times\n", i, FILENAME, access_stats[i]);
        if (access_stats[i] > max_accesses)
        {
            max_accesses = access_stats[i];
            max_child_id = i;
        }
    }
    printf("[Main] ===> The process that accessed the file most often is %d (%d accesses)\n", max_child_id, max_accesses);
    free(access_stats);
}

void *thread_function(void *x)
{
    thread_args_t *args = (thread_args_t *)x;

    /* TODO: protect the critical section using semaphore(s) as needed */

    if (sem_wait(s) == -1)
        handle_error("Error wait sem");
    // open file, write child identity and close file
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd < 0)
        handle_error("error while opening file");
    printf("[Child#%d-Thread#%d] File %s opened in append mode!!!\n", args->child_id, args->thread_id, FILENAME);

    write(fd, &(args->child_id), sizeof(int));
    printf("[Child#%d-Thread#%d] %d appended to file %s opened in append mode!!!\n", args->child_id, args->thread_id, args->child_id, FILENAME);

    close(fd);
    printf("[Child#%d-Thread#%d] File %s closed!!!\n", args->child_id, args->thread_id, FILENAME);

    if (sem_post(s) == -1)
        handle_error("Error post s1em");

    free(x);
    pthread_exit(NULL);
}

void mainProcess()
{
    /* TODO: 
     * the main process waits for all the children to start,
     * it notifies them to start their activities, and sleeps
     * for some time t. Once it wakes up, it notifies the children
     * to end their activities, and waits for their termination.
     * Finally, it calls the parseOutput() method and releases
     * any shared resources. */

    sem_post


}

void childProcess(int child_id)
{
    /* TODO:
     * each child process notifies the main process that it
     * is ready, then waits to be notified from the main in order
     * to start. As long as the main process does not notify a
     * termination event [hint: use sem_getvalue() here], the child
     * process repeatedly creates m threads that execute function
     * thread_function() and waits for their completion. When a
     * notification has arrived, the child process notifies the main
     * process that it is about to terminate, and releases any
     * shared resources before exiting. */
    data = (int *)mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    
    if(sem_post(n) == -1) handle_error("Error sem post sem n");
    if(sem_wait(n) == -1) handle_error("Error sem post sem n");

    
        int *value;
    sem_getvalue(n, value);
    while (*value)
    {
        pthread_t *threads[M];
        for (int i = 0; i < M; i++)
        {
            if (pthread_create(threads[i], NULL, thread_function, NULL) != 0)
                handle_error("Error creating thread");
        }

        for (int j = 0; j < M; j++)
        {
            if (pthread_join(threads[j], NULL) != 0)
                handle_error("error in join threads");
        }
    }

    print("Child[%d] is about to terminate... releasing resources", child_id);
    if (munmap(data, SIZE) == -1) handle_error("Error unmapping");
}

int main(int argc, char **argv)
{
    // arguments
    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        m = atoi(argv[2]);
    if (argc > 3)
        t = atoi(argv[3]);

    // initialize the file
    init_file(FILENAME);
    if (shm_unlink(SHM_NAME) == -1)
        handle_error("Error unlinking shared memory");
    fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1)
        handle_error("Errore opening shared memory");
    if (ftruncate(fd, SIZE) == -1)
        handle_error("errore truncating shared memory");

    s = create_named_semaphore(SEM1,0666,1);
    n = create_named_semaphore(SEM2,0666,1);
        
    // memset
    data = (int *)mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    /* TODO: initialize any semaphore needed in the implementation, and
     * create N children where the i-th child calls childProcess(i);
     * initialize the shared memory (create it, set its size and map it in the
     * memory), then the main process executes function mainProcess() once
     * all the children have been created */
    for (int i = 0; i < N; i++)
    {
        int pid = fork();
        if (pid == -1)
        {
            handle_error("Error fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            childProcess(getpid());
            _exit(EXIT_SUCCESS);
        }
    }
    mainProcess();

    exit(EXIT_SUCCESS);
}