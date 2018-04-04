#include<time.h>
#include<stdio.h>
#include<pthread.h>
#define CLEAR() printf("\033[2J")
#define RESET_CURSOR() printf("\033[H")
// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
void CountTime(void)
{
	time_t counttime;
	while(1)
}
int main(int argc, char *argv[])
{
   time_t counttime;
  counttime=time(0);
  HIDE_CURSOR();
  while(1)
  {
    RESET_CURSOR();
    printf("\t");
    RESET_CURSOR();
    sleep(1);
    printf("%d" ,time(0)-counttime);
    fflush(stdout);
  }

}
