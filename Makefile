SHELL =  /bin/sh

.SUFFIXIES:
.SUFFIXIES: .o .c

CC = gcc
CFLAGS = -pedantic -Wall
CTESTF = -w
LIBS = -pthread
LUUID = -luuid

all: pthread_pool.o task_list.o return_list.o priority_list.o task_queue.o
	ar rcs libphthreadpool.a $^
pthread_pool.o: pthread_pool.c
	$(CC) $(CFLAGS) $(LIBS) -c $^

task_list.o: task_list.c
	$(CC) $(CFLAGS) $(LIBS) -c $^

return_list.o: return_list.c
	$(CC) $(CFLAGS) $(LIBS) -c $^

priority_list.o: priority_list.c
	$(CC) $(CFLAGS) $(LIBS) -c $^

task_queue.o: task_queue.c
	$(CC) $(CFLAGS) $(LIBS) -c $^

clean:
	rm -f *.o *.a *.sh

test_task_queue: test_task_queue.c task_queue.o
	$(CC) $(CTESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh

test_priority_list: test_priority_list.c priority_list.o task_queue.o
	$(CC) $(CTESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh

test_return_list: test_return_list.c return_list.o task_list.o task_queue.o priority_list.o
	$(CC) $(CTESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh	

test_task_list: test_task_list.c task_list.o task_queue.o priority_list.o return_list.o
	$(CC) $(CTESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh

test_pthread_pool: test_pthread_pool.c task_list.o task_queue.o priority_list.o return_list.o pthread_pool.o
	$(CC) $(CTESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh

test_all: clean test_task_queue test_priority_list test_return_list test_task_queue test_pthread_pool

test_all_the_things: main.c task_list.o task_queue.o priority_list.o return_list.o pthread_pool.o
	$(CC) $(TESTF) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh
