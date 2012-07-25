#include "priority_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "mock.c"

int tests_run = 0;

ListNode *first = NULL, *last = NULL;

static char *test_addNewTask() {
	int *value, *value2;
	value = (int *)malloc(sizeof(int));
	value2 = (int *)malloc(sizeof(int));
	*value = 1;
	mu_assert("Priority_List: Error adding function to list (taskId = 1) in test_addNewTask()", list_addNewTask(mock_function, (void *)value, 20, 1, &first, &last) == 0);	
	*value2 = 2;
	mu_assert("Priority_List: Error adding function to list (taskId = 2) in test_addNewTask()", list_addNewTask(mock_function, (void *)value, 10, 2, &first, &last) == 0);
	mu_assert("Priority_List: Error adding function to list (taskId = 3) in test_addNewTask()", list_addNewTask(mock_function, (void *)value2, 15, 3, &first, &last) == 0);	
	mu_assert("Priority_List: Error adding function to list (taskId = 3) in test_addNewTask()", list_addNewTask(mock_function, (void *)value, 30, 4, &first, &last) == 0);
	return 0;
}

static char *test_getNextTask() {
	TaskNode *node = NULL;
	int *val;
	val = (int *)malloc(sizeof(int));
	node = list_getNextTask(&first, &last);
	mu_assert("Priority_List: Error No Function Retrieved in test_getNextTask()!!", node != NULL);
	mu_assert("Priority_List: Error Function not retrieved in priority order (taskId should be 2) in test_getNextTask()!!", node->taskId == 2);
	val = (int *)node->task(node->argument);
	mu_assert("Priority_List: Error mock_function not working Properly in test_getNextTask()!!", *val == 2);
	node = list_getNextTask(&first, &last);		
	mu_assert("Priority_List: Error No Function Retrieved in test_getNextTask()!!", node != NULL);
	mu_assert("Priority_List: Error Function not retrieved in priority order (taskId shoulb be 3) in test_getNextTask()!!", node->taskId == 3);
	val = (int *)node->task(node->argument);
	mu_assert("Priority_List: Error mock_function not working Properly in test_getNextTask()!!", *val == 3);
	node = list_getNextTask(&first, &last);
	mu_assert("Priority_List: Error Function not retrieved in priority order (taskId shoulb be 2) in test_getNextTask()!!", node->taskId == 2);
	node = list_getNextTask(&first, &last);
	mu_assert("Priority_List: Error Function not retrieved in priority order (taskId shoulb be 4) in test_getNextTask()!!", node->taskId == 4);
	node = list_getNextTask(&first, &last);
	mu_assert("Priority_List: List has node when it should be empty in test_getNextTask()!!", node == NULL);	
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
		printf("%s\n", result);
	}
	else {
		printf("\tPriority_List: ALL TEST PASSED!!\n");
	}
	printf("\t\tTest runned: %d\n", tests_run);
	return result != 0;
}


