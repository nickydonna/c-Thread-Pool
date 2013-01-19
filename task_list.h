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
	int next_task_id;
	sem_t sem;
	pthread_info *pthreads;
	pthread_mutex_t return_list_mutex;
	pthread_mutex_t priority_list_mutex;
	ListNode *priority_first_node;
	ListNode *priority_last_node;
	ReturnNode *return_first_node;
	ReturnNode *return_last_node;
}TaskList;

int add_new_task(TaskList **list, Task task, void* argument, int priority);
TaskNode *get_next_task(TaskList **list);
int get_return_value_by_id(TaskList** list, int task_id, void** value_returned);

#endif	
