/*************************************************************************
    > File Name: upcase.c
    > Author :miaogen miaogen
    > Mail: miaogen_work.163.com 
    > Created Time: Tue 16 May 2017 07:39:53 PM CST
 ************************************************************************/

#include<stdio.h>
int i;
char buffer1[100], buffer2[100];
int main(void)
{
	fgets(buffer1, sizeof(buffer1), stdin);
	for(i=0;i<100;i++)
	{
		if(buffer1[i]>=97&&buffer1[i]<=122)
		{
			buffer2[i]=buffer1[i]-32;
		}
		else{
			buffer2[i]=buffer1[i];
		}
	}
	printf("the str is :%s \n", buffer2);
	return 0;
}
