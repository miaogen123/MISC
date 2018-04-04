/*************************************************************************
    > File Name: pthreadodata.c
    > Author :miaogen octopus
    > Mail: octopus_work.163.com 
    > Created Time: Sun 07 May 2017 11:49:34 AM CST
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
void *my_thread(void*arg)
{
	int retval=0;
	pthread_attr_t attr;
	struct sched_param param;
	size_t	stacksize;
	int		detachstate;
	int		scope;
	int		inherit;
	int		policy;
	if(pthread_attr_init(&attr)==0)
	{
		if(pthread_attr_getstacksize(&attr, &stacksize)==0)
		{
			printf("stacksize:%d\n", stacksize);
		}
		if(pthread_attr_getdetachstate(&attr, &detachstate)==0)
		{
			if(detachstate==PTHREAD_CREATE_JOINABLE)
			{
				printf("DetachState : PTHREAD_CREADTE_JOINABLE\n");
			}
			if(detachstate==PTHREAD_CREATE_DETACHED)
			{
				printf("detachstate :PTHREAD_CREATE_DETACHED\n");
			}
		}
		if(pthread_attr_getscope(&attr, &scope)==0)
		{
			if(scope==PTHREAD_SCOPE_PROCESS)
			{
				printf("Scope: PTHREAD_SCOPE_PROCESS\n");
			}
			if(scope==PTHREAD_SCOPE_SYSTEM)
			{
				printf("Scope: PTHREAD_SCOPE_SYSTEM\n");
			}
		}
		if(pthread_attr_getinheritsched(&attr, &inherit)==0)
		{
			if(inherit==PTHREAD_INHERIT_SCHED)
			{
				printf("inheritsched: PTHREAD_INHERIT_SCHED\n");
			}
			if(inherit==PTHREAD_EXPLICIT_SCHED)
			{
				printf("inheirtsched: PTHREAD_EXPLICIT_SCHED\n");
			}
			
		}
		if(pthread_attr_getschedpolicy(&attr, &policy)==0)
		{
			if(policy==SCHED_FIFO)
			{
				printf("SCHED_FIFO: SCHED_FIFO\n");
			}
			if(policy==SCHED_RR)
			{
				printf("schedpolicy: SCHED_RR\n");
			}
			else 
			{
				printf("schedPolicy: SCHED_OTHER\n");
			}
			if(pthread_attr_getschedparam(&attr, &param)==0)
			{
				printf("schedpriority: %d\n", param.sched_priority);
			}
			pthread_attr_destroy(&attr);
		}
		pthread_exit(&retval);
	}
}
int main(void)
{
	int			count;
	pthread_t	thread;
	int			*retval;
	if(pthread_create(&thread, NULL, my_thread, (void*) NULL)!=0)
	{
		printf("count not create threaddddddd!\n");
		return -1;

	}
	if(pthread_join(thread, (void **)(&retval))!=0)
	{
		printf("no thread to join\n");
		return -2;
	}
	return 0;


}
