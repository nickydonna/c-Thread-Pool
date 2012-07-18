#ifndef _TASK_QUEUE_H_
	#define _TASK_QUEUE_H_


typedef void *(*Task)(void *);

typedef struct C {
	int thread;
	int taskId;
	Task task;
	void *argument;
	struct C *next;
} QueueNode;

int queue_addNewTask(Task task, void *taskArgument, int taskId,  QueueNode **first, QueueNode **last);
QueueNode *queue_getNextTask(QueueNode **first, QueueNode **last);


#endif
