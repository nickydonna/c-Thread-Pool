#ifndef _DEBUG_H_
	#define _DEBUG_H_

	#ifndef NDEBUG
        	#include <stdio.h>
	        #define d_print(message) do {printf("%s\n", message);} while(0)
	#else
        	#define d_printf(message)
	#endif
#endif
