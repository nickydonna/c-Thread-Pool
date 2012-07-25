#ifndef _TASK_LIST_H_
	#define _TASK_LIST_H_
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
        pthread_t pthread_id;
        enum pthread_status status;
}pthread_info;

typedef struct {
	int work;
	int nextTaskId;
	sem_t sem;
	pthread_info *pthreads;
	pthread_mutex_t returnListMutex;
	pthread_mutex_t priorityListMutex;
	ListNode *priorityFirstNode;
	ListNode *priorityLastNode;
	ReturnNode *returnFirstNode;
	ReturnNode *returnLastNode;
}TaskList;

int addNewTask(TaskList **list, Task task, void* argument, int priority);
TaskNode *getNextTask(TaskList **list);
int getReturnValueById(TaskList** list, int taskId, void** valueReturned);

#endif	
