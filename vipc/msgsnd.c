/*************************************************************************
    > File Name: msgsnd.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 11:22:18 AM CST
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
int main (void )
{
	int runningFlg=1;
	int msgid;
	msgid=msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid==-1)
	{
		perror("msgget failed!\n");
		exit(1);
	}
	while(runningFlg==1)
	{
		printf("input the string\n");
		fgets(msgbuf.text, BUFSIZ, stdin);
		msgbuf.my_msg_type=1;
		if(msgsnd(msgid, (void*)&msgbuf, BUFSIZ, 0)==-1)
		{
			perror("magsnd failed\n");
			exit(1);
		}
		if(strncmp(msgbuf.text, "end", 3)==0)
		{
			runningFlg=0;
		}
	}
	return 0;
}
