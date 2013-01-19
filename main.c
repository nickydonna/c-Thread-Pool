#include <stdlib.h>
#include "pthread_pool.h"
#include <stdio.h>
#include "debug.h"
#include "mock.c"

int main(int argc, char *argv[]) {
	pthread_pool *tp = NULL;
	int *value = NULL, i = 1;
	value = (int *)malloc(sizeof(int));
	if(value == NULL) {
		printf("Main: Couldn't malloc");
		return -1;
	}
	tp = pthread_pool_create(NULL);
	if(tp == NULL) {
		printf("Main: Error pthread_pool_create returns NULL");
		return -1;
	}
	while(1) {
		if(add_new_task(&(tp->list), mock_function, (void *)value, i) != 0) {
			printf("Main: Error couldn't add Task");
			return -1;
		}
		i++;
	}

	
	sleep(5);
	return 0;
}
