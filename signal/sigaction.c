/*************************************************************************
    > File Name: sigaction.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 04:04:45 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
void signalDeal(int signum);
int main(void)
{
	char buffer1[100], buffer2[100];
	int i;
	struct sigaction act;
	act.sa_handler=signalDeal;
	act.sa_flags=0;
	if((int)sigaction(SIGTERM, &act ,NULL)==-1)
	{
		perror("could not  register this signal handler\n");
		return 1;
	}
	printf("pid of this sprocess s %d \n", getpid());
	while(1)	
	{
		printf("input \n");
		fgets(buffer1, sizeof(buffer1), stdin);
		for(i=0;i<100;i++)
		{
			if(buffer1[i]>=97&&buffer1[i]<=122)
			{

			buffer2[i]=buffer1[i]-32;
		}
		else
		{

			buffer2[i]=buffer1[i];
		}
		}
		printf("our input is %s", buffer2);
	}
	eixt(0);
	
}
void signalDeal(int signum)
{
	printf(" catch signal SIGTERM\n");
	exit(0);
}
