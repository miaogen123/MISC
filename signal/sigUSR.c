/*************************************************************************
    > File Name: sigUSR.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 03:34:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<errno.h>
static void sigDeal(int);
int main(void )
{
	if(signal(SIGUSR1, sigDeal)==SIG_ERR)
	{
		perror("can't catch SIGUSR1\n");
	}
	if(signal(SIGUSR2, sigDeal)==SIG_ERR)
	{
		perror("can't catch SIGUSR2\n");
	}
	printf("pid of this process :%d\n", getpid());
	while(1)
	{
		pause();
	}
}
static void sigDeal(int signo)
{
	if(signo==SIGUSR1)
	{
		printf("received SIGUSR1\n");
	}
	else if(signo==SIGUSR2)
	{
		printf("received SIGUSR2\n");
	}
	else 
	{
		printf("received signal%d \n");
	}
}
