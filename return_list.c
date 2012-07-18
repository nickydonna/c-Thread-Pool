#include "return_list.h"
#include "task_list.h"
#include <stdlib.h>

int addReturnValue (ReturnNode **first, ReturnNode **last, void *returnValue, int taskId){
	ReturnNode *node = (ReturnNode*)malloc(sizeof(ReturnNode));
	if (node == NULL){
		return -1;
	}
	node->returnValue=returnValue;
	node->taskId=taskId;

	node->next = NULL;

	if (*first == NULL)
	{
		*first=node;
		*last=node;
		return 0;
	}

	(*last)->next=node;
	*last=node;
	return 0;
}

