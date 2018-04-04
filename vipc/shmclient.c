/*************************************************************************
    > File Name: shmclient.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 04:14:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(void)
{
	int shmid;
	char c;
	char *shmptr, *s;
	if((shmid=shmget(1234, 256, 0666))<0)
	{
		perror("shmget failed\n");
		exit(1);
	}
	if((shmptr=shmat(shmid,0, 0))==-1)
	{
		shmctl(shmid, IPC_RMID, (struct shmid_ds*)shmptr);
		perror("shmat failed\n");
		exit(1);
	}
	for(s=shmptr;*s!=NULL;s++)
	{
		putchar(*s);
	}
	printf("\n");
	*shmptr='*';
	return 0;
}
