#ifndef _RETURN_LIST_H_
	#define _RETURN_LIST_H_


typedef struct D {
	int taskId;
	void *returnValue;
	struct D *next;
} ReturnNode;


int addReturnValue(ReturnNode **first, ReturnNode **last, void *returnValue, int taskId);



#endif
