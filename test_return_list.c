#include "task_list.h"

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int tests_run = 0;
task_list_t *list;

static char *test_add_return_value() {
	int *r1, *r2, *r3;
	list= malloc(sizeof(task_list_t));
	r1= malloc (sizeof(int));
	r2= malloc (sizeof(int));
	r3= malloc (sizeof(int));
	list->return_first_node=NULL;
	list->return_last_node=NULL;
	pthread_mutex_init(&(list->return_list_mutex), NULL);

	mu_assert("Task_List: Error couldn't make malloc in test_add_return_value()!!", (r1 != NULL || r2 != NULL || r3 != NULL));

	*r1 = 1;
	*r2 = 2;
	*r3 = 3;

	mu_assert("Task_List: Error in test_add_return_value(1)!!", ( add_return_value(&(list->return_first_node), &(list->return_last_node), (void *) r1, 1, TASK_FINISHED, &(list->return_list_mutex))  == 0 )   );
	mu_assert("Task_List: Error in test_add_return_value(2)!!", ( add_return_value(&(list->return_first_node), &(list->return_last_node), (void *) r2, 2, TASK_FINISHED, &(list->return_list_mutex))  == 0 )   );
	mu_assert("Task_List: Error in test_add_return_value(3)!!", ( add_return_value(&(list->return_first_node), &(list->return_last_node), (void *) r3, 3, TASK_FINISHED, &(list->return_list_mutex))  == 0 )   );
	
	return 0;
}

static char *test_get_return_value_by_id() {
	int *rv=NULL;
	mu_assert("Task_List: Error in test_get_return_value_by_id(1)!!",  get_return_value_by_id(&list, 2, (void *) &rv)==TASK_FINISHED);
	mu_assert("Task_List: Error in test_get_return_value_by_id(1) Not the expected return value!!", (*(int *) rv ==2));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_get_return_value_by_id(2)!!", get_return_value_by_id(&list, 1, (void *) &rv)== TASK_FINISHED );
	mu_assert("Task_List: Error in test_get_return_value_by_id(2) Not the expected return value!!", (*(int *) rv==1));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_get_return_value_by_id(3)!!", get_return_value_by_id(&list, 3, (void *) &rv)== TASK_FINISHED );
	mu_assert("Task_List: Error in test_get_return_value_by_id(3) Not the expected return value!!", (*(int *)rv ==3));

	return 0;
}
static char *run_all_test() {
	mu_run_test(test_add_return_value);
	mu_run_test(test_get_return_value_by_id);
	return 0;
}

int main(int argc, char **argv) {
	char *result;

	result = run_all_test();
	if(result != 0) {
		printf("%s\n",result);
	}
	else {
		printf("\tReturn_List: ALL TEST PASSED!!\n");
	}
	printf("\t\tTests runned: %d\n", tests_run);
	return (result != 0);
}

