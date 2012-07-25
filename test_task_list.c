#include <stdlib.h>
#include "minunit.h"
#include "task_list.h"
#include "mock.c"
#include <semaphore.h>
#include <pthread.h>

int tests_run = 0;

TaskList *list = NULL;

static char *set_up() {
	int res = 0;
	list = (TaskList *)malloc(sizeof(TaskList));
	mu_assert("Task_List: Error Couldn't malloc in set_up!!",list != NULL);	
	res += pthread_mutex_init(&(list->priorityListMutex), NULL);
	res += pthread_mutex_init(&(list->returnListMutex), NULL);
	mu_assert("Task_List: Error Couldn't initialize Mutex in set_up()!!", res == 0);
	list->priorityFirstNode = NULL;
	list->priorityLastNode = NULL;
	list->returnFirstNode = NULL;
	list->returnLastNode = NULL;
	list->nextTaskId = 1;
	list->work = 0;
	return 0;
}


static char *test_addNewTask() {
	int *value = NULL, *value2 = NULL;
	value = (int *)malloc(sizeof(int));
	value2 = (int *)malloc(sizeof(int));
	mu_assert("Task_List: Error couldn't malloc in test_addNewTask()!!", value != NULL && value != NULL);
	*value = 1;
	*value2 = 2;
	mu_assert("Task_List: Error Couldn't initialize Semaphore in test_addNewTask!!", sem_init(&(list->sem), 0, 0) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_addNewTask!!", addNewTask(&list, mock_function, (void *)value, 20) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_addNewTask!!", addNewTask(&list, mock_function, (void *)value2, 20) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_addNewTask!!", addNewTask(&list, mock_function, (void *)value, 40) == 0);
	return 0;
}

static char *test_getNextTask() {
	int *value = NULL;
	TaskNode *task = NULL;
	value = (int *)malloc(sizeof(int));
	task = getNextTask(&list);
	mu_assert("Task_List: Error Couldn't retrieve first task from List in test_getNextTask()!!", task != NULL);
	value = (int *)task->task(task->argument);
	mu_assert("Task_List: Error Task didn't work properly in test_getNextTask()!!", *value == 2);
	task = getNextTask(&list);
	mu_assert("Task_List: Error Couldn't retrieve second task from List in test_getNextTask()!!", task != NULL);
	value = (int *)task->task(task->argument);
	mu_assert("Task_List: Error Task didn't work properly in test_getNextTask()!!", *value == 3);
	task = getNextTask(&list);
	mu_assert("Task_List: Error Couldn't retrieve third task from List in test_getNextTask()!!", task != NULL);
	task = getNextTask(&list);
	mu_assert("Task_List: Error Task is not null when list should be empty!!", task == NULL);
	return 0;
}

static char *run_all_test() {
	mu_run_test(set_up);
	mu_run_test(test_addNewTask);
	mu_run_test(test_getNextTask);
	return 0;
}

int main(int argc, char **argv) {
	char *result;
	result = run_all_test();
	if(result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("\tTask_List: ALL TEST PASSED!!!\n");
	}
	printf("\t\tTests runned: %d\n", tests_run);
	return result != 0;
}
