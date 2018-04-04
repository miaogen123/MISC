#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
void *func(void *arg)
{
  int i=*(int *)(arg);
  printf("worker:%d\n", i);
}
int main(void )
{
  pthread_t tid;
  int j;
  int count=1000;
  for(j=0;j<count;j++)
  {
    int *p=&(j);
    int ret=pthread_create(&tid, NULL, func , (void *)p);
    if(ret)
    {
      printf("create error \n");
    }
    else
    {
      int p=j;
      printf("the value of count is :%d\n", p);
      pthread_detach(tid);
      printf("the value of count is :%d\n", p);
    }
  }
  return 0;
}
