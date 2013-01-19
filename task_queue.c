#include "task_queue.h"
#include <stdlib.h>

int queue_add_new_task(task_t task, void *task_argument, int task_id, task_node_t **first, task_node_t **last) {
	task_node_t *new;
	new = (task_node_t *)malloc(sizeof(task_node_t));	
	new->task = task;
	new->argument = task_argument;
	new->task_id = task_id;
	new->next = NULL;

	if(*first == NULL && *last == NULL) {
		*first = *last = new;
		return 0;
	}

	(*last)->next = new;
	*last = new;
	return 0;
}

task_node_t *queue_get_next_task(task_node_t **first, task_node_t **last) {
	
	task_node_t *aux = NULL;
	
	aux = *first;
	if(*first == *last) {
		*first = *last = NULL;
		return aux;		
	}

	if((*first)->next == *last) {
		*first = *last;
		return aux;
	}
	*first = (*first)->next;
	
	return aux;
}
