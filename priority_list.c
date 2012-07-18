#include "priority_list.h"
#include <stdlib.h>
int list_addNewTask(Task task, void *argument, int priority, int taskId,  ListNode **first, ListNode **last) {
		
	int work = 1;
	ListNode *aux, *new;
	QueueNode *firstNode, *lastNode;

	if (*first == NULL || *last == NULL) {
		new = (ListNode *)malloc(sizeof(ListNode));
		firstNode = (QueueNode *)malloc(sizeof(QueueNode));
		lastNode = (QueueNode *)malloc(sizeof(QueueNode));
		new->priority = priority;
		new->first = firstNode;
		new->last = lastNode;
		if(queue_addNewTask(task, argument, taskId, &firstNode, &lastNode) == 0) {
			return 0;
		}
	}
	
	aux = *first;

	if(aux->priority == priority) {
		return queue_addNewTask(task, argument, taskId, &(aux->first), &(aux->last));
	}

	while(work != 0) {
		if(aux->next->priority == priority) {
			return queue_addNewTask(task, argument, taskId, &(aux->first), &(aux->last));
		}
		if(aux->next->priority < priority) {
			ListNode *new;
			new = (ListNode *)malloc(sizeof(ListNode));
			firstNode = (QueueNode *)malloc(sizeof(QueueNode));
			lastNode = (QueueNode *)malloc(sizeof(QueueNode));
			new->first = firstNode;
			new->last = lastNode;
			return queue_addNewTask(task, argument, taskId, &firstNode, &lastNode);
		}

		if (aux == *last) {
			return -1;
		}
		aux = aux->next;
		
	}
	return -1;	
}

QueueNode *list_getNextTask(ListNode **first, ListNode **last) {
	
	return NULL;	
}
