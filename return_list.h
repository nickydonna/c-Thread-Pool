#ifndef _RETURN_LIST_H_
	#define _RETURN_LIST_H_
#include <uuid/uuid.h>
#include <stdlib.h>
#include <pthread.h>

enum tasks_states {
	TASK_NOT_STARTED,
	TASK_RUNNING,
	TASK_FINISHED
};

typedef struct D {
	unsigned char * task_id;
	void *return_value;
	struct D *next;
	enum tasks_states task_state;
} return_node_t;


int add_return_value(return_node_t **first, return_node_t **last, void *return_value, unsigned char * task_id, enum tasks_states task_state, pthread_mutex_t *mutex);
int change_return_value (return_node_t **first, return_node_t **last, void *return_value, unsigned char * task_id, enum tasks_states task_state, pthread_mutex_t *mutex);


#endif
