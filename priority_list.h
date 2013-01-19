#ifndef _PRIORITY_LIST_H_
	#define _PRIORITY_LIST_H_
	#include "task_queue.h"

typedef struct E {
	struct E *next;
	int priority;
	
	TaskNode *first;
	TaskNode *last;
} ListNode;

int list_add_new_task(Task task, void *argument, int priority, int taskId, ListNode **first, ListNode **last);
TaskNode *list_get_next_task(ListNode **first, ListNode **last);

#endif
