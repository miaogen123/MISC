/*************************************************************************
    > File Name: shm.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 03:26:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<errno.h>
#include<string.h>
 
#define SIZE 1024

int main(void)
{
	int  shmid;
	char *shmaddr;
	struct shmid_ds buf;
	int flag=0;
	int pid;
	shmid=shmget(IPC_PRIVATE, SIZE , IPC_CREAT|0600);
	if(shmid<0)
	{
		perror("get shm ipc_id error\n");
		exit(1);
	}
	pid=fork();
	if(pid==0)
	{
		shmaddr=(char*)shmat(shmid, NULL, 0);
		if((int)shmaddr==-1)
		{
			perror("shmat addr error\n");
			exit(1);
		}
		strcpy(shmaddr, "hi , i am child process\n");
		shmdt(shmaddr);
		exit(1);
	}
	else if(pid>0)
	{
		sleep(3);
		flag=shmctl(shmid, IPC_STAT, &buf);
		if(flag==-1)
		{
			perror("shmctl shm error\n");
			exit(1);
		}
		printf("shm_segsz=%d bytes\n", buf.shm_segsz);
		printf("parent pid=%d, shm_cpid=%d\n", getpid(), buf.shm_cpid);
		printf("chid pid=%d, shm_lpid=%d \n", pid, buf.shm_lpid);
		shmaddr=(char*)shmat(shmid, NULL, 0);
		if((int )shmaddr==-1)
		{
			perror("shmat addr error\n");
			exit(1);
		}
		printf("%s", shmaddr);
		shmdt(shmaddr);
		shmctl(shmid, IPC_RMID, NULL);
	}
	else{
		perror("fork error\n");
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}
