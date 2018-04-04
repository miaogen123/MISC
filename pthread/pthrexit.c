#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stddef.h>
void printf_message(char* ptr)
{
  int retval;
  printf("thread ID: %lx\n", pthread_self());
  printf("%s\n", ptr);
  pthread_exit(&retval);
}
int main(int argc, char *argv[])
{
  pthread_t thread1, thread2;
  char *m1="the first\n";
  char *m2="the second\n";
  pthread_create(&thread1, NULL, (void *)(&printf_message), (void *)m1);
  pthread_create(&thread2, NULL, (void *)(&printf_message), (void*)m2);
  sleep(1);
  return 0;
}
