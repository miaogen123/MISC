/*************************************************************************
    > File Name: fifoclient.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 09:37:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define FIFO_FILE "MYFIFO"
int main(int argc, char *argv[])
{
	FILE *fp;
	int i;
	if(argc<=1)
	{
		printf("usage:%s <pathname>\n", argv[0]);
		exit(1);
	}
	if((fp=fopen(FIFO_FILE, "w"))==NULL)
	{
		printf("open file error \n");
		exit(1);
	}
	for(i=1;i<argc;i++)
	{
		if(fputs(argv[i], fp)==EOF)
		{
			printf("write fifo error\n");
			exit(1);
		}
		if(fputs("", fp)==EOF)
		{
			printf("write fifo ERROR\n");
			exit(1);
		}
	}
	fclose(fp);
	return 0;

}
