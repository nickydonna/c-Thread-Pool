#include "pthread_pool.h"

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int tests_run = 0;
pthread_pool* ptp= NULL;

static char *test_pthread_pool_create() {
	ptp= pthread_pool_create(NULL);

	mu_assert("Task_List: Error in pthread_pool_create()!!",  ptp != NULL);
	return 0;
}

static char *test_function_loop() {
/*	int *rv=NULL;
	mu_assert("Task_List: Error in test_getReturnValueById(1)!!",  getReturnValueById(&list, 2, (void *) &rv)==0);
	mu_assert("Task_List: Error in test_getReturnValueById(1) Not the expected return value!!", (*(int *) rv ==2));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_getReturnValueById(2)!!", getReturnValueById(&list, 1, (void *) &rv)== 0 );
	mu_assert("Task_List: Error in test_getReturnValueById(2) Not the expected return value!!", (*(int *) rv==1));
	free(rv);
	rv=NULL;
	mu_assert("Task_List: Error in test_getReturnValueById(3)!!", getReturnValueById(&list, 3, (void *) &rv)== 0 );
	mu_assert("Task_List: Error in test_getReturnValueById(3) Not the expected return value!!", (*(int *)rv ==3));

	return 0;
*/
}
static char *run_all_test() {
	mu_run_test(test_pthread_pool_create);
	/*mu_run_test(test_function_loop);*/
	return 0;
}

int main(int argc, char **argv) {
	char *result;

result = run_all_test();
	if(result != 0) {
		printf("%s\n",result);
	}
	else {
		printf("\tALL TEST PASSED!!\n");
	}
	printf("\t\tTests runned: %d\n", tests_run);
	return (result != 0);
}

