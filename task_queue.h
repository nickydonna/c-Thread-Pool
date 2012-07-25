#ifndef _TASK_QUEUE_H_
	#define _TASK_QUEUE_H_


typedef void *(*Task)(void *);

typedef struct C {
	int thread;
	int taskId;
	Task task;
	void *argument;
	struct C *next;
} TaskNode;

int queue_addNewTask(Task task, void *taskArgument, int taskId,  TaskNode **first, TaskNode **last);
TaskNode *queue_getNextTask(TaskNode **first, TaskNode **last);


#endif
