#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Fix Variable
#define yFrame_T 1
#define xFrame_L 1
#define MAX_Y 24
#define MAX_X 80
#define kEsc 27
#define kEnter 13
#define kUp 72
#define kDown 80
#define kLeft 75
#define kRight 77

//function
void gotoxy(int, int);
void Frame();
void CheckKey(int);
void print_snake(int);
void walking_snake();
void move_posxy_snake();
void add_len_snake();
void random_food();
void print_food();
int collision_check();

//global variable
struct pos_xy {
	int x;
	int y;
};
struct pos_xy pos[1920];
int len_snake = 1, Fs = 0, Rs = 0;
int food_x = 0, food_y = 0;
char walking = 'L';

//main
int main()
{
	system("cls");
	int KeyHit;
	srand(time(NULL));
	
	Regame:
	system("cls");
	//set variables
	pos[0].x = 40;
	pos[0].y = 12;
	int i;
	len_snake = 1, Fs = 0, Rs = 0;
	random_food();
	gotoxy(30, 10);
	printf("Enter to Start game");
	if((KeyHit = getch()) != kEnter)
	{
		goto Regame;
	}
	
	//loop game
	do{
		CheckKey(KeyHit);
		while(kbhit() == 0)
		{
			system("cls");
			print_food();
			walking_snake();
			for(i = 0;i < len_snake;i++)
			{
				print_snake(i);
			}
			Frame();
			Sleep(100);
			
			if((pos[Fs].x == food_x) && (pos[Fs].y == food_y))
			{
				add_len_snake();
			}
			
			if((pos[Fs].x >= MAX_X) || (pos[Fs].y >= MAX_Y) || (pos[Fs].x <= xFrame_L) || (pos[Fs].y <= yFrame_T) || collision_check())           
			{
				system("cls");
				gotoxy(35, 10);
				printf("! you lose !");
				gotoxy(35, 12);
				printf("score : %d", len_snake);
				if(KeyHit = getch())
				{
					goto Regame;
				}
			}           
		}
	}while((KeyHit = getch()) != kEsc);
	
	return 0;
}

//gotoxy
void gotoxy(int x, int y)
{
	printf("\033[%d;%dH",y ,x);
}

//Frame
void Frame()
{
	int i;
	
	for(i=xFrame_L;i <= MAX_X;i++)
	{
		gotoxy(i, yFrame_T);
		printf("#");
		gotoxy(i, MAX_Y);
		printf("#");
	}
	for(i=yFrame_T;i <= MAX_Y;i++)
	{
		gotoxy(xFrame_L, i);
		printf("#");
		gotoxy(MAX_X, i);
		printf("#");
	}
}

//CheckKey
void CheckKey(int rKey)
{
	if(rKey == kUp)
	{
		if((pos[Fs].x != pos[Fs+1].x) && ((pos[Fs].y-1) != pos[Fs+1].y))
		{
			walking = 'U';
		}
	}
	if(rKey == kDown)
	{
		if((pos[Fs].x != pos[Fs+1].x) && ((pos[Fs].y+1) != pos[Fs+1].y))
		{
			walking = 'D';
		}
	}
	if(rKey == kLeft)
	{
		if(((pos[Fs].x-1) != pos[Fs+1].x) && ((pos[Fs].y) != pos[Fs+1].y))
		{
			walking = 'L';
		}
	}
	if(rKey == kRight)
	{
		if(((pos[Fs].x+1) != pos[Fs+1].x) && ((pos[Fs].y) != pos[Fs+1].y))
		{
			walking = 'R';
		}
	}
}

// print_snake
void print_snake(int i)
{
	gotoxy(pos[i].x, pos[i].y);
	printf("O");
}

// walking_snake
void walking_snake()
{
	int x = 0;
	int y = 0;
	if(walking == 'U')
	{
		y = -1;
	}
	if(walking == 'D')
	{
		y = 1;
	}
	if(walking == 'L')
	{
		x = -1;
	}
	if(walking == 'R')
	{
		x = 1;
	}
	
	if(Fs == Rs)
	{
		pos[Fs].x += x;
		pos[Fs].y += y;
	}
	else
	{
		move_posxy_snake();
		pos[Fs].x += x;
		pos[Fs].y += y;
	}
}

//move_posxy_snake
void move_posxy_snake()
{
	struct pos_xy pos_copy[1920];
	int i;
	for(i = 0;i < len_snake;i++)
	{
		pos_copy[i] = pos[i];
	}
	for(i = 0;i < len_snake;i++)
	{
		pos[i+1] = pos_copy[i];
	}
}

// add_len_snake
void add_len_snake()
{
	random_food();
	len_snake += 1;
	Rs += 1;
	if(walking == 'U')
	{
		pos[Rs].x = pos[Rs - 1].x;
		pos[Rs].y = pos[Rs - 1].y + 1;
	}
	if(walking == 'D')
	{
		pos[Rs].x = pos[Rs - 1].x;
		pos[Rs].y = pos[Rs - 1].y - 1;
	}
	if(walking == 'L')
	{
		pos[Rs].x = pos[Rs - 1].x + 1;
		pos[Rs].y = pos[Rs - 1].y;
	}
	if(walking == 'U')
	{
		pos[Rs].x = pos[Rs - 1].x - 1;
		pos[Rs].y = pos[Rs - 1].y;
	}
}

//random_food
void random_food()
{
	int first = 2;
	int last = first + 2;
	food_x = first + int(rand() % (MAX_X - last));
	food_y = first + int(rand() % (MAX_Y - last));
}

//print_food
void print_food()
{
	gotoxy(food_x, food_y);
	printf("*");
}

//collision_check
int collision_check()
{
	int i;
	for(i = 1;i < len_snake; i++)
	{
		if((pos[Fs].x == pos[i].x) && (pos[Fs].y == pos[i].y))
		{
			return 1;
		}
	}
	return 0;
}








