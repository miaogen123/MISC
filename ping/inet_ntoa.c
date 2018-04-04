/*************************************************************************
    > File Name: inet_ntoa.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Thu 31 Aug 2017 09:39:05 AM CST
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

int main(void)
{
	struct in_addr addr1, addr2;
	char * str1, *str2;
	char buf[20];
	addr1.s_addr=htonl(0x1020304);
	str1=inet_ntoa(addr1);
	memcpy(buf, str1, sizeof(str1));
	addr2.s_addr=htonl(0xc0a80101);
	str2=inet_ntoa(addr2);
	printf("%#lx -> %s\n", (long)addr1.s_addr, buf);
	printf("%#lx -> %s\n", (long)addr2.s_addr, str2);
	return 0;

}
