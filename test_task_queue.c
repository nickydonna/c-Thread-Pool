#include "task_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int tests_run = 0;

QueueNode *first = NULL, *last = NULL;

void *mock_function(void *value){
	int *aux = (int *)value;
	(*aux)++;
	return aux;
}

static char *test_addNewTask() {
	int *value;
	value = (int *)malloc(sizeof(int));
	*value = 1;
	mu_assert("Task_Queue: Error inserting function in test_addNewTask()!!", queue_addNewTask(mock_function, (void *)value, 1, &first, &last) == 0);
	*value++;
	mu_assert("Task_Queue: Error inserting function in test_addNewTask()!!", queue_addNewTask(mock_function, (void *)value, 2, &first, &last) == 0);
	return 0;
}

static char *test_getNextTask() {
	int *value;
	QueueNode *aux = NULL;
	aux = queue_getNextTask(&first, &last);
	mu_assert("Task_Queue: Error Queue is empty in test_getNextTask()!!", aux != NULL);
	mu_assert("Task_Queue: Error Dind't get first value (taskId != 1) in test_getNextTask()!!", aux->taskId == 1);
	value = (int *)aux->task(aux->argument);
	mu_assert("Task_Queue: Error Function didn't returned expected value in test_getNextTask()!!", *value == 2);
	aux = queue_getNextTask(&first, &last);
	mu_assert("Task_Queue: Error Dind't get second value (taskId != 2) in test_getNextTask()!!", aux->taskId == 2);
	return 0;
}

static char *run_all_test() {
	mu_run_test(test_addNewTask);
	mu_run_test(test_getNextTask);
	return 0;
}

int main(int argc, char **argv) {
	char *result;
	result = run_all_test();
	if(result != 0) {
		printf("%s\n",result);
	}
	else {
		printf("ALL TEST PASSED!!\n");
	}
	printf("Tests runned: %d\n", tests_run);
	return result != 0;
}

