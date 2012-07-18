#include "return_list.h"
#include "task_list.h"
#include "task_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int tests_run = 0;
struct TaskList *list;

static char *test_addReturnValue() {
	int *r1, *r2, *r3;
	list= malloc(sizeof(TaskList));
	r1= malloc (sizeof(int));
	r2= malloc (sizeof(int));
	r3= malloc (sizeof(int));
	list->returnFirstNode=NULL;
	list->returnLastNode=NULL;

	mu_assert("Task_List: Error couldn't make malloc in test_addReturnValue()!!", (r1 != NULL || r2 != NULL || r3 != NULL));

	*r1 = 1;
	*r2 = 2;
	*r3 = 3;

	mu_assert("Task_List: Error in test_addReturnValue(1)!!", ( addReturnValue(&(list->returnFirstNode), &(list->returnLastNode), (void *) r1, 1)  == 0 )   );
	mu_assert("Task_List: Error in test_addReturnValue(2)!!", ( addReturnValue(&(list->returnFirstNode), &(list->returnLastNode), (void *) r2, 2)  == 0 )   );
	mu_assert("Task_List: Error in test_addReturnValue(3)!!", ( addReturnValue(&(list->returnFirstNode), &(list->returnLastNode), (void *) r3, 3)  == 0 )   );
	
	return 0;
}

static char *test_getReturnValueById() {
	int *rv=NULL;
//	mu_assert("Task_List: Error in test_getReturnValueById(1)!!", ( getReturnValueById(&list, 2, (void *) &rv) == 0 ) ||  (*rv ==2));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_getReturnValueById(2)!!", ( getReturnValueById(&list, 1, (void *) &rv) == 0 ) ||  (*rv ==1));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_getReturnValueById(3))!!", ( getReturnValueById(&list, 3, (void *) &rv) == 0 ) ||  (*rv ==3));

	return 0;
}
static char *run_all_test() {
	mu_run_test(test_addReturnValue);
	mu_run_test(test_getReturnValueById);
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
	return (result != 0);
}

