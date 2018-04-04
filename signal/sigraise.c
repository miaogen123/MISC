/*************************************************************************
    > File Name: sigraise.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 05:08:34 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
void inthandler(int signum);
void continuehandler(int signum);
void terminatehandler(int signum);
int main(void)
{
	char buffer[100];
	if((int )(signal(SIGINT, &inthandler))==-1)
	{
		exit(1);
	}
	if((int)signal(SIGTSTP, &inthandler)==-1)
	{
		exit(2);
	}
	if((int) signal(SIGCONT, &continuehandler)==-1)
	{
		exit(3);
	}
	if((int)(signal(SIGTERM, &terminatehandler))==-1)
	{
		exit(4);
	}
	printf("pid of this porcess:%d \n", getpid());
	while(1)
	{
		printf("input\n");
		fgets(buffer, sizeof(buffer), stdin);
		if(strcmp(buffer, "int\n")==0)
		{
			raise(SIGINT);
		}
		else if(strcmp(buffer, "stop\n")==0)
		{
			raise(SIGTSTP);
		}
		else if(strcmp(buffer, "continue\n")==0)
		{
			raise(SIGCONT);
		}
		else if(strcmp(buffer, "quit\n")==0)
		{
			raise (SIGTERM);
		}
		else
		{
			printf("your input is %s\n", buffer);
		}
	}
		exit(0);
}
void inthandler(int signum)
{
	printf("catch sigal %d\n", signum);
}
void continuehandler(int signum)
{
	printf("continue code\n");
}
void terminatehandler(int signum )
{
	printf("signal SIGTERM\n");
	exit(0);
}
