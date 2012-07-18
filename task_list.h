#ifndef _TASK_LIST_H_
	#define _TASK_LIST_H_
	#include "priority_list.h"
	#include "return_list.h"
	#include <pthread.h>

typedef struct TaskList{
	int work;
	pthread_mutex_t returnListMutex;
	pthread_mutex_t priorityListMutex;
	ListNode *priorityFirstNode;
	ListNode *priorityLastNode;
	ReturnNode *returnFirstNode;
	ReturnNode *returnLastNode;
}TaskList;

int getReturnValueById(TaskList** list, int taskId, void** valueReturned);

#endif	
