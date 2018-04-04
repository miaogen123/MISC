/*************************************************************************
    > File Name: printfmem.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 04:30:14 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>

#define ARRAY_SIZE 4000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600
char array[ARRAY_SIZE];
int main(void)
{
	int shmid;
	char *ptr, *shmptr;
	printf("array[] from %lx to %lx \n", (unsigned long)&array[0], (unsigned long)&array[ARRAY_SIZE]);
	printf("stack around %lx\n", (unsigned long)&shmid);
	if((ptr=malloc(MALLOC_SIZE))==NULL)
	{
		perror("malloc error\n");
	}
	printf("malloced from %lx to %lx \n", (unsigned long)ptr, (unsigned long)ptr+MALLOC_SIZE);
	if((shmid=shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE))<0)
	{
		perror("shmget eoror	\n");

	}
	if(shmptr=shmat(shmid, 0, 0)==(void*)-1)
	{
		perror("shmat error\n");
	}
	printf("shared memory attach ed form %lx to %lx\n", (unsigned long )shmptr, (unsigned long)shmptr+SHM_SIZE);
	if(shmctl(shmid, IPC_RMID, 0))
	{
		perror("shmctl errro\n");
	}
	exit(0);
}
