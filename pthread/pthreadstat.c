/*************************************************************************
    > File Name: pthreadstat.c
    > Author: octopus
    > Mail: octopus_work.163.com 
    > Created Time: Sun 07 May 2017 08:16:27 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#if 0
char *str_acGGcumulate(char *s)
{
	static char accu[1024]={0};
	strcat(accu,s);
	return 0;
}
#endif
static pthread_key_t str_key;
static pthread_once_t str_alloc_key_once=PTHREAD_ONCE_INIT;
static void str_alloc_key();
static void str_alloc_destroy_accu(void *accu);
char *str_accumulate(const char *s)
{
	char *accu;
	pthread_once(&str_alloc_key_once, str_alloc_key);
	accu=(char *) pthread_getspecific(str_key);
	if(accu=NULL)
	{
		accu=(char*)malloc(1024);
		if(accu=NULL)
		{
			return NULL;
		}
		accu[0]=0;
		pthread_setspecific(str_key, (void *)accu);
		printf("pthread %lx:allocting bffer at %p\n", pthread_self(), accu);
	}
	strcat(accu,s);
	return accu;
}
static void str_alloc_key(void)
{
	pthread_key_create(&str_key, str_alloc_destroy_accu);
	printf("Thread %lx allocated key %d \n", pthread_self, str_key);
}
static void str_alloc_destroy_accu(void *accu)
{
	printf("Thread %lx: freeing buffer at %p\n");
	free(accu);
}
void *process(void *arg)
{
	char *str;
	str=str_accumulate("result of ");
	str=str_accumulate((char *)arg);
	str=str_accumulate("thread");
	printf("THread %lx:\"%s\" \n", pthread_self(), str);
	return NULL;
}
int main(int argc, char* argv[])
{
	char *str;
	pthread_t th1, th2;
	str=str_accumulate("result of");
	pthread_create(&th1, NULL, process, (void *)"first");
	pthread_create(&th2, NULL, process, (void *)"second");
	str=str_accumulate("initial thread");
	printf("Thread %lx:  %s \n ", pthread_self(), str);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	return 0;
}
