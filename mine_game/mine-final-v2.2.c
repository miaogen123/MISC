//������linux��ʵ���ַ�ɨ�ף��������
#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<termio.h>
#include <sys/ioctl.h>
#include<curses.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MATRIX 16           //����ɨ�׵�������
#define MINIMUN 9           //������С��ɨ�׽���
//�жϣ�x��y���Ƿ��ھ����ڲ�
#define JUDGE(x,y)  ((x)>-1&&(x)<MATRIX&&(y)>-1&&(y)<MATRIX?TRUE:FALSE)
int matrix;  //ȫ�ֱ���������¼�û�������
#define JUDGEMINE(x, y) ((mine[x][y])==20?'A':mine[x][y])
// �����Ļ
#define CLEAR() printf("\033[2J")
// ���ƹ��
#define MOVEUP(x) printf("\033[%dA", (x))
// ���ƹ��
#define MOVEDOWN(x) printf("\033[%dB", (x))
// ���ƹ��
#define MOVELEFT(y) printf("\033[%dD", (y))
// ���ƹ��
#define MOVERIGHT(y) printf("\033[%dC",(y))
// ��긴λ
#define RESET_CURSOR() printf("\033[H")
//xianshi 
#define SHOW_CURSOR() printf("\033[?25h")
//���ڲ�����꣬ �������س�����    ��������  ����ֵ����������ļ��� acsii��
int scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	in = getchar();
	tcsetattr(0,ICANON,&stored_settings);
	return in;
}
//��ʼ������ɲ��� ���� ����ֵ ��
void InitializeMine(int mine[MATRIX][MATRIX])
{
    //����ı����ֱ�������¼ �н� �н� Ӧ���׵����� ����������� ʵ�ʵ�����Ŀ
    int countone=0, countsec=0,amount=0,randnum=0, minenum=0;
    amount=(matrix-9)*5+10;
    while(minenum!=amount)          //ֱ���������㹻���׺�ֹͣѭ��
    {
        for(countone=0;countone<matrix;countone++)
        {
            for(countsec=0;countsec<matrix;countsec++)
            {
                randnum=rand()%8+19;//20����
                if(mine[countone][countsec]==20)
                {
                  continue;
                }
                else if(randnum==20 )
                {
                    if(minenum==amount)
                    {
                        mine[countone][countsec]=randnum-1;
                    }
                    else
                    {
                        mine[countone][countsec]=randnum;
                        minenum++;
                    }
                }
                else
                {
                  mine[countone][countsec] = randnum;
                }
              }
          }
    }
	//����ѭ�����������ҳ���Ӧ�������ܵ��׵���Ŀ
	for (countone = 0; countone<matrix; countone++)
	{
		for (countsec = 0; countsec<matrix; countsec++)
		{
			minenum = 0;
			if (mine[countone][countsec] != 20)         //ͨ���ж��ҳ����ĸ���Χ������
			{
				if (JUDGE(countone - 1, countsec - 1))
				{
					if (mine[countone-1][countsec-1] == 20)
						minenum++;
				}
				if (JUDGE(countone - 1, countsec))
				{
					if (mine[countone - 1][countsec] == 20)
						minenum++;
				}
				if (JUDGE(countone - 1, countsec + 1) )
				{
					if (mine[countone - 1][countsec + 1] == 20)
						minenum++;
				}
				if (JUDGE(countone, countsec - 1))
				{
					if (mine[countone][countsec - 1]==20)
						minenum++;
				}
				if (JUDGE(countone, countsec + 1))
				{
					if (mine[countone][countsec + 1] == 20)
						minenum++;
				}
				if (JUDGE(countone + 1, countsec - 1))
				{
					if (mine[countone + 1][countsec - 1] == 20)
						minenum++;
				}
				if (JUDGE(countone + 1, countsec))
				{
					if (mine[countone + 1][countsec] == 20)
						minenum++;
				}
				if (JUDGE(countone + 1, countsec + 1))
				{
					if (mine[countone + 1][countsec + 1] == 20)
						minenum++;
				}
				mine[countone][countsec] = minenum;         //���ĸ��ϼ�¼��Χ������
			}
		}
	}
}
//FUNC����ʾ��ʼ������ ����:�� ����ֵ����
void Initialize(void)
{
  int countone=0, countsec=0;
  for(countone=0;countone<matrix;countone++)
    {
        for(countsec=0;countsec<matrix;countsec++)
        {
              printf("#   ");
        }
        if(countsec==matrix)
        {
            printf("%d", countone+1);
            printf("\n");
        }
    }
    for(countone=1;countone<=matrix;countone++)
    {
      if(countone<10)
      {
              printf("%d   ", countone);
      }
      else
      {
        printf("%d  ", countone);
      }
    }
    printf("\n");
}


