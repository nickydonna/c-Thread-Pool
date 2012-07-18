#ifndef _PRIORITY_LIST_H_
	#define _PRIORITY_LIST_H_
	#include "task_queue.h"

typedef struct E {
	struct E *next;
	int priority;
	
	QueueNode *first;
	QueueNode *last;
} ListNode;

int list_addNewTask(Task task, void *argument, int priority, int taskId, ListNode **first, ListNode **last);
QueueNode *list_getNextTask(ListNode **first, ListNode **last);

#endif
