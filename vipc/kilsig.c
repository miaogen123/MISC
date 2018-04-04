/*************************************************************************
    > File Name: kilsig.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 02:32:51 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
int main(void)
{
	system("ipcs -m");
	shmctl(2457613, IPC_RMID, NULL);
	system("ipcs -m");
	return 0;	
}
