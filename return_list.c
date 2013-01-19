#include "return_list.h"
#include "task_list.h"

int add_return_value (return_node_t **first, return_node_t **last, void *return_value, unsigned char * task_id, enum tasks_states task_state, pthread_mutex_t *mutex){
	return_node_t *node = (return_node_t*)malloc(sizeof(return_node_t));
	if (node == NULL){
		return -1;
	}
	pthread_mutex_lock(mutex);
	node->return_value=return_value;
	node->task_id=task_id;
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

int change_return_value (return_node_t **first, return_node_t **last, void *return_value, unsigned char * task_id, enum tasks_states task_state, pthread_mutex_t *mutex){
	return_node_t *node=NULL;
	pthread_mutex_lock(mutex);
	for (node=*first; node != NULL; node=node->next)
	{
		if (node->task_id == task_id){
			node->return_value = return_value;
			node->task_state = task_state;
			pthread_mutex_unlock(mutex);
			return 0;
		}
	}
	pthread_mutex_unlock(mutex);
	return -1;
}
