#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stddef.h>
void printf_message(char* ptr)
{
  int i;
  for(i=0;i<10;i++)
    printf("%s\n", ptr);

}
int main(int argc, char *argv[])
{
  pthread_t thread1, thread2;
  void *retval;
  char *m1="the first\n";
  char *m2="the second\n";
  pthread_create(&thread1, NULL, (void *)(&printf_message), (void *)m1);
  pthread_create(&thread2, NULL, (void *)(&printf_message), (void*)m2);
  pthread_join(thread1, &retval);
  printf("%d\n", retval);
  pthread_join(thread2, &retval);
  printf("%d\n", retval);
  sleep(1);
  return 0;
}
