/*************************************************************************
    > File Name: ftok.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Wed 17 May 2017 08:24:49 AM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
int main(int argc, char **argv)
{
	struct stat stat1;
	if(argc!=2)
	{
		printf("usage :ftok<pathname>\n");
		exit(1);
	}
	stat(argv[1], &stat1);
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,\
			(unsigned long)stat1.st_ino, ftok(argv[1], 0x579));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,\
		(unsigned long)stat1.st_ino, ftok(argv[1], 0x118));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,\
		(unsigned long)stat1.st_ino, ftok(argv[1], 0x22));
	printf("st_dev:%lx, st_ino:%lx, key:%x\n", (unsigned long)stat1.st_dev,\
		(unsigned long)stat1.st_ino, ftok(argv[1], 0x33));
	exit(0);
}
