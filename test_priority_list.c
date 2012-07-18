#include "priority_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int tests_run = 0;

ListNode *first = NULL, *last = NULL;

void *mock_function(void *value) {
	int *aux = (int *)value;
	(*aux)++;
	return aux;
}

static char *test_addNewTask() {
	int *value;
	value = (int *)malloc(sizeof(int));
	*value = 1;
	mu_assert("Priority_List: Error adding function to list in test_addNewTask()", list_addNewTask(mock_function, (void *)value, 20, 1, &first, &last) == 0);	
	mu_assert("Priority_List: Error adding function to list in test_addNewTask()", list_addNewTask(mock_function, (void *)value, 10, 2, &first, &last) == 0);
	return 0;
}

static char *test_getNextTask() {
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
		printf("ALL TEST PASSED!!\n");
	}
	printf("Test runned: %d\n", tests_run);
	return result != 0;
}


