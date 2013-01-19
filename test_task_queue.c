#include "task_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "mock.c"

int tests_run = 0;

task_node_t *first = NULL, *last = NULL;

static char *test_add_new_task() {
	int *value;
	uuid_t id;
	uuid_generate(id);
	value = (int *)malloc(sizeof(int));
	*value = 1;
	mu_assert("Task_Queue: Error inserting function in test_add_new_task()!!", queue_add_new_task(mock_function, (void *)value, id, &first, &last) == 0);
	uuid_generate(id);
	*value++;
	mu_assert("Task_Queue: Error inserting function in test_add_new_task()!!", queue_add_new_task(mock_function, (void *)value, id, &first, &last) == 0);
	return 0;
}

static char *test_get_next_task() {
	int *value;
	task_node_t *aux = NULL;
	aux = queue_get_next_task(&first, &last);
	mu_assert("Task_Queue: Error Queue is empty in test_get_next_task()!!", aux != NULL);
	mu_assert("Task_Queue: Error Dind't get first value (task_id != 1) in test_get_next_task()!!", aux->task_id == 1);
	value = (int *)aux->task(aux->argument);
	mu_assert("Task_Queue: Error Function didn't returned expected value in test_get_next_task()!!", *value == 2);
	aux = queue_get_next_task(&first, &last);
	mu_assert("Task_Queue: Error Dind't get second value (task_id != 2) in test_get_next_task()!!", aux->task_id == 2);
	return 0;
}

static char *run_all_test() {
	mu_run_test(test_add_new_task);
	mu_run_test(test_get_next_task);
	return 0;
}

int main(int argc, char **argv) {
	char *result;
	result = run_all_test();
	if(result != 0) {
		printf("%s\n",result);
	}
	else {
		printf("\tTask_Queue: ALL TEST PASSED!!\n");
	}
	printf("\t\tTests runned: %d\n", tests_run);
	return result != 0;
}

