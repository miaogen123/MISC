/*************************************************************************
    > File Name: sigthree.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 02:48:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void intfunc(int signum);
void exitfunc(int signum);
int main()
{
	char buffer1[100], buffer2[100];
	int i;
	if((int)(signal(SIGINT, intfunc))==-1)
	{
		printf("couldn't register handler for SIGINT\n");
		exit(1);
	}
	if((int)signal(SIGTSTP, intfunc)==-1)
	{
		printf("couldn't register handler for SIGTSTP\n");
		exit(1);
	}
	if((int)signal(SIGTERM, exitfunc)==-1)
	{
		printf("couldn't register handler for SIGTERM\n");
		exit(1);
	}
	printf("pid of this process %d\n",getpid());
	while(1)
	{
		printf("input please \n");
		fgets(buffer1, sizeof(buffer1), stdin);
		for(i=0;i<100;i++)
		{
			if(buffer1[i]>=97&&buffer1[i]<=122)
			{
				buffer2[i]=buffer1[i]-32;
			}
			else 
			{
				buffer2[i]=buffer1[i];
			}
		}
		printf("your input is %s \n", buffer2);
	}
	exit(0);
}

	void intfunc(int signum)
	{
		printf("catch signal %d\n", signum);
	}
	void exitfunc(int signum)
	{
		printf("signal SIGTERM\n");
		exit(0);
	}
