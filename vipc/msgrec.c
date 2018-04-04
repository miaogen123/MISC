/*************************************************************************
    > File Name: msgrec.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 11:38:24 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
#include<errno.h>
struct my_msg
{
	long int my_msg_type;
	char text[BUFSIZ];
}msgbuf;
int main(void)
{
	int runningFlg=1;
	int msgid;
	long int msg_to_receive=0;
	msgid=msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid==-1)
	{
		printf("msgget error\n");
		exit(1);
	}
	printf("i enter the while\n");
	while(runningFlg==1)
	{
		printf("i enter the while\n");
		if(msgrcv(msgid, (void*)&msgbuf, BUFSIZ, msg_to_receive, 0)==-1)
		{
			perror("msgrcv failed\n");
			exit(1);
		}
		printf("string received is %s\n", msgbuf.text);
		if(strncmp(msgbuf.text, "end", 3)==0)
			runningFlg=0;
	}
	if(msgctl(msgid, IPC_RMID, 0)==-1)
	{
		perror("msggct(IPC_RMID, failed\n");
		exit(1);
	}
	return 0;
}
