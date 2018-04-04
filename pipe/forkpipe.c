/*************************************************************************
  > File Name: forkpipe.c
  > Author :miaogen miaogen
  > Mail: miaogen_work.163.com 
  > Created Time: Mon 15 May 2017 10:58:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#define BUFSIZE 8192
int main(void )
{
	int n, fd[2];
	pid_t pid;
	char buffer[BUFSIZE];
	if(pipe(fd)<0)
	{
		perror("pipe failed\n");
		exit(0);	
	}
	if((pid=fork())<0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(pid>0)
	{
		close(fd[0]);
		write(fd[1], "this is pipe test \n", 22);
				}
				else
				{
				close(fd[1]);
				n=read(fd[0], buffer, BUFSIZE);
				write(STDOUT_FILENO, buffer, n);
				}
				exit(0);
				}
