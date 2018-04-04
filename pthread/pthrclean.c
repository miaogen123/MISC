#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
void* clean(void *arg)
{
  printf("clean %s \n", (char *)arg);
  return  (void *)0;
}
void *thr_fn1(void *arg)
{
  printf("thread1 start\n");
  pthread_cleanup_push((void *)clean, "thread 1 first hanndler");
  pthread_cleanup_push((void*)clean, "thread 1 second handler");
  if(arg)
  {
    return ((void*)1);
  }
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void*)1);
}
void *thr_fn2(void *arg)
{
  printf("thread2 start\n");
  pthread_cleanup_push((void *)clean, "thread 2 first hanndler");
  pthread_cleanup_push((void*)clean, "thread 2 second handler");
  if(arg)
  {
    return ((void*)2);
  }
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return (void*)1;
}
int main(int argc, char *argv[])
{
  int err;
  pthread_t tid1, tid2;
  void *tret;
  err=pthread_create(&tid1, NULL, thr_fn1, (void *)1);
  if(err!=0)
  {
    perror("create pthread error\n");
    return -1;
  }
  err=pthread_create(&tid2, NULL, thr_fn2, (void*)1);
  if(err!=0)
  {
    perror("create pthread 2 error \n");
    return -1;
  }
  err=pthread_join(tid1, &tret);
  if(err!=0)
  {
    perror("join tid1 error\n");
    return -1;
  }
  printf("tid1 exit code %d\n", (int )tret);
  err=pthread_join(&tid2, &tret);
  if(err!=0)
  {
    perror("join tid2 error\n");
    return -1;
  }
  printf("tid2 exitcode %d\n", (int)tret);
  return 0;
}
