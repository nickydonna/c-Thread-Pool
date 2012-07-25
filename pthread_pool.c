#include "pthread_pool.h"
#include "task_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
pthread_pool* pthread_pool_create(pthread_pool_attr *attr){
	pthread_pool *tp=NULL;
	int i;
	pthread_attr_t *create_attr=NULL;
	tp = malloc(sizeof(pthread_pool));
	if (tp == NULL){
		return NULL;
	}

	if (attr != NULL){

		if (attr->min > attr->max || attr->max < 0)
		{
			return NULL;
		}
		create_attr=attr->create_attr;
		tp->min = attr->min;
		tp->max = attr->max;

	}
	else
	{
		tp->min = 10;
		tp->max = 20;
	}
	tp->current =0;
	tp->list=malloc(sizeof(TaskList));
	if (tp->list == NULL){
		return NULL;
	}

	tp->list->pthreads=malloc(sizeof(pthread_info) * tp->max);
	if (tp->list->pthreads == NULL){
		return NULL;
	}
	tp->list->priorityFirstNode = NULL;
	tp->list->priorityLastNode = NULL;
	tp->list->returnFirstNode = NULL;
	tp->list->returnLastNode = NULL;
	tp->list->nextTaskId=1;
	sem_init(&(tp->list->sem), 0, 0);
	tp->list->work=0;
	if (pthread_mutex_init(&(tp->list->returnListMutex), NULL) != 0)
	{
		return NULL;
	}
	if (pthread_mutex_init(&(tp->list->priorityListMutex), NULL) != 0)
	{
		return NULL;
	}

	for (i=0; i<tp->max; i++){
		int rv;
		rv = pthread_create((pthread_t *) &(((tp->list->pthreads)+i)->pthread_id)  , create_attr, functionLoop, tp->list);
		if (rv != 0){
			return NULL;
		}
		tp->current++;
		/*tp->list->(pthreads+i)->status=BETWEEN_FUNCTIONS;*/
	}

	return tp;
}


void* functionLoop (void* tlist){
	TaskList * list = (TaskList *) tlist;
	TaskNode *currentTask = NULL;
	int work = 1;
	void * returnValue;
	while (work != 0){
		if (list->work > 0){
			work = 0;
			list->work-=1;
			break;
		}
		currentTask = getNextTask(&list);
		returnValue = currentTask->task(currentTask->argument);
		changeReturnValue(&(list->returnFirstNode), &(list->returnLastNode), returnValue, currentTask->taskId, TASK_FINISHED, &list->returnListMutex);
	}

	return NULL;
}




