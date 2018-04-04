/*************************************************************************
    > File Name: ownpipe.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Mon 15 May 2017 10:43:07 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
int main(void)
{
	int fd[2];
	char str[256];
	if(pipe(fd)<0)
	{
		perror("create the pipe error\n");
		exit(0);
	}
	write(fd[1], "create the pipe successfully!", 31);
	read(fd[0], str, sizeof(str));
	printf("%s", str);
	printf("pipe file id are %d , %d",fd[0], fd[1]);
	close(fd[0]);
	close(4);
	return 0;

	
}
