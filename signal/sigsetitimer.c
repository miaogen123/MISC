/*************************************************************************
    > File Name: sigsetitimer.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Sun 14 May 2017 05:28:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
#include<stdlib.h>
static void DealTime(int signo)
{
	struct timeval tp;
	struct tm *tm;
	gettimeofday(&tp, NULL);
//	tm=localtime(&tp.tv_sec);
//	printf("sec=%ld \t ", tp.tv_sec);
//	printf("usec=%ld \t", tp.tv_sec);
	printf("%d-%d-%d%d:%d:%d:%d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}
static void InitTime(int tv_sec, int tv_usec)
{
	struct itimerval value;
	signal(SIGALRM, DealTime);
	value.it_value.tv_sec=tv_sec;
	value.it_value.tv_usec=tv_usec;
	value.it_interval.tv_sec=tv_sec;
	value.it_interval.tv_usec=tv_usec;
	setitimer(ITIMER_REAL, &value, NULL);
}
int main (void)
{
	InitTime(1, 0);
	while(1)
	{

	}
	exit(0);
}
