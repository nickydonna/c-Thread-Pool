#include "pthreadpool.h"

void* functionLoop (void* tlist){
	Tasklist * list = (TaskList *) tlist;
	taskNode curentTask = NULL;
	int work = 1;
	void * returnValue;
	while (work != 0){
		if (list->work > 0){
			work = 0;
			list->work-=1;
			break;
		}
		currentTask = getTask(list);
		if (currentTask.saveReturnValue != 0){
			currentTask.task(currentTask.argument);
			continue;
		}
		returnValue = currentTask.task(currentTask.argument);
		addReturnValue(list->returnFirstNode, list->returnLastNode, returnValue, currentTask.id);
	}

	return NULL;
}
