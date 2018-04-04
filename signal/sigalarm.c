/*************************************************************************
    > File Name: sigalarm.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 04:36:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pwd.h>
#include<signal.h>
#include<errno.h>
static void func(int signo)
{
	struct passwd *rootptr;
	if((rootptr=getpwnam("root"))==NULL)
	{
		perror("getpwnam error\n");
	}
	signal(SIGALRM , func);
	alarm(1);
}
int main(void)
{
	struct passwd *ptr;
	signal(SIGALRM, func);
	for(;;)
	{
		if(ptr=getpwnam("sar")==NULL)
		{
			perror("getpwnam error\n");
		}
	}
	return 0;
}
