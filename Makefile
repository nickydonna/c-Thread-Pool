CC = gcc
CFLAGS = -pedantic -Wall
LIBS = -pthread
LUUID = -luuid

test_pthread_pool: pthread_pool.c task_queue.c return_list.c priority_list.c task_list.c test_pthread_pool.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_pthread_pool

test_task_queue: task_queue.c test_task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_task_queue

test_return_list: return_list.c test_return_list.c task_list.c priority_list.c task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_return_list

test_priority_list: priority_list.c test_priority_list.c task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_priority_list

test_task_list: task_list.c test_task_list.c priority_list.c task_queue.c return_list.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_task_list

test_all_the_things: pthread_pool.c task_queue.c return_list.c priority_list.c task_list.c task_queue.c main.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LUUID)
	./test_all_the_things

test: test_task_queue test_return_list test_priority_list
	./test_task_queue
	./test_return_list
	./test_priority_list
	./test_task_list
	./test_pthread_pool
	

