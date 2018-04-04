/*************************************************************************
    > File Name: sigout.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 02:37:23 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
void signalDeal(int iSignNum)
{
	printf("the signal NO.is :%d  \n", iSignNum);
	return NULL;
}
int main(void)
{

	signal(SIGINT, signalDeal);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
