#include <stdio.h>
#include "debug.h"

void *mock_function(void *value){
	int i = 0;
        int *aux = (int *)value;
        (*aux)++;
	for (i; i < 100; i+=2) {
		i--;
	}
	char buff[50];
	sprintf(buff, "Value: %d", *aux);
	d_print(buff);
        return aux;
}


