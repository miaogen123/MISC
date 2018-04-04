/*************************************************************************
    > File Name: pipemore.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 07:03:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<limits.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>
#define DEF_PAGER "/bin/more"
#define MAXLINE 4096
int main(int argc, char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char *pager, *argv0;
	char line[MAXLINE];
	FILE *fp;
	if(argc!=2)
	{
		perror("usage: <pathname>=\n");
		exit(1);
	}
	if((fp=fopen(argv[1], "r"))==NULL)
	{
		printf("can't open %s", argv[1]);
		exit(1);
	}
	if(pipe(fd)<0)
	{
		perror(" pipe error\n");
		exit(0);
	}
	if((pid=fork())<0)
	{
		perror("fork error\n");
		exit(0);
	}
	else if(pid>0)
	{
		close(fd[0]);
		while(fgets(line, MAXLINE, fp)!=NULL)
		{
			n=strlen(line);
			if(write(fd[1], line, n)!=n)
			{
				perror("write error to piep \n");
				exit(1);
			}
		}
		if(ferror(fp))
		{
			perror("fgets error\n");
			exit(1);
		}
		close(fd[1]);
		if(waitpid(pid, NULL, 0)<0)
		{
			perror("waitpid error");
			exit(1);
		}
		exit(0);
	}
	else 
	{
		close(fd[1]);
		if(fd[0]!=STDIN_FILENO)
		{
			if(dup2(fd[0], STDIN_FILENO)!=STDIN_FILENO)
			{
				perror("dup2 error to stdin\n");
				exit(1);
			}
			close (fd[0]);
		}
		if((pager=getenv("PAGER"))==NULL)
		{
			pager=DEF_PAGER;
		}
		if((argv0=strrchr(pager, '/'))!=NULL)
		{
			argv0++;
		}
		else
		{
			argv0=pager;
		}
		if(execl(pager, argv0, (char*)0)<0)
		{
			printf("execl error for %s", pager);
			exit(1);
		}
	}
	exit(0);

}
