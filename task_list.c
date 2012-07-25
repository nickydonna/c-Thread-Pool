#include "return_list.h"
#include "task_list.h"
#include <stdlib.h>
#include <stdio.h>

int addNewTask(TaskList **list, Task task, void *argument, int priority) {

	if(pthread_mutex_lock(&((*list)->priorityListMutex)) != 0) return -1;
	if(list_addNewTask(task, argument, priority, (*list)->nextTaskId, &((*list)->priorityFirstNode), &((*list)->priorityLastNode)) != 0){
		/* Set Error */
		return -1;
	}
	if(sem_post(&((*list)->sem)) != 0){
		/* Set Error */
		return -1;
	}
	if(addReturnValue(&((*list)->returnFirstNode), &((*list)->returnLastNode), NULL , (*list)->nextTaskId, TASK_NOT_STARTED, &(*list)->returnListMutex) != 0) {
		/* Set Error */
		return -1;
	}
	((*list)->nextTaskId)++;
	if(pthread_mutex_unlock(&((*list)->priorityListMutex)) != 0) return -1;
	if(addReturnValue(&(*list)->returnFirstNode, &(*list)->returnLastNode, NULL, (*list)->nextTaskId-1, TASK_NOT_STARTED, &(*list)->returnListMutex) != 0)
	{
		/* Set Error */
		return -1;
	}
	return 0;
}

TaskNode *getNextTask(TaskList **list) {
	TaskNode *node = NULL;	

	if(sem_wait(&((*list)->sem)) != 0){
		/* Set Error */
		return NULL;
	}

	if (pthread_mutex_lock(&((*list)->priorityListMutex)) != 0) return NULL;

	if((node = list_getNextTask(&((*list)->priorityFirstNode), &((*list)->priorityLastNode))) == NULL) {
		/*Set Error */
		return NULL;
	}
	
	/* Set RUNNING in return list */
	if(pthread_mutex_unlock(&((*list)->priorityListMutex)) != 0) return NULL;

	changeReturnValue (&(*list)->returnFirstNode, &(*list)->returnLastNode, NULL, node->taskId, TASK_RUNNING, &(*list)->returnListMutex);
	return node;
}


int getReturnValueById(TaskList** list, int taskId, void** valueReturned){
	ReturnNode *node= NULL;
	ReturnNode *aux= NULL;

	pthread_mutex_lock(&(*list)->returnListMutex);
	if ((*list)->returnFirstNode == NULL)
	{
		pthread_mutex_unlock(&(*list)->returnListMutex);
		return -1;
	}
	if ((*list)->returnFirstNode->taskId == taskId)
	{
		aux=((*list)->returnFirstNode);
		node=aux->next;
	}
	else
	{
		for(node=(*list)->returnFirstNode; node->next !=NULL; node=node->next){
			if (node->next->taskId == taskId){
				aux=node->next;
				break;
			}
		}
	}

	if (aux==NULL){
		pthread_mutex_unlock(&(*list)->returnListMutex);
		return -2;
	}

	if(aux->task_state != TASK_FINISHED)
	{
		pthread_mutex_unlock(&(*list)->returnListMutex);
		return aux->task_state;
	}
	*valueReturned=aux->returnValue;
	
	node->next=aux->next;

	if (aux==(*list)->returnFirstNode){
		(*list)->returnFirstNode=aux->next;
	}
	if (aux==(*list)->returnLastNode){
		(*list)->returnLastNode=node;
		(*list)->returnLastNode->next=NULL;
	}
	free(aux);

	pthread_mutex_unlock(&(*list)->returnListMutex);
	return aux->task_state;
}

