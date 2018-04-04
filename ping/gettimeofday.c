/*************************************************************************
    > File Name: gettimeofday.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Thu 31 Aug 2017 09:11:42 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>


float timediff(struct timeval *begin, struct timeval *end)
{
	int n;
	n=(end->tv_sec-begin->tv_sec)*100000+(end->tv_usec-begin->tv_usec);
	return (float)(n/1000);
}

int main(void)
{
	struct timeval begin, end;
	gettimeofday(&begin, 0);
	printf("calm down ,calm down , i'm trying\n");
	printf("calm down ,calm down , i'm trying\n");
	printf("calm down ,calm down , i'm trying\n");
	printf("calm down ,calm down , i'm trying\n");
	printf("calm down ,calm down , i'm trying\n");
	usleep(1000);
	gettimeofday(&end, 0);
	printf("running time is:%fms\n ", timediff(&begin, &end));
	return 0;
}
