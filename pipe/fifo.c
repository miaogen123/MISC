/*************************************************************************
    > File Name: fifo.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 08:28:50 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<linux/stat.h>
#include<errno.h>
#include<fcntl.h>
#define FIFO "FIFO2" 
int main(void) 
{
	pid_t pid;
	int fd_r, fd_w;
	int num_r, num_w;
	int len=40;
	char buf_r[len];
	char buf_w[len];
	if((mkfifo(FIFO,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
	{
		perror("create fifo fail\n");
		exit(1);
	}
	if((pid=fork())==0)
	{
		sleep(1);
		printf("process %s :ready to open fifo ", getpid());
		fd_r=open(FIFO, O_RDONLY, 0);
		if(fd_r==-1)
		{
			printf("process %d :open error\n", getpid());
			return ;
		}
		printf("process %d open successfully\n", getpid());
		while(1)
		{
			num_r=read(fd_r, buf_r, sizeof(buf_r));
			printf("read %d kb\n", num_r);
			sleep(1);
		}
	}
	else
	{
		printf("process %d read to open fifo\n", getpid());
		fd_w=open(FIFO, O_WRONLY, 0);
		if(fd_w==-1)
		{
			printf("process %d :open fifo error\n", getpid());
			exit(1);
		}
		printf("process %d :open fifo successfully\n", getpid());
		while(1)
		{
			num_w=write(fd_w, buf_w, sizeof(buf_w));
			printf("write %d kb \n", num_w);
		}
	}
}
