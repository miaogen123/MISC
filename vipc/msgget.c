/*************************************************************************
    > File Name: msgget.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 11:08:46 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<errno.h>
int main(void)
{
	key_t key;
	int msqid;
	printf("enter the desire key in hex=\n");
	scanf("%x", &key);
	printf("\nkey=0x%x", key);
	if((msqid=msgget(key, IPC_CREAT|0660))==-1)
	{
		perror("the msgget failed \n");
		exit(1);
	}
	printf("the msgget successfully :msaid=%d\n", msqid);
	exit(0);
}
