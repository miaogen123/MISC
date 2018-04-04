/*************************************************************************
    > File Name: sigkill2.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 04:58:21 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
int main (void)
{
	pid_t child;
	int status, retval;
	child=fork();
	if(child<0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(child==0)
	{
		sleep(1000);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		if((waitpid(child, &status, WNOHANG))==0)
		{
			retval=kill(child, SIGKILL);

		}
		if(retval)
		{
			puts("kill failed\n");
			perror("kill");
			waitpid(child, &status, 0);
		}
		else 
		{
			printf("%d killed \n", child);
		}
	}
	exit(EXIT_SUCCESS);
}
