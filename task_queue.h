#ifndef _TASK_QUEUE_H_
	#define _TASK_QUEUE_H_


typedef void *(*Task)(void *);

typedef struct C {
	int thread;
	int task_id;
	Task task;
	void *argument;
	struct C *next;
} TaskNode;

int queue_add_new_task(Task task, void *task_argument, int taskId,  TaskNode **first, TaskNode **last);
TaskNode *queue_get_next_task(TaskNode **first, TaskNode **last);


#endif
