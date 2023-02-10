#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>


// data array
int * data;
int fd;
sem_t * worker , * requester;

/** COMPLETE THE FOLLOWING CODE BLOCK
*
* Add any needed resource 
**/

int request() {
  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  
  if( data = (int*) mmap(0,SIZE,PROT_READ | PROT_WRITE ,MAP_SHARED,fd,0) == MAP_FAILED) handle_error("Error mapping file descriptor");


  printf("request: mapped address: %p\n", data);

  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = i;
  }
  printf("request: data generated\n");

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the worker that it can start the elaboration
    * and wait it has terminated
    **/

   sem_post(worker);
   printf("request: acquire updated data\n");


   sem_wait(requester);
  printf("request: updated data:\n");
  for (i = 0; i < NUM; ++i) {
    printf("%d\n", data[i]);
  }

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/

  //  sem_close(SEM_NAME_REQ);
  //  sem_close(SEM_NAME_WRK);
   munmap(SHM_NAME,SIZE);

  return EXIT_SUCCESS;
}

int work() {

  /** COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  if( data = (int*) mmap(0,SIZE,PROT_READ | PROT_WRITE ,MAP_SHARED,fd,0) == MAP_FAILED) handle_error("Error mapping file descriptor");
  printf("worker: mapped address: %p\n", data);

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Wait that the request() process generated data
    **/
   sem_wait(worker);
  printf("worker: waiting initial data\n");

  printf("worker: initial data acquired\n");

  printf("worker: update data\n");
  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = data[i] * data[i];
  }

  printf("worker: release updated data\n");

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the requester that elaboration terminated
    **/
   sem_post(requester);

  /** COMPLETE THE FOLLOWING CODE BLOCK
   *
   * Release resources
   **/

  // sem_close(SEM_NAME_REQ);
  //  sem_close(SEM_NAME_WRK);
   munmap(SHM_NAME,SIZE);

  return EXIT_SUCCESS;
}



int main(int argc, char **argv){

   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Create and open the needed resources 
    **/


     if(shm_unlink(SHM_NAME) == -1) handle_error("Error unlinking shared memory");

     if(fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR,0666) == -1 ) handle_error("Error opening shared memory") ;

     if(ftruncate(fd,SIZE) == -1) handle_error("Error truncating");


      if(sem_unlink(SEM_NAME_REQ)==-1) handle_error("Error unlinking sem name req");
      if(sem_unlink(SEM_NAME_WRK)==-1) handle_error("Error unlinking sem name wrk");

      requester = sem_open(SEM_NAME_REQ,0);
      if( requester == SEM_FAILED) {
        handle_error("Error opening sem req");
        exit(EXIT_FAILURE);
      }
      if(worker = sem_open(SEM_NAME_WRK,0) == SEM_FAILED) {
        handle_error("Error opening sem wrk");
        exit(EXIT_FAILURE);
      }
    //  if( data = (int*) mmap(0,SIZE,O_RDWR,MAP_SHARED,fd,0) == MAP_FAILED) handle_error("Error mapping file descriptor");


    int ret;
    pid_t pid = fork();
    if (pid == -1) {
        handle_error("main: fork");
    } else if (pid == 0) {
        work();
        _exit(EXIT_SUCCESS);
    }

    request();
    int status;
    ret = wait(&status);
    if (ret == -1)
      handle_error("main: wait");
    if (WEXITSTATUS(status)) handle_error_en(WEXITSTATUS(status), "request() crashed");


   /** COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Close and release resources
    **/

     sem_close(requester);
     sem_close(worker);
     sem_unlink(SEM_NAME_REQ);
     sem_unlink(SEM_NAME_WRK);
      close(fd);
     if(shm_unlink(SHM_NAME) == -1) handle_error("Error unlinking shared memory");


    _exit(EXIT_SUCCESS);

}
