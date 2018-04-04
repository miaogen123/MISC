/*************************************************************************
    > File Name: gethostbyname.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Thu 31 Aug 2017 10:05:34 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(int argc, char *argv[])
{
	int i;
	struct hostent *host;
	if(argc<2)
	{
		printf("usage:%s <hostname> ", argv[0]);
		exit(1);
	}
	printf("before\n");
	host=gethostbyname(argv[1]);
	printf("after\n");
	for(i=0;host->h_addr_list[i];i++)
	{
		printf("IP addr %d: %s \n", i+1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	}
	return 0;
}
