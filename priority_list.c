#include "priority_list.h"
#include <stdlib.h>
#include <stdio.h>

int list_addNewTask(Task task, void *argument, int priority, int taskId,  ListNode **first, ListNode **last) {		
	ListNode *aux, *new, *previous;

	if (*first == NULL || *last == NULL) {
		new = (ListNode *)malloc(sizeof(ListNode));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		new->next = NULL;
		if(queue_addNewTask(task, argument, taskId, &(new->first), &(new->last)) == 0) {
			*first = *last = new;
			return 0;
		}
		return -1;
	}
	
	aux = *first;
	
	if(aux->priority == priority) {
		
		if(queue_addNewTask(task, argument, taskId, &(aux->first), &(aux->last)) == 0) {	
			return 0;
		}
		return -1;
	}

	if(aux->priority > priority) {
		new = (ListNode *)malloc(sizeof(ListNode));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		if(queue_addNewTask(task, argument, taskId, &(new->first), &(new->last)) == 0) {	
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
			if(queue_addNewTask(task, argument, taskId, &(aux->first), &(aux->last)) == 0) {
				return 0;
			}
			return -1;
		}
		if(aux->priority > priority) {
			new = (ListNode *)malloc(sizeof(ListNode));
			new->priority = priority;
			new->first = NULL;
			new->last = NULL;
			if(queue_addNewTask(task, argument, taskId, &(new->first), &(new->last)) == 0) {	
				previous->next = new;
				new->next = aux;
				return 0;
			}
			return -1;
		}
	}
	
	if(aux->priority < priority) {
		new = (ListNode *)malloc(sizeof(ListNode));
		new->priority = priority;
		new->first = NULL;
		new->last = NULL;
		if(queue_addNewTask(task, argument, taskId, &(new->first), &(new->last)) == 0) {
			(*last)->next = new;
			*last = new;
			return 0;
		}
	}
	return -1;	
}

TaskNode *list_getNextTask(ListNode **first, ListNode **last) {
	TaskNode *task = NULL;
	ListNode *aux = NULL;

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
	task = queue_getNextTask(&(aux->first), &(aux->last));
	if (task == NULL) {
		/* Generar Error de No hay Tareas */
		return NULL;
	}
	return task;
}
