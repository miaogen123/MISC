//程序在linux下
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
//judge the number of mines that surround "x"
#define JUDGE(x,y)  ((x)>-1&&(x)<16&&(y)>-1&&(y)<16?TRUE:FALSE)
int matrix;
#define JUDGEMINE(x, y) ((mine[x][y])==20?'A':mine[x][y])
// 清除屏幕
#define CLEAR() printf("\033[2J")
// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))
// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))
// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))
// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
// 光标复位
#define RESET_CURSOR() printf("\033[H")
// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")
//反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")
//初始化，完成布雷 参数 返回值 空
void InitializeMine(int mine[16][16], int matrix)
{
    int countone=0, countsec=0,amount=0,randnum=0, minenum=0;
    amount=(matrix-9)*5+10;
    while(minenum!=amount)
    {
        for(countone=0;countone<matrix;countone++)
        {
            for(countsec=0;countsec<matrix;countsec++)
            {
                randnum=rand()%8+19;//20有雷
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
	//进行循环遍历，查找出对应雷区四周的雷的数目
	for (countone = 0; countone<matrix; countone++)
	{
		for (countsec = 0; countsec<matrix; countsec++)
		{
			minenum = 0;
			if (mine[countone][countsec] != 20)
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
				mine[countone][countsec] = minenum;
			}
		}
	}
}
//FUNC:print the first eye picture  RETURN: void PARAMETER: matrix
void Initialize(int matrix)
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


//对雷进行遍历，记录每个雷的数值#参数为二维数组#返回值为二维数组的指针

//int *** GetMine(int mine[16][16])



////雷的检测  参数：行，列，状态（模拟左右键） 二维数组的指针  返回值：字符  表示雷的状态
//A means click blank, B means right click

//char JudgeMine(int row, int col, int mine[16][16])

//{
//  if(mine[row][col]==20)
//  {
//    return TRUE;
//  }
//  if(mine)
//
//}

//显示雷  参数：行，列， 状态, 二维数组的指针  返回值：空
//void DisplayMine(int row ,int col, char state , int mine[][12]);
//雷被引爆 显示所有的雷 并输出爆炸特效  参数：无 返回：空
void BomMine(int mine[16][16])
{
      int countone=0, countsec=0;
      for(countone=0;countone<matrix;countone++)
      {
        for(countsec=0;countsec<matrix;countsec++)
        {
              if(mine[countone][countsec]==20)
              {
                  MoveCursor(countone+1, countsec+1);
                  printf("\033[40;31;1mMN\033[40;30;0m" );
                  usleep(100000);
              }
          }
      }
      RESET_CURSOR();
      for(countone=0;countone<matrix;countone++)
      {

          printf("                           ");
          printf("                           ");
          printf("                           ");
          usleep(200000);

        printf("\n");
      }
      printf("                                          ");
      printf("                                          ");
      printf("\n");
      printf("       ***********|            ***********|                   \n");
      printf("     ***********|             ***********|                    \n");
      printf("    ****                  ****                          \n");
      printf("   ***                   ***                           \n");
      printf("   ***       **           ***       **                  \n");
      printf("    ****    ****            ****    ****                   \n");
      printf("     ******   ***             ******   ***                 \n");
      exit(1);
}

//show the blank of the matrix  Argument : center row ,center col Return:void
void Set_Blank(int row, int col, int mine[16][16], int flag[16][16])
{
  if(mine[row][col]>0)
  {
    MoveCursor(row+1, col+1);
    flag[row][col]=1;
    printf("\033[40;32;1m%d \033[40;30;0m" , mine[row][col]);
    return 0;
  }
  else if(mine[row][col]==-1)
  {
    return 0;
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
    if(row==0&&(col>0&&col<15))
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row, col+1, mine, flag);
      Set_Blank(row+1, col, mine, flag);
    }
    if(row==0&&col==15)
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row+1, col, mine, flag);
    }
    if((row<15&&row>0)&&col==0)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if((row<15&&row>0)&&(col>0&&col<15))
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
      Set_Blank(row, col-1, mine, flag);
    }
    if((row<15&&row>0)&&col==15)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row+1, col, mine, flag);
      Set_Blank(row, col-1, mine, flag);
    }
    if(row==15&&col==0)
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if(row==15&&(col>0&&col<15))
    {
      Set_Blank(row-1, col, mine, flag);
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row, col+1, mine, flag);
    }
    if(row==15&&col==15)
    {
      Set_Blank(row, col-1, mine, flag);
      Set_Blank(row-1, col, mine, flag);
    }
  }
}
//move cursor to the specific position  Argument: row and col
void MoveCursor(int row ,int col)
{
  RESET_CURSOR();
  if(row==1)
    {
      if(col==1)
      {
        return 0;
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
        return 0;
      }
      else
      {
        MOVERIGHT(4*(col-1));
      }
    }
}
//display the cursor and replace the "#" with number
void DisplayCursor(int mine[16][16], int flag[16][16],  int row, int col)
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
        Set_Blank(row-1, col-1, mine, flag);
    }
}
int main(void)
{
    int countone=0, countsec=0,count=0;
    int row=0, col=0;
    matrix=16;
    char tempchar;
    char state;
    srand((unsigned long)time(0));
//    printf("欢迎进入游戏\n");
//    printf("请输入你想玩的雷的阶数（9~16）\n");
    /*while(scanf("%d", &matrix)!=1)
    {
        printf("输入错误请重新输入\n");
        while((tempchar=getchar())!='\n'&&tempchar!=EOF);
    while(matrix>16||matrix<9)
    {
        printf("输入错误，请重新输入9~16之间的数字\n");
        while((tempchar=getchar())!='\n'&&tempchar!=EOF);
        scanf("%d", &matrix);
    }*/
    int mine[16][16]={0};
    int flag[16][16]={0};
    int minenumber=0;
    InitializeMine(mine, matrix);
    sleep(3);
    Initialize(matrix);
    // output the mine code inside the comment
    for(countone=0;countone<matrix;countone++)
    {
        for(countsec=0;countsec<matrix;countsec++)
        {
            printf("%d\t", mine[countone][countsec]);
        }
        if(countsec==matrix)
        {
            printf("\n");
        }
    }
    while(1)
    {
        printf("please input the row and col \n");
        while(scanf("%d%d", &row, &col)!=2)
        {
            printf("输入错误请重新输入\n");
            while((tempchar=getchar())!='\n'&&tempchar!=EOF);
        }
        while(row<0||row>matrix)
        {
            printf("hang输入错误，请重新输入9~16之间的数字\n");
            while((tempchar=getchar())!='\n'&&tempchar!=EOF);
            while(scanf("%d", &row )!=1)
            {
                printf("输入错误请重新输入\n");
                while((tempchar=getchar())!='\n'&&tempchar!=EOF);
            }
        }
        while(col<0||col>matrix)
        {
            printf("lie输入错误，请重新输入9~16之间的数字\n");
            while((tempchar=getchar())!='\n'&&tempchar!=EOF);
            while(scanf("%d", &col)!=1)
            {
                printf("输入错误请重新输入\n");
                while((tempchar=getchar())!='\n'&&tempchar!=EOF);
            }
        }
        printf("%d %d\n", row, col);
        printf("please input state(A means click, B means right click)");
        while((tempchar=getchar())!='\n'&&tempchar!=EOF);
        while(scanf("%c", &state)!=1)
        {
          printf("input state error, please input again\n");
          while((tempchar=getchar())!='\n'&&tempchar!=EOF);
        }

        while((state!='A')&&(state!='B'))
        {
          printf("please input A or B\n");
          while((tempchar=getchar())!='\n'&&tempchar!=EOF);
          while(scanf("%c", &state)!=1)
          {
            printf("input state error, please input again\n");
            while((tempchar=getchar())!='\n'&&tempchar!=EOF);
          }
        }
        RESET_CURSOR();
        if(state=='A')
        {
          if(flag[row-1][col-1]!=1)
          {
            DisplayCursor(mine, flag, row, col);
          }
        }
        if(state='B')
        {
          if(flag[row-1][col-1]!=1&&flag[row-1][col-1]!=2)
          {
            MoveCursor(row,col);
            printf("\033[40;31;1m@\033[40;30;0m");
            flag[row-1][col-1]=2;
          }
        }
        RESET_CURSOR();
        MOVEDOWN(matrix+1);
//        for(count=0;count<10;count++)
//        {
//          printf("                                               \n");
//        }
        RESET_CURSOR();
        MOVEDOWN(matrix+1);
//        for(countone=0;countone<matrix;countone++)
//          {
//              for(countsec=0;countsec<matrix;countsec++)
//              {
//                  printf("%d\t", mine[countone][countsec]);
//              }
//              if(countsec==matrix)
//              {
//                  printf("\n");
//              }
//          }
          for(countone=0;countone<matrix;countone++)
          {
              for(countsec=0;countsec<matrix;countsec++)
              {
                  printf("%d\t", flag[countone][countsec]);
              }
              if(countsec==matrix)
              {
                  printf("\n");
              }
          }
    }
    return 0;
}

