#ifndef _TASK_QUEUE_H_
	#define _TASK_QUEUE_H_
	#include <stdlib.h>
	#include <uuid/uuid.h>

typedef void *(*task_t)(void *);

typedef struct C {
	unsigned char * task_id;
	task_t task;
	void *argument;
	struct C *next;
} task_node_t;

int queue_add_new_task(task_t task, void *task_argument, uuid_t task_id, task_node_t **first, task_node_t **last);
task_node_t *queue_get_next_task(task_node_t **first, task_node_t **last);


#endif
