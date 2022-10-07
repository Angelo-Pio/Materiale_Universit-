#include "performance.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

void do_work() {
	return;
}

void* thread_fun(void *arg) {
	do_work();
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Syntax: %s <N>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// parse N from the command line
	int n = atoi(argv[1]);

	// thread reactivity
	printf("Thread reactivity, %d tests...\n", n);
	unsigned long sum = 0;
	timer t;
	int i, ret;

	begin(&t);
	pthread_t* threads = malloc(n* sizeof(pthread_t));
	for (i = 0; i < n; i++) {
		ret = pthread_create(&threads[i], NULL, thread_fun, NULL);
		if (ret != 0) {
			fprintf(stderr, "Can't create a new thread, error %d\n", ret);
			exit(EXIT_FAILURE);
		}
	}
	for (int j = 0; j < n; j++)
	{
		ret = pthread_join(threads[j], NULL);
		if (ret != 0) {
			fprintf(stderr, "Cannot join on thread, error %d\n", ret);
			exit(EXIT_FAILURE);
		}
			
	}
	
	end(&t);
	sum += get_microseconds(&t);
	
	// compute statistics
	unsigned long thread_avg = sum / n;
	printf("Average: %lu microseconds\n", thread_avg);

	free(threads);
	return EXIT_SUCCESS;
}
