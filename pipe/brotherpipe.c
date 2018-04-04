/*************************************************************************
    > File Name: brotherpipe.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 06:43:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<limits.h>
#include<string.h>
#include<errno.h>
#define BUFFSIZE 8192
int main(void)
{
	int fd[2];
	char buf[BUFFSIZE]="hello! i am your brother\n";
	pid_t pid;
	int len;
	if((pipe(fd))<0)
	{
		perror("pipe failed\n");
	}
	if((pid=fork())<0)
	{
		perror("fork failed\n");
	}
	else if(pid==0)
	{
		close(fd[0]);
		write(fd[1],  "kdsjfasjfkasjflkjasklfjklasjfkl\n", strlen(buf));
		exit(0);
	}
	if(pid=fork()<0)
	{
		perror("fork failed\n");
	}
	else if(pid>0)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else 
	{
		close(fd[1]);
		len=read(fd[0], buf, BUFFSIZE);
		write(STDOUT_FILENO, buf, len);
		close(fd[0]);
	}
	return 0;
}
