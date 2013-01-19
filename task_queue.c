#include "task_queue.h"
#include <stdlib.h>

int queue_add_new_task(Task task, void *task_argument, int task_id, TaskNode **first, TaskNode **last) {
	TaskNode *new;
	new = (TaskNode *)malloc(sizeof(TaskNode));
	new->thread = 1234;
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

TaskNode *queue_get_next_task(TaskNode **first, TaskNode **last) {
	
	TaskNode *aux = NULL;
	
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