//����ƶ�����  ���������� ����ֵ����
void MoveCursor(int row ,int col) {
  RESET_CURSOR();
  if(row==1)
    {
      if(col==1)
      {
        return ;
      }
      else
      {
        MOVERIGHT(4*(col-1));
      }
    }
    else
    {
      MOVEDOWN(row-1);
      if(col==1)
      {
        return ;
      }
      else
      {
        MOVERIGHT(4*(col-1));
      }
    }
}
//��ʾ���   ��������Ļ�ϵ�����  �Լ���־ 1��0 ����ֵ����
void Sub_MoveCursor(int row ,int col, int flag)//flag���������� ��1ʱ��ʾ��� ��0ʱ�ػ���Ļ
{
  RESET_CURSOR();
  if(row==1)
    {
      if(col==1)
      {
		  MOVERIGHT(1);
      }
      else
      {
        MOVERIGHT(4*(col-1)+1);
      }
    }
    else
    {
      MOVEDOWN(row-1);
      if(col==1)
      {
		  MOVERIGHT(1);
      }
      else
      {
        MOVERIGHT(4*(col-1)+1);
      }
    }
	if(flag==1)
	{
		printf("\033[44;34;1m|\033[40;30;0m" );
	}
	else if(flag==0)
	{
		printf(" ");
	}
}
//�ױ����� ��ʾ���е��� �������ը��Ч  �������� ���أ���
void BomMine(int mine[MATRIX][MATRIX])
{
      struct winsize ws;
      ioctl(0, TIOCGWINSZ, &ws);
      int countone=0, countsec=0;
      for(countone=0;countone<matrix;countone++)
      {
        for(countsec=0;countsec<matrix;countsec++)
        {
              if(mine[countone][countsec]==20)
              {
                  MoveCursor(countone+1, countsec+1);
                  printf("\033[40;31;1mMN\033[40;30;0m" );
              }
          }
      }
      fflush(stdout);
      sleep(3);
      RESET_CURSOR();
      for(countone=0;countone<matrix+10;countone++)
      {
          for(countsec=0;countsec<(int)ws.ws_col;++countsec)
          {
            printf(" ");
          }
          printf("\n");
          usleep(40000);
      }
      sleep(1);
      CLEAR();
      RESET_CURSOR();
      printf("       ***********            ***********                   \n");
      printf("     ***********            ***********                    \n");
      printf("    ****                  ****                          \n");
      printf("   ***                   ***                           \n");
      printf("   ***       **           ***       **                  \n");
      printf("    ****    ****            ****    ****                   \n");
      printf("     ******   ***             ******   ***                 \n");
      exit(1);
}

