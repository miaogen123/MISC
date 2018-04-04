#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
void* thread_func(void *arg)
{
  int *val=arg;
  printf("i'm a pthread\n");
  if(NULL!=arg)
  {
    while(1)
      printf("%d\n", *val);
  }
}
int main(int argc, char *argv[])
{
  pthread_t tid;
  int t_arg=10;
  if(pthread_create(&tid, NULL, thread_func, &t_arg))
  {
    perror("pthread create error");
  }
  sleep(1);
  printf("main thread !\n");
  pthread_cancel(tid);
  return 0;
}
