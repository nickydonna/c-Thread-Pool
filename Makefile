CC = gcc
CFLAGS = -pedantic -Wall 
LIBS = -pthread

test_task_queue: task_queue.c test_task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
	./test_task_queue

test_return_list: return_list.c test_return_list.c task_list.c
	$(CC) $(LIBS) -o $@ $^
	./test_return_list

test_priority_list: priority_list.c test_priority_list.c task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
	./test_priority_list

test: test_task_queue test_return_list test_priority_list


