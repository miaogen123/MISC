/*************************************************************************
    > File Name: inetaddr.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Thu 31 Aug 2017 09:32:28 AM CST
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>

int main(void)
{
	char *addr1="1.2.3.4";
	char *addr2="192.168.1.1";
	in_addr_t data;
	
	data=inet_addr(addr1);
	printf("%s-> %#lx \n", addr1, (long)data);
	data=inet_addr(addr2);
	printf("%s-> %#lx \n", addr2, (long)data);

	return 0;
}
