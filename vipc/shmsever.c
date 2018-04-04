/*************************************************************************
    > File Name: shmsever.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 04:01:33 PM CST
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
	if(shmid=shmget(1234, 256, IPC_CREAT|0666))
	{
		perror("shmget error\n");
		exit(1);
	}
	if((shmptr=(char *)shmat(shmid, 0, 0))==-1)
	{
		shmctl(shmid, IPC_RMID, (struct shmid_ds*)shmptr);
		perror("shmat failed\n");
		exit(1);
	}
	s=shmptr;
	for(c='a';c<='z';c++)
	{
		*s++=c;
	}
	*s=NULL;
	while(*shmptr!='*')
	{
		sleep(1);
	}
	shmctl(shmid, IPC_RMID, (struct shmid_ds*)shmptr);
	return 0;
}
