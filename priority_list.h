#ifndef _PRIORITY_LIST_H_
	#define _PRIORITY_LIST_H_
	#include "task_queue.h"

typedef struct E {
	struct E *next;
	int priority;
	
	task_node_t *first;
	task_node_t *last;
} list_node_t;

int list_add_new_task(task_t task, void *argument, int priority, uuid_t task_id, list_node_t **first, list_node_t **last);
task_node_t *list_get_next_task(list_node_t **first, list_node_t **last);

#endif
