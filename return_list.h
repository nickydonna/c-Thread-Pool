#ifndef _RETURN_LIST_H_
	#define _RETURN_LIST_H_

#include <pthread.h>

enum tasks_states {
	TASK_NOT_STARTED,
	TASK_RUNNING,
	TASK_FINISHED
};

typedef struct D {
	int taskId;
	void *returnValue;
	struct D *next;
	enum tasks_states task_state;
} ReturnNode;


int addReturnValue(ReturnNode **first, ReturnNode **last, void *returnValue, int taskId, enum tasks_states task_state, pthread_mutex_t *mutex);
int changeReturnValue (ReturnNode **first, ReturnNode **last, void *returnValue, int taskId, enum tasks_states task_state, pthread_mutex_t *mutex);


#endif
