/*************************************************************************
    > File Name: mkfifo.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 08:20:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	mode_t mode=0666;
	if(argc!=2)
	{
		printf("USEMSG:Create_FIFO, <FIFO name>\n");
		exit(1);
	}
	if((mkfifo(argv[1], mode))<0)
	{
		perror("falied to mkfifo\n");
		exit(1);
	}
	else{
		printf("successful c_FIFO %s", argv[1]);
	}
	return 0;
}
