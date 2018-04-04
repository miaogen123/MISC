/*************************************************************************
    > File Name: pthreadsyn1.c
    > Author :miaogen octopus
    > Mail: octopus_work.163.com 
    > Created Time: Wed 10 May 2017 10:58:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
void* readfun();
void* writefun();
char buffer[256];
int buffer_has_item=0;
int retflag=FALSE;
pthread_mutex_t mutex;
int main(void )
{
	pthread_t reader;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&reader, NULL, readfun, NULL);
	writefun();
	exit(0);

}
void* readfun()
{
	while(1)
	{
		if(retflag)
		{
			return NULL;
		}
		pthread_mutex_lock(&mutex);
		if(buffer_has_item==1)
		{
			printf("llllll\n");
			printf("%s", buffer);
			sleep(1);	
			buffer_has_item=0;
		}
		pthread_mutex_unlock(&mutex);
	}
	
		return NULL;
}
void* writefun(void)
{
	int i=0;
	while(1)
	{
		printf("dkdkdkd\n");
		if(i==10)
		{
			retflag=TRUE;
			return NULL;
		}
		pthread_mutex_lock(&mutex);
		if(buffer_has_item==0)
		{
			sprintf(buffer, "this is %d\n", i);
			i++;
			buffer_has_item=1;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return NULL;
}
