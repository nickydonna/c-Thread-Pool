#ifndef _RETURN_LIST_H_
	#define _RETURN_LIST_H_

#include <pthread.h>

enum tasks_states {
	TASK_NOT_STARTED,
	TASK_RUNNING,
	TASK_FINISHED
};

typedef struct D {
	int task_id;
	void *return_value;
	struct D *next;
	enum tasks_states task_state;
} ReturnNode;


int add_return_value(ReturnNode **first, ReturnNode **last, void *return_value, int task_id, enum tasks_states task_state, pthread_mutex_t *mutex);
int change_return_value (ReturnNode **first, ReturnNode **last, void *return_value, int task_id, enum tasks_states task_state, pthread_mutex_t *mutex);


#endif
