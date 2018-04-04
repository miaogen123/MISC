/*************************************************************************
    > File Name: alarm.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 07:52:45 PM CST
 ************************************************************************/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#define MAXLINE 1024
static void sigalrm(int);
int main(void)
{
	int n;
	char line[MAXLINE];
	if(signal(SIGALRM, sigalrm)==SIG_ERR)
	{
		perror("SIGALRM error\n");	
	}
	alarm(10);
	if(n==read(STDIN_FILENO, line, MAXLINE)<0)
	{
		perror("read error");
	}
	alarm(0);
	write(STDOUT_FILENO, line, n);
	exit(0);
}
static void sigalrm(int signo)
{
	
}
