#include "return_list.h"
#include "task_list.h"
#include <stdlib.h>

int addReturnValue (ReturnNode **first, ReturnNode **last, void *returnValue, int taskId, enum tasks_states task_state, pthread_mutex_t *mutex){
	ReturnNode *node = (ReturnNode*)malloc(sizeof(ReturnNode));
	if (node == NULL){
		return -1;
	}
	pthread_mutex_lock(mutex);
	node->returnValue=returnValue;
	node->taskId=taskId;
	node->task_state=task_state;

	node->next = NULL;

	if (*first == NULL)
	{
		*first=node;
		*last=node;
		pthread_mutex_unlock(mutex);
		return 0;
	}

	(*last)->next=node;
	*last=node;
	pthread_mutex_unlock(mutex);
	return 0;
}

int changeReturnValue (ReturnNode **first, ReturnNode **last, void *returnValue, int taskId, enum tasks_states task_state, pthread_mutex_t *mutex){
	ReturnNode *node=NULL;
	pthread_mutex_lock(mutex);
	for (node=*first; node != NULL; node=node->next)
	{
		if (node->taskId == taskId){
			node->returnValue = returnValue;
			node->task_state = task_state;
			pthread_mutex_unlock(mutex);
			return 0;
		}
	}
	pthread_mutex_unlock(mutex);
	return -1;
}
