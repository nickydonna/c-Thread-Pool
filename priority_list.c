#include "priority_list.h"
#include <stdlib.h>
#include <stdio.h>

int list_add_new_task(task_t task, void *argument, int priority, uuid_t task_id,  list_node_t **first, list_node_t **last) {		
	list_node_t *aux, *new, *previous;

	if (*first == NULL || *last == NULL) {
		new = (list_node_t *)malloc(sizeof(list_node_t));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		new->next = NULL;
		if(queue_add_new_task(task, argument, task_id, &(new->first), &(new->last)) == 0) {
			*first = *last = new;
			return 0;
		}
		return -1;
	}
	
	aux = *first;
	
	if(aux->priority == priority) {
		
		if(queue_add_new_task(task, argument, task_id, &(aux->first), &(aux->last)) == 0) {	
			return 0;
		}
		return -1;
	}

	if(aux->priority > priority) {
		new = (list_node_t *)malloc(sizeof(list_node_t));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		if(queue_add_new_task(task, argument, task_id, &(new->first), &(new->last)) == 0) {	
			new->next = *first;
			*first = new;
			return 0;
		}
		return -1;
	}
	while(aux->priority <= priority && aux->next != NULL) {
		previous = aux;
		aux = aux->next;
		
		if(aux->priority == priority) {
			if(queue_add_new_task(task, argument, task_id, &(aux->first), &(aux->last)) == 0) {
				return 0;
			}
			return -1;
		}
		if(aux->priority > priority) {
			new = (list_node_t *)malloc(sizeof(list_node_t));
			new->priority = priority;
			new->first = NULL;
			new->last = NULL;
			if(queue_add_new_task(task, argument, task_id, &(new->first), &(new->last)) == 0) {	
				previous->next = new;
				new->next = aux;
				return 0;
			}
			return -1;
		}
	}
	
	if(aux->priority < priority) {
		new = (list_node_t *)malloc(sizeof(list_node_t));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		if(queue_add_new_task(task, argument, task_id, &(new->first), &(new->last)) == 0) {
			(*last)->next = new;
			*last = new;
			return 0;
		}
	}
	return -1;	
}

task_node_t *list_get_next_task(list_node_t **first, list_node_t **last) {
	task_node_t *task = NULL;
	list_node_t *aux = NULL;

	aux = *first;

	while(aux->first == NULL) {
		aux = aux->next;
		if(aux == NULL) {
			return NULL;
		}
		if((*first) == (*last)) {
			break;
		}
	}
	task = queue_get_next_task(&(aux->first), &(aux->last));
	if (task == NULL) {
		/* Generar Error de No hay Tareas */
		return NULL;
	}
	return task;
}
