3)EQUAL THREAD:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
pthread_t tmp_thread;
void* func_one(void* ptr)
{
	if (pthread_equal(tmp_thread, pthread_self())) {
		printf("equal\n");
	} else {
		printf("not equal\n");
	}
}
int main()
{
	pthread_t thread_one;
	tmp_thread = thread_one;
	pthread_create(&thread_one, NULL, func_one, NULL);
	pthread_join(thread_one, NULL);
}
