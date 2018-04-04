/*************************************************************************
    > File Name: shmget.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 03:16:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<errno.h>

#define BUFSIZE 4096
 int main(void)
{
	int shm_id;
	shm_id=shmget(IPC_PRIVATE, BUFSIZE, 0666);
	if(shm_id<0)
	{
		perror("shmget error\n");
		exit(1);
	}
	printf("create a shared memory segment successfully: %d \n", shm_id);
	system("ipcs -m");
	shmctl(shm_id, IPC_RMID, NULL);
	system("ipcs -m");
	return 0;
}
