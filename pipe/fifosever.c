/*************************************************************************
    > File Name: fifosever.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 09:23:58 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<linux/stat.h>
#include<errno.h>
#define FIFO_FILE "MYFIFO"
int main(void)
{
	FILE *fp;
	char readbuf[80];
	if((fp=fopen(FIFO_FILE, "r"))==NULL)
	{
		umask(0);
		mknod(FIFO_FILE, S_IFIFO|0666, 0);
	}
	else 
	{
		fclose(fp);
	}
	while(1)
	{
		if((fp=fopen(FIFO_FILE, "r"))==NULL)
		{
			printf("open fifo failed\n");
			exit(1);
		}
		if(fgets(readbuf, 80, fp)!=NULL)
		{
			printf("recevied string %s\n", readbuf);
			fclose(fp);
		}
		else{
			if(ferror(fp))
			{
				perror("read fifo failed\n");
				exit(1);
			}
		}
	}
	return 0;
}