//������ҳ����е���Χ���׵ĸ��Ӳ���ʾΪ��   �������У��У��׵����飬 ��־����
void Set_Blank(int row, int col, int mine[MATRIX][MATRIX], int flag[MATRIX][MATRIX])
{
  if(mine[row][col]>0)
  {
    MoveCursor(row+1, col+1);
    flag[row][col]=1;
    printf("\033[40;32;1m%d \033[40;30;0m" , mine[row][col]);
    return ;
  }
  else if(mine[row][col]==-1)
  {
    return ;
  }
  else if(mine[row][col]==0)
  {
    MoveCursor(row+1,  col+1);
    flag[row][col]=1;
    fprintf(stdout, " ");
    mine[row][col]=-1;
    if(row==0&&col==0)
    {
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if(row==0&&(col>0&&col<matrix-1))
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row, col+1, mine, flag);
      Set_Blank(row+1, col, mine, flag);
    }
    if(row==0&&col==matrix-1)
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row+1, col, mine, flag);
    }
    if((row<matrix-1&&row>0)&&col==0)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if((row<matrix-1&&row>0)&&(col>0&&col<matrix-1))
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
      Set_Blank(row, col-1, mine, flag);
    }
    if((row<matrix-1&&row>0)&&col==matrix-1)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col-1, mine, flag);
    }
    if(row==matrix-1&&col==0)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if(row==matrix-1&&(col>0&&col<matrix-1))
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if(row==matrix-1&&col==matrix-1)
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row-1, col, mine, flag);
    }
  }
}
//��ʾĳλ�õ����ݣ����׾�ը���Դ˸���Ϊ���ĵľŹ��������ף�����ʾ�׵���Ŀ��û������ʾ�����Ŀհ�  
//���� ���󣬱�־���飬 ����
void DisplayCursor(int mine[MATRIX][MATRIX], int flag[MATRIX][MATRIX],  int row, int col)
{
    if(mine[row-1][col-1]==20)
    {
      BomMine(mine);
    }
    else if(mine[row-1][col-1]!=0)
    {
      MoveCursor(row, col);
      flag[row-1][col-1]=1;
      printf("\033[40;32;1m%d \033[40;30;0m", mine[row-1][col-1]);
    }
    else// diguibianlikongge MINE[row-1][col-1]==0
    {
        Set_Blank(row-1,  col-1, mine, flag);
    }
}
//��ʾyouwin   ��������ֵ��
void YouWin(void)
{

  CLEAR();
  RESET_CURSOR();
  printf(" ***       ***      ***     @        *** *******           *****                 \n");
  printf("  ***     ** **    ***      ****    ****    ***           ****               \n");
  printf("   ***   ***  ***  ***      ****     ***    ***            ***               \n");
  printf("     ****      ****        ****     ***    ***            @            \n");
  exit(1);
}
//��Ϸ��ں���   ��������ֵ����
void StartGame()
{
    int count=0;
    int row=1, col=1;
    char tempchar, state;
    int mineremain=0, true_mineremain=0;
	pthread_t tid;
    int mine[MATRIX][MATRIX]={0};
    int flag[MATRIX][MATRIX]={0};
    int minenumber=0;
    srand((unsigned long)time(0));
    printf("please input the dimension of the matrix(9~16)\n");
    while(scanf("%d", &matrix)!=1||(matrix>MATRIX||matrix<MINIMUN))
    {
        printf("input error , please iput agein\n");
        while((tempchar=getchar())!='\n'&&tempchar!=EOF);
    }
    printf("please wait a monment.....\n");
    CLEAR();
    RESET_CURSOR();
    InitializeMine(mine);
    sleep(1);
    mineremain=(matrix-9)*5+10;
    true_mineremain=mineremain;
    Initialize();
    printf("mineremain=%d     \n", mineremain  );
	count=0;
	int err=0;
    while(1)
    {
		/*err=pthread_creat(&tid, NULL, (void*)getch, NULL);*/
		/*if(err==0)*/
		/*{*/
			/*printf("pthread create error, prggram adbort\n");*/
			/*return 0;*/
		/*}*/
		state=(char)scanKeyboard();
		printf("...i\n");
		if(count!=1)
		{
			Sub_MoveCursor(row, col, 0);
		}
		count++;
		if(state=='I')
		{
			if(row==1)
			{
				row=matrix;
				Sub_MoveCursor(row, col, 1);
			}
			else
			{
				row--;
				Sub_MoveCursor(row, col, 1);
			}
		}
		else if(state=='K')
		{
			if(row==matrix)
			{
				row=1;
				Sub_MoveCursor(row, col, 1);
			}
			else
			{
				row++;
				Sub_MoveCursor(row, col, 1);
			}
		}
		else if(state=='J') 
		{
			if(col==1)
			{
				col=matrix;
				Sub_MoveCursor(row, col, 1);
			}
			else
			{
				col--;
				Sub_MoveCursor(row, col, 1);
			}

		}
		else if(state=='L')
		{
			if(col==matrix)
			{
				col=1;
				Sub_MoveCursor(row, col, 1);
			}
			else
			{
				col++;
				Sub_MoveCursor(row, col, 1);
			}
		}
        else if(state=='A')
        {
          if(flag[row-1][col-1]!=1&&flag[row-1][col-1]!=2)
          {
            DisplayCursor(mine, flag, row, col);
          }
          if(flag[row-1][col-1]==2)
          {
            DisplayCursor(mine, flag, row, col);
			mineremain++;
			RESET_CURSOR();
            MoveCursor(matrix+2, 1);
            printf("mineremain=%d     \n", mineremain  );

          }
        }
        else if(state=='B')
        {
          if(flag[row-1][col-1]!=1&&flag[row-1][col-1]!=2)
          {
            MoveCursor(row,col);
            printf("\033[40;31;1m@\033[40;30;0m");
            flag[row-1][col-1]=2;
            mineremain--;
            RESET_CURSOR();
            MoveCursor(matrix+2, 1);
            printf("mineremain=%d     \n", mineremain  );
            if(mine[row-1][col-1]==20)
            {
              true_mineremain--;
			  if(true_mineremain==0)
			  {
				  YouWin();
			  }
            }
          }
		}
        RESET_CURSOR();
		MOVEDOWN(matrix+2);
    }
}
int main(void)
{
	
	printf("wel come to the game\n");
	printf("attention: this game use \"I K J L\" to move up or down or left or right\n");
	printf("use A to implement mouse left click,  use B to implement mouse right click\n");
	StartGame();
    return 0;
}
