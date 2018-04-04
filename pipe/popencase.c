/*************************************************************************
    > File Name: popencase.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 08:04:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char*argv[])
{
	char  buffer[BUFSIZ+1];
	FILE *fpin, *fpout;
	if(argc<=1)
	{
		printf("usage:%s <pathname>\n");
		exit(1);
	}
	if((fpin=fopen(argv[1], "r"))==NULL)
	{
		printf("can't open %s \n", argv[1]);
		exit(1);
	}
	if((fpout=popen("./upcase", "w"))==NULL)
	{
		perror("popen error\n");
		exit(1);
	}
	while(fgets(buffer, BUFSIZ, fpin)!=NULL)
	{
		if(fputs(buffer, fpout)==EOF)
		{
			perror("fputs error to pipe. \n");
			exit(1);
		}
		if(ferror(fpin))
		{
			perror("fgets error\n");
			exit(1);
		}
		if(pclose(fpout)==-1)
		{
			printf("close error\n");
			exit(1);
		}
	}
	exit(0);
}
