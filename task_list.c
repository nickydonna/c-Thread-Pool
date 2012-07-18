#include "return_list.h"
#include "task_list.h"
#include <stdlib.h>

#include <stdio.h>

int getReturnValueById(TaskList** list, int taskId, void** valueReturned){
	ReturnNode *node= NULL;
	ReturnNode *aux= NULL;
	if ((*list)->returnFirstNode == NULL)
	{
		return -1;
	}

	if ((*list)->returnFirstNode->taskId == taskId)
	{
		aux=((*list)->returnFirstNode);
	}
	else
		for(node=(*list)->returnFirstNode; node->next !=NULL; node=node->next){
			if (node->next->taskId == taskId){
				aux=node->next;
				break;
			}
		}

	if (aux==NULL){
		return -2;
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
	printf("taskId: %d\nval: %d\n", taskId, *(int *)(aux->returnValue));

	return 0;
}

