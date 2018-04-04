/*************************************************************************
    > File Name: sigkill1.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 04:46:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
int main(void)
{
	pid_t pid;
	int status;
	if(!(pid=fork()))
	{
		printf(" child process\n");
		sleep(10);
		printf(" child process\n");
		return 0;
	}
	else{
		printf("send signal to child process (%d)\n", pid);
		sleep(1);
		if(kill(pid, SIGABRT)==-1)
		{
			perror("kill failed\n");

		}
		wait(&status);
		if(WIFSIGNALED(status))
		{
			printf("child process receive signal %d\n", WTERMSIG(status));
		}
	}
	return 0;
}
