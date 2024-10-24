#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>  // For random number generation
#include <windows.h>

//---------------------------- Fix Variable ---------------------//
#define max_len_snake 1820
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

//---------------------------- Function declaration ---------------------//
void gotoxy(int, int);
void Frame();
void CheckKey(int);
void print_snake(int);
void walking_snake();
void save_posxy_snake();
void add_len_snake();
void random_point();
void print_point();
int collision_check();
void print_score();

//------------- Global Variables -----------
struct pos_xy {
	int x;
	int y;
};
struct pos_xy pos[max_len_snake];
int len_snake = 1, Fs = 0, Rs = 0;
int point_X = 0, point_Y = 0;
char walking = 'L';

//---------------------------- Main Function ---------------------//
int main()
{
	system("cls");
	int KeyHit;
	srand(time(NULL));

	Regame:
	system("cls");
	//Set variables
	pos[0].x = 40;
	pos[0].y = 12;
	int i;
	len_snake = 1, Fs = 0, Rs = 0;
	random_point();
	gotoxy(30, 10); 
	printf("Enter to start game");
	if((KeyHit = getch()) != kEnter)
	{
		goto Regame;
	}
	system("cls");
	Frame();

	do{
		CheckKey(KeyHit);		
		while(kbhit() == 0)
		{
			print_point();
			walking_snake();
			for(i = 0;i < len_snake;i++)
			{
				print_snake(i);
			}
			print_score();
			Sleep(100);

			if((pos[Fs].x == point_X) && (pos[Fs].y == point_Y))
			{
				add_len_snake();
			}

			if((pos[Fs].x >= MAX_X) || (pos[Fs].y >= MAX_Y) || (pos[Fs].x <= xFrame_L) || (pos[Fs].y <= yFrame_T) || collision_check())
			{
				Frame();
				system("cls");
				gotoxy(35, 10);
				printf("! you lose !");
				if(len_snake < 10)
				{
					gotoxy(37, 12);
				}
				else if(len_snake < 100)
				{
					gotoxy(36, 12);
				}
				else
				{
					gotoxy(35, 12);
				}
				printf("score : %d", len_snake);
				if(KeyHit = getch())
				{
					goto Regame;
				}
			}
			// key B or b
			if(KeyHit == 66 || KeyHit == 98)
			{
				do
				{
					gotoxy(30, 10); 
					printf("!-- Break Game --!");
					gotoxy(28, 12);
					printf("Please Enter to start!");
					KeyHit = getch();
				}while(KeyHit != kEnter);
				gotoxy(30, 10);
				printf("                  ");
				gotoxy(28, 12);
				printf("                      ");
				KeyHit = 0; //reset key
			}
		}
	}while((KeyHit = getch()) != kEsc);

	EndGame:
	return 0;
}

//------------- gotoxy -----------
void gotoxy(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

//------------- Frame -----------
void Frame()
{
	int i, j;

	for(i=xFrame_L;i <= MAX_X;i++)
	{
		gotoxy(i, yFrame_T); 
		printf("#");
		gotoxy(i,  MAX_Y); 
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

//------------- Check Key -----------
void CheckKey(int rKey)
{
	if(rKey == kUp || rKey == int('W') || rKey == int('w'))
	{
		if((pos[Fs].x != pos[Fs+1].x) && ((pos[Fs].y-1) != pos[Fs+1].y))
		{
			walking = 'U';
		}
	}
	if(rKey == kDown || rKey == int('S') || rKey == int('s'))
	{
		if((pos[Fs].x != pos[Fs+1].x) && ((pos[Fs].y+1) != pos[Fs+1].y))
		{
			walking = 'D';
		}
	}
	if(rKey == kLeft || rKey == int('A') || rKey == int('a'))
	{

		if(((pos[Fs].x-1) != pos[Fs+1].x) && (pos[Fs].y != pos[Fs+1].y))
		{
			walking = 'L';
		}
	}
	if(rKey == kRight || rKey == int('D') || rKey == int('d'))
	{
		if(((pos[Fs].x+1) != pos[Fs+1].x) && (pos[Fs].y != pos[Fs+1].y))
		{
			walking = 'R';
		}
	}
}

//------------- print snake -----------
void print_snake(int i)
{
	gotoxy(pos[i].x, pos[i].y);
	printf("O");
}

//------------- walking snake -----------
void walking_snake()
{
	int x = 0;
	int y = 0;
	switch (walking) {
        case 'U':
            y = -1;
            break;
        case 'D':
            y = 1;
            break;
        case 'L':
            x = -1;
            break;
        case 'R':
            x = 1;
            break;
	}

	if(Fs == Rs)
	{
		gotoxy(pos[Rs].x, pos[Rs].y); printf(" ");
		pos[Fs].x += x;
		pos[Fs].y += y;
	}
	else
	{
		save_posxy_snake();
		pos[Fs].x += x;
		pos[Fs].y += y;
	}
}

//------------- save posxy snake -----------
void save_posxy_snake()
{
	gotoxy(pos[Rs].x, pos[Rs].y); printf(" ");
	struct pos_xy pos_copy[max_len_snake];
	int i;
	for(i = 0;i < len_snake; i++)
	{
		pos_copy[i] = pos[i];
	}
	for(i = 0;i < len_snake; i++)
	{
		pos[i+1] = pos_copy[i];
	}
}

//------------- add len snake -----------
void add_len_snake()
{
	gotoxy(point_X, point_Y); printf(" ");
	random_point();
	len_snake += 1;
	Rs += 1;

	switch (walking) {
        case 'U':
		pos[Rs].x = pos[Rs - 1].x;
		pos[Rs].y = pos[Rs - 1].y + 1;
            break;
        case 'D':
		pos[Rs].x = pos[Rs - 1].x;
		pos[Rs].y = pos[Rs - 1].y - 1;
            break;
        case 'L':
		pos[Rs].x = pos[Rs - 1].x + 1;
		pos[Rs].y = pos[Rs - 1].y;
            break;
        case 'R':
		pos[Rs].x = pos[Rs - 1].x - 1;
		pos[Rs].y = pos[Rs - 1].y;
            break;
	}
}

//------------- random point -----------
void random_point()
{
	int first = 2;
	int last = first + 2;
	point_X = first + int(rand() % (MAX_X - last));
	point_Y = first + int(rand() % (MAX_Y - last));
}

//------------- print point -----------
void print_point()
{
	gotoxy(point_X, point_Y);
	printf("*");
}

//------------- collision check -----------
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

//------------- print score -----------
void print_score()
{
	gotoxy(1, 25); printf("");
}
