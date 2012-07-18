#ifndef _PTHREADPOOL_H_
	#define _PTHREADPOOL_H_

enum pthread_status {
	RUNNING,
	SLEEPING
};

struct Thread_Info {
	int pthread_id;
	pthread_status status;
};

struct ThreadPool {
	pthread_info* pthreads;
	int pthread_admin;
	int min;
	int max;
	int current;
	struct TaskList* list;
};

	void* funtionLoop (void*); //recibe el tasklist 



#endif
