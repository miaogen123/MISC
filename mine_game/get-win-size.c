#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
void main(void)
{
   struct winsize ws;
   ioctl(0, TIOCGWINSZ, &ws);
    sleep(3);
   int i=0;
   for(;i<ws.ws_col;++i) printf("=");
   printf("\n");
   printf("%d", ws.ws_col);
   return 0;
}
