/*************************************************************************
    > File Name: msgctl.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Wed 17 May 2017 01:03:24 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/msg.h>
#include<errno.h>
#include<string.h>


#define TEXT_SIZE 512
 struct msgbuf{
	long mtype;
	char mtext[TEXT_SIZE];
 };
int main(int argc, char **argv)
{
	int msqid;
	struct msqid_ds info;
	struct msgbuf buf;
	struct msgbuf buf2;
	int flag;
	int sendlength, recvlength;
	msqid=msgget(IPC_PRIVATE, 0666);
	if(msqid<0)
	{
		perror("get ipc_id error\n");
		exit(1);
	}
	buf.mtype=1;
	strcpy(buf.mtext, "this is test\n");
	sendlength=sizeof(struct msgbuf)-sizeof(long);
	flag=msgsnd(msqid, &buf, sendlength, 0);
	if(flag<0)
	{
		perror("snd error\n");
		exit(1);
	}
	buf.mtype=3;
	strcpy(buf.mtext, "this is a antther test!\n");
	sendlength=sizeof(struct msgbuf)-sizeof(long);
	flag=msgsnd(msqid, &buf, sendlength,0 );
	if(flag<0)
	{
		perror("send message error 2\n");
		exit(1);
	}
	printf("uid:%d, gid=%d"", cuid=%d, dgid=%d, \n",\
			info.msg_perm.uid, info.msg_perm.gid, info.msg_perm.cuid, info.msg_perm.cgid);
	printf("read-write: %03o, cbytes=%lu, qnum=%lu, qbytes=%lu\n", \
			info.msg_perm.mode, info.msg_cbytes, info.msg_qnum, info.msg_qbytes);
	system("ipcs -q");
	recvlength=sizeof(struct msgbuf)-sizeof(long);
	memset(&buf, 0x00, sizeof(struct msgbuf));
	flag=msgrcv(msqid, &buf2, recvlength, 3, 0);
	if(flag<0)
	{
		perror("rec error \n");
		exit(1);
	}
	printf("type=%d, contect=%s\n", buf.mtype, buf.mtext);
	flag=msgctl(msqid, IPC_RMID, NULL);
	if(flag<0)
	{
		perror("rm ipc error\n");
		exit(1);
	}
	system("ipcs -q");
	return 0;
}
