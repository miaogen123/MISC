/*************************************************************************
    > File Name: sem.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 02:38:00 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>

union semun
{
	int val;		//the value of setval
	struct semid_ds *buf; // IPC_STAT, IPC_SET -buffer
	unsigned short *array;//GETALL, SETALL -array
	struct semiofo *__buf;// IPC_INFO buffer
};
int Opreation_P(int semid, int semnum)
{
	struct sembuf sops={semnum, -1, SEM_UNDO};
	return (semop(semid, &sops, 1));
}
int Opreation_V(int semid, int semnum)
{
	struct sembuf sops={semnum, +1, SEM_UNDO };
	return (semop(semid, &sops, 1));
}
int main(int argc, char **argv)
{
	int key;
	int semid, ret;
	union semun arg;
	int flag;
	struct sembuf semop;
	key=ftok("/tmp",0x66 );
	if(key<0)	
	{
		perror("ftok key error\n");
		exit(1);
	}
	semid=semget(key, 3, IPC_CREAT|0600);
	if(semid==-1)
	{
		perror("create semget error\n");
		exit(1);
	}
	if(argc==1)
	{
		arg.val=1;
		ret=semctl(semid,0, SETVAL,arg );
		if(ret<0)	
		{
			perror("ctl sem eror\n");
			semctl(semid, 0, IPC_RMID, arg);
			exit(1);
		}
	}
	ret=semctl(semid, 0, GETALL, arg);
	printf(" after semctl setval sem[0].val=[%d]\n", ret);
	system("date");
	printf("P operate begin\n");
	flag=Opreation_P(semid ,0);
	if(flag)
	{
		perror("P operate error\n");
		exit(1);
	}
	printf("PO operate over \n");
	ret=semctl(semid, 0, GETVAL, arg);
	printf("after P sem[0].val=[%d]\n", ret);
	system("date");
	if(argc==1)
	{
		sleep(120);
	}
	printf("V Opreation begin\n");
	if(Opreation_V(semid, 0)<0)
	{
		perror("Voperation error\n");
		exit(1);
	}
	printf("v Opreation over\n");
	ret=semctl(semid, 0, GETVAL, arg);
	printf("after v sem[0].val=%d\n", ret);
	system("date");
	if(argc>1)
	{
		semctl(semid, 0, IPC_RMID, arg);
	}
	return 0;
}
