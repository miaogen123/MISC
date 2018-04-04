#include<stdio.h>
#include<pthread.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
//#if 0
//char *str_accumulate(char *s)
//{
//  static cahr accu[1024]={0};
//  strcat(accu, s);
//  return accu;
//}
//#endif // 0
static pthread_key_t str_key;
static pthread_once_t str_alloc_key_once=PTHREAD_ONCE_INIT;
static void str_alloc_key();
static void str_alloc_destroy_accu(void *accu);
char *str_accumulate(const char *s)
{
  char *accu;
  pthread_once(&str_alloc_key_once, str_alloc_key);
  accu=(char *)pthread_getspecific(str_key);
  if(accu==NULL)
  {
    accu=malloc(1024);
    if(accu==NULL)
      return NULL;
    accu[0]=0;
    pthread_setspecific(str_key, (void *)accu);
    printf("Thread %lx: allocating buffer at %p\n", pthread_self(), accu);

  }
  strcat(accu, s);
}
static void str_alloc_destory_accu(void *accu)
{
  printf("Thread %lx : freeing buffer at %p\n", pthread_self(), accu );
  free(accu);
}
static void str_alloc_key()
{
  pthread_key_create(&str_key, str_alloc_destory_accu);
  printf("Thread %lx: allocated key%d\n", pthread_self(), str_key);
}

void *process(void *arg)
{
  char *str;
  str=str_accumulate("result of");
  str=str_accumulate((char *)arg);
  str=str_accumulate("thread");
  printf("Thread %lx: \"%s\" \n", pthread_self(), str);
  return NULL;
}
int main(int argc, char *argv[])
{
  char *str;
  pthread_t tid1, tid2;
  str=str_accumulate("result of");
  pthread_create(&tid1, NULL, process, (void*)"first");
  pthread_create(&tid2, NULL, process, (void *)"second");
  str=str_accumulate("initial thread");
  printf("Thread %lx:\"%s\"\n", pthread_self(), str);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  return 0;
}
