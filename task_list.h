#ifndef _TASK_LIST_H_
	#define _TASK_LIST_H_
	#include <stdlib.h>
	#include "priority_list.h"
	#include "return_list.h"
	#include <pthread.h>
	#include <semaphore.h>

enum pthread_status {
        THREAD_RUNNING,
        THREAD_SLEEPING,
        THREAD_BETWEEN_FUNCTIONS
};

typedef struct {
	int work;
	sem_t sem;
	
	pthread_mutex_t return_list_mutex;
	pthread_mutex_t priority_list_mutex;
	list_node_t *priority_first_node;
	list_node_t *priority_last_node;
	return_node_t *return_first_node;
	return_node_t *return_last_node;

	pthread_barrier_t barrier;
}task_list_t;

int add_new_task(task_list_t **list, task_t task, void* argument, int priority);
task_node_t *get_next_task(task_list_t **list);
int get_return_value_by_id(task_list_t** list, uuid_t task_id, void** value_returned);

#endif	
