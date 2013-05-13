#include <stdlib.h>
#include "minunit.h"
#include "task_list.h"
#include "mock.c"
#include <semaphore.h>
#include <pthread.h>

int tests_run = 0;

task_list_t *list = NULL;

static char *set_up() {
	int res = 0;
	list = (task_list_t *)malloc(sizeof(task_list_t));
	mu_assert("Task_List: Error Couldn't malloc in set_up!!",list != NULL);	
	res += pthread_mutex_init(&(list->priority_list_mutex), NULL);
	res += pthread_mutex_init(&(list->return_list_mutex), NULL);
	mu_assert("Task_List: Error Couldn't initialize Mutex in set_up()!!", res == 0);
	list->priority_first_node = NULL;
	list->priority_last_node = NULL;
	list->return_first_node = NULL;
	list->return_last_node = NULL;
	list->work = 0;
	return 0;
}


static char *test_add_new_task() {
	int *value = NULL, *value2 = NULL, *value3 = NULL;
	value = (int *)malloc(sizeof(int));
	value2 = (int *)malloc(sizeof(int));
	value3 = (int *)malloc(sizeof(int));
	mu_assert("Task_List: Error couldn't malloc in test_add_new_task()!!", value != NULL && value != NULL);
	*value = 1;
	*value2 = 2;
	*value3 = 3;
	mu_assert("Task_List: Error Couldn't initialize Semaphore in test_add_new_task!!", sem_init(&(list->sem), 0, 0) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_add_new_task!!", add_new_task(&list, mock_function, (void *)value, 20) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_add_new_task!!", add_new_task(&list, mock_function, (void *)value2, 20) == 0);
	mu_assert("Task_List: Error Couldn't add First Task in test_add_new_task!!", add_new_task(&list, mock_function, (void *)value3, 40) == 0);
	return 0;
}

static char *test_get_next_task() {
	int *value = NULL;
	task_node_t *task = NULL;
	value = (int *)malloc(sizeof(int));
	task = get_next_task(&list);
	printf("hi\n");
	mu_assert("Task_List: Error Couldn't retrieve first task from List in test_get_next_task()!!", task != NULL);
	value = (int *)task->task(task->argument);
	mu_assert("Task_List: Error Task didn't work properly in test_get_next_task()!!", *value == 2);
	task = get_next_task(&list);
	mu_assert("Task_List: Error Couldn't retrieve second task from List in test_get_next_task()!!", task != NULL);
	value = (int *)task->task(task->argument);
	mu_assert("Task_List: Error Task didn't work properly in test_get_next_task()!!", *value == 3);
	task = get_next_task(&list);
	mu_assert("Task_List: Error Couldn't retrieve third task from List in test_get_next_task()!!", task != NULL);
	task = get_next_task(&list);
	printf("hi\n");
	mu_assert("Task_List: Error Task is not null when list should be empty!!", task == NULL);
	return 0;
}

static char *run_all_test() {
	mu_run_test(set_up);
	mu_run_test(test_add_new_task);
	mu_run_test(test_get_next_task);
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
