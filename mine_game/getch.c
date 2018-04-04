/*************************************************************************
    > File Name: getch.c
    > Author :miaogen
    > Mail: miaogen156@outlook.com 
    > Created Time: Sun 04 Jun 2017 11:47:57 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<curses.h>
int main (void)
{
	char temp;
	initscr();
	temp=getch();
	printf("\byou have inputed the char %c\n" ,temp);
	temp=getch();
	printf("\byou have inputed the char %c\n" ,temp);
	endwin();
	return 0;
}
