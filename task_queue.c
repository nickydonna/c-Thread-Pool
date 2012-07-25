#include "task_queue.h"
#include <stdlib.h>

int queue_addNewTask(Task task, void *taskArgument, int taskId, TaskNode **first, TaskNode **last) {
	TaskNode *new;
	new = (TaskNode *)malloc(sizeof(TaskNode));
	new->thread = 1234;
	new->task = task;
	new->argument = taskArgument;
	new->taskId = taskId;
	new->next = NULL;

	if(*first == NULL && *last == NULL) {
		*first = *last = new;
		return 0;
	}

	(*last)->next = new;
	*last = new;
	return 0;
}

TaskNode *queue_getNextTask(TaskNode **first, TaskNode **last) {
	
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
