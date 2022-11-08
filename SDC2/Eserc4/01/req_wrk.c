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
sem_t* sem_wrk;
sem_t* sem_seq;



/*
TODO COMPLETE THE FOLLOWING CODE BLOCK
*
* Add any needed resource 
**/

int request() {
  /*
  TODO COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  
  data = (int*) mmap(0,SIZE,PROT_READ | PROT_WRITE ,MAP_SHARED,fd,0);
  
  
  // if(sem_wait(sem_seq) == -1) {handle_error("Error in waiting sem_wrk in request");}

  printf("request: mapped address: %p\n", data);

  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = i;
  }
  printf("request: data generated\n");

   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the worker that it can start the elaboration
    * and wait it has terminated
    **/
  if(sem_post(sem_wrk) == -1) {handle_error("Error in post sem_seq in request");}
  if(sem_wait(sem_seq) == -1) {handle_error("Error in waiting sem_wrk in request");}

  printf("request: acquire updated data\n");

  printf("request: updated data:\n");
  for (i = 0; i < NUM; ++i) {
    printf("%d\n", data[i]);
  }

   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Release resources
    **/

   if(munmap(data,SIZE) == -1) {handle_error("Error in unmapping shared memory");};


  return EXIT_SUCCESS;
}

int work() {


  /*
  TODO COMPLETE THE FOLLOWING CODE BLOCK
  *
  * map the shared memory in the data array
  **/
  data = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,fd,0);

  printf("worker: mapped address: %p\n", data);

   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Wait that the request() process generated data
    **/

   if(sem_wait(sem_wrk) == -1) {handle_error("Error in waiting sem_wrk in worker");}

  printf("worker: waiting initial data\n");

  printf("worker: initial data acquired\n");

  printf("worker: update data\n");
  int i;
  for (i = 0; i < NUM; ++i) {
    data[i] = data[i] * data[i];
  }

  printf("worker: release updated data\n");

   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Signal the requester that elaboration terminated
    **/
   if(sem_post(sem_seq) == -1) {handle_error("Error in post sem_seq in worker");}



  /*
  TODO COMPLETE THE FOLLOWING CODE BLOCK
   *
   * Release resources
   **/

  if(munmap(data,SIZE) == -1) {handle_error("Error in unmapping shared memory");};
 

  return EXIT_SUCCESS;
}



int main(int argc, char **argv){

   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Create and open the needed resources 
    **/


  if (sem_unlink(SEM_NAME_WRK) == -1) {handle_error("Error in destroing sem_wrk");}
  if (sem_unlink(SEM_NAME_REQ) == -1) {handle_error("Error in destroing sem_seq");}

   
    int ret;

    sem_wrk = sem_open(SEM_NAME_WRK,O_CREAT | O_EXCL,0600,0);
    if( sem_wrk == SEM_FAILED ) { handle_error("Error in sem_wrk initialisation"); }
    
    sem_seq = sem_open(SEM_NAME_REQ,O_CREAT | O_EXCL,0600,0) ;
    if( sem_seq == SEM_FAILED) { handle_error("Error in sem_seq initialisation"); }

  //  Unlink prima della creazione
    shm_unlink(SHM_NAME);

    fd = shm_open(SHM_NAME,O_CREAT | O_EXCL | O_RDWR,0600);
    if(fd == 1){
      handle_error("Error in shared memory initialisation");
    }
    if(ftruncate(fd,SIZE) == -1){handle_error("Error in shared memory truncation");  }



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


   /*
   TODO COMPLETE THE FOLLOWING CODE BLOCK
    *
    * Close and release resources
    **/
   sem_close(sem_wrk);
   sem_close(sem_seq);
  if (close(fd)) {handle_error("Error in destroing sem_wrk");}

    _exit(EXIT_SUCCESS);

}
