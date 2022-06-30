#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15
#define CHAR '●'
#define BLANK ' '

#define ESC 0x1b

#define SPECIAL1 0xe0
#define SPECIAL2 0x00

#define UP  0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define SPACE ' '

#define WIDTH 100
#define HEIGHT 30

typedef struct RECORD {
	char rank;
	int rtime;
	char name[20];
	int tryNum;
}RECORD;

void removeCursor(void) {

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

void draw_box2(int x1, int y1, int x2, int y2, char* ch)
{
	int x, y;
	for (x = x1; x <= x2; x++) {
		gotoxy(x, y1);
		printf("%s", ch);
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", ch);
		gotoxy(x2, y);
		printf("%s", ch);
	}
}

int map[30][60] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,2,2,2,2,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,2,2,2,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1,
	1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,1,
	1,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,6,6,2,2,6,6,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,1,
	1,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,2,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,2,2,2,2,2,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,6,6,2,0,0,0,0,0,0,0,0,0,0,0,0,3,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,1
};

int map2[30][60] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,10,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,7,2,2,2,1,
	1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,1,
	1,0,0,0,0,0,0,2,6,2,6,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,6,6,2,2,6,6,2,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,0,0,0,0,0,1,
	1,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,6,2,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,5,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
	1,0,9,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,2,1,
	1,2,2,2,2,6,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,0,2,2,2,6,2,2,2,2,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,1
};

int blockx = 38, blockx2 = 39, blockx3 = 40;
int blocky = 13;

void movebox(int dx, int dy) {
	map[blocky][blockx] = 0;
	map[blocky][blockx2] = 0;
	map[blocky][blockx3] = 0;

	blockx += dx;
	blockx2 += dx;
	blockx3 += dx;

	if (map[blocky][blockx] == 8) {
		blockx = 38;
	}
	if (map[blocky][blockx2] == 8) {
		blockx2 = 38;
	}
	if (map[blocky][blockx3] == 8) {
		blockx3 = 38;
	}
	map[blocky][blockx] = 2;
	map[blocky][blockx2] = 2;
	map[blocky][blockx3] = 2;
}

void putstar(int x, int y, int ch)
{
	map[y][x] = ch;
}

void erasestar(int x, int y)
{
	map[y][x] = 0;
}

void putstar2(int x, int y, int ch)
{
	map2[y][x] = ch;
}

void erasestar2(int x, int y)
{
	map2[y][x] = 0;
}

void showScore(int sco) {
	textcolor(GREEN1, GRAY1);
	gotoxy(3, 1);
	printf("Score : %d", sco);

	textcolor(BLACK, WHITE);
}

void showTryn(int t) {
	textcolor(GREEN1, GRAY1);
	gotoxy(104, 1);
	printf("Try Count : %d", t);

	textcolor(BLACK, WHITE);
}

void showTime(int Time) {
	textcolor(BLUE1, GRAY1);
	gotoxy(55, 1);
	printf("경과시간: %02d", Time);
	textcolor(BLACK, WHITE);
}

void main() {
	unsigned char last_ch, ch, ch2;
	int i, n;
	int tryn = 0, score = 0;
	int x, y, oldx, oldy, newx, newy;
	int startTime, runtime, finaltime;
	int keep_moving, keep_moving2;
	int levelcount = 0;
	keep_moving = keep_moving2 = 1;

	oldx = newx = 2;
	oldy = newy = 21;
	removeCursor();

	erasestar(oldx, oldy);
	putstar(oldx, oldy, 9);
	ch = 0;
	keep_moving = keep_moving2 = 0;
	i = 0;
	startTime = time(NULL);

START:
	oldx = newx = 2;
	oldy = newy = 21;
	while (1) {
		gotoxy(55, 32);
		printf("Left ← ↑ → Right");
		gotoxy(62, 33);
		printf("Jump");
		for (y = 0; y < 30; y++) {
			gotoxy(0, y);
			for (x = 0; x < 60; x++) {
				if (map[y][x] == 0 || map[y][x] == 28)
					printf("  ");
				else if (map[y][x] == 1) {
					textcolor(WHITE, BLACK);
					printf("□");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 2) {
					textcolor(WHITE, BLACK);
					printf("■");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 3) {
					textcolor(CYAN2, WHITE);
					printf("◎");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 4) {
					textcolor(BLACK, GRAY1);
					printf("▶");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 5) {
					if (i % 2) {
						textcolor(YELLOW2, GREEN1);
						printf("★");
						textcolor(BLACK, WHITE);
					}
					else {
						textcolor(YELLOW2, GREEN1);
						printf("☆");
						textcolor(BLACK, WHITE);
					}
				}
				else if (map[y][x] == 6) {
					textcolor(BLACK, WHITE);
					printf("△");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 7) {
					textcolor(BLACK, GRAY1);
					printf("▲");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 8) {
					textcolor(BLACK, WHITE);
					printf("▣");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 9) {
					textcolor(YELLOW1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				else if (map[y][x] == 10) {
					textcolor(BLACK, GRAY1);
					printf("◀");
					textcolor(BLACK, WHITE);
				}
				
			}
			showTryn(tryn);
			showScore(score);
			runtime = time(NULL) - startTime;
			showTime(runtime);
		}
		i = i ? 0 : 1;
		Sleep(50);
		movebox(1, 0);

		if (_kbhit() == 1) {
			ch = _getch();

			if (ch == ESC)
				exit(0);
			if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = _getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default:
					keep_moving = 0;
				}
			}
		}
		if (keep_moving) {
			switch (ch) {
			case UP:
				if (map[oldy + 1][oldx] == 2) {
					newy = oldy - 2;
				}
				else if (map[oldy + 1][newx] != 2) {
					newy = oldy + 1;
					ch = DOWN;
				}
				keep_moving = 1;
				break;
			case DOWN:
				if (map[oldy + 1][oldx] != 2) {
					newy = oldy + 1;
					ch = DOWN;
				}
				else if (map[oldy + 1][oldx] == 5) {
					newy = oldy + 1;
				}
				else if (map[oldy + 1][oldx] == 0 || map[oldy + 1][oldx] == 4) {
					newy = oldy + 1;
					ch = DOWN;
				}
				else
					newy = oldy;
				if (map[oldy + 1][oldx] == 7) {
					newx = oldx;
					newx = 24;
					newy = 10;
				}
				keep_moving = 1;
				break;
			case LEFT:
				if (oldx > 1) {
					if (map[oldy][oldx - 1] == 0 || map[oldy][oldx - 1] == 5)
						newx = oldx - 1;
					else if (map[oldy][oldx - 1] == 2 || map[oldy][oldx - 1] == 1)
						newx = oldx;
					else if (map[oldy][oldx - 1] == 10) {
						newx = oldx - 1;
						newx = 7;
						newy = 7;
					}
				}
				if (map[oldy + 1][oldx - 1] == 6) {
					newx = oldx - 1;
					tryn++;
					erasestar(oldx, oldy);
					goto START;
				}
				if (map[oldy][oldx - 1] == 7) {
					newx = oldx - 1;
					newx = 24;
					newy = 10;
				}
				if (map[newy][newx] == 6) {
					erasestar(oldx, oldy);
					tryn++;
					goto START;
				}
				if (map[oldy + 1][oldx - 1] == 0 || map[oldy + 1][oldx - 1] == 28) {
					newy = oldy + 1;
					ch = DOWN;
				}
				keep_moving = 0;
				break;
			case RIGHT:
				if (oldx < WIDTH - 2) {
					if (map[oldy][oldx + 1] == 0 || map[oldy][oldx + 1] == 5)
						newx = oldx + 1;
					else if (map[oldy][oldx + 1] == 4) {
						newx = oldx + 1;
						erasestar(oldx, oldy);
						for (oldx; map[oldy][oldx + 1] != 2; newx = oldx++)
							keep_moving = 1;
					}
					else if (oldy == 9 && oldx + 1 == 55) {
						newx = oldx + 1;
						newx = 48;
						newy = 6;
					}
					else if (oldy == 23 && oldx + 1 == 58) {
						newx = oldx + 1;
						newx = 1;
						newy = 11;
					}
					else
						newx = oldx;
				}
				if (map[oldy + 1][oldx + 1] == 6) {
					newx = oldx + 1;
					erasestar(oldx, oldy);
					tryn++;
					goto START;
				}
				if (map[oldy + 1][oldx + 1] == 0 || map[oldy + 1][oldx + 1] == 28) {
					newy = oldy + 1;
					ch = DOWN;
				}
				if (map[oldy][oldx + 1] == 7) {
					newx = oldx + 1;
					newx = 24;
					newy = 10;
				}
				keep_moving = 0;
				break;
			default:
				break;
			}
			erasestar(oldx, oldy);

			if (map[newy][newx] == 5) {
				erasestar(oldx, oldy);
				putstar(newx, newy, 9);
				score++;
			}

			if (map[newy + 1][newx] == 0) {
				ch = DOWN;
				keep_moving = 1;
			}
			if (map[newy][newx] == 28 || map[newy][newx] == 6) {
				erasestar(oldx, oldy);
				tryn++;
				goto START;
			}
			putstar(newx, newy, 9);

			if (score == 3)
				goto END;


			if (map[newy][newx + 3] == 4 || map[newy][newx + 2] == 4 || map[newy][newx + 1] == 4) {
				gotoxy(0, 30);
				printf("▶ : Teleport to RIGHT");
			}
			if (map[newy][newx + 3] == 3 || map[newy][newx + 2] == 3 || map[newy][newx + 1] == 3) {
				gotoxy(0, 31);
				printf("◎ : Teleport to another ◎");
			}
			if (map[newy][newx + 3] == 7 || map[newy][newx + 2] == 7 || map[newy][newx + 1] == 7) {
				gotoxy(0, 32);
				printf("▲: Teleport to UP");
			}
			if (map[newy][newx - 3] == 10 || map[newy][newx - 2] == 10 || map[newy][newx - 1] == 10) {
				gotoxy(0, 33);
				printf("◀: Teleport to LEFT");
			}
			oldx = newx;
			oldy = newy;
		}
	}

END:
	cls(BLACK, WHITE);
	finaltime = runtime;
	while (1) {
		int c1, c2;
		do {
			c1 = rand() % 16;
			c2 = rand() % 16;
		} while (c1 == c2);
		textcolor(c1, c2);
		gotoxy(37,9);
		printf("         CONGRATURATION!! YOU CLEARED!!         ");
		gotoxy(49, 10);
		printf("%02d초 기록, 시도횟수 %d회", finaltime, tryn);
		gotoxy(50, 13);
		printf(" S RANK: 80초 미만 ");
		gotoxy(49, 15);
		printf(" A RANK: 100초 미만 ");
		gotoxy(49, 17);
		printf(" B RANK: 120초 미만 ");
		gotoxy(49, 19);
		printf(" C RANK: 140초 미만 ");
		gotoxy(49, 21);
		printf(" D RANK: 160초 미만 ");
		gotoxy(49, 23);
		printf(" E RANK: 180초 미만 ");
		gotoxy(49, 25);
		printf(" F RANK: 200초 이상 ");
		gotoxy(45, 30);
		textcolor(WHITE, BLACK);
		printf("HIT (R) to Rank Up (Q) to Quit");
		Sleep(300);
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'r' || ch == 'q')
				break;
		}
	}
	if (ch == 'r') {
		cls(GRAY2, WHITE);
		char name[10];
		RECORD data;
		int n;

		gotoxy(51, 15);
		textcolor(WHITE, BLUE2);
		printf("Your Name? "); scanf("%s", data.name);
		data.rtime = finaltime;
		data.tryNum = ++tryn;
		if (finaltime < 80) data.rank = 'S';
		else if (finaltime >= 80 && finaltime < 100) data.rank = 'A';
		else if (finaltime >= 100 && finaltime < 120) data.rank = 'B';
		else if (finaltime >= 120 && finaltime < 140) data.rank = 'C';
		else if (finaltime >= 160 && finaltime < 180) data.rank = 'D';
		else if (finaltime >= 180 && finaltime < 200) data.rank = 'E';
		else if (finaltime >= 200) data.rank = 'F';

		while (1) {
			gotoxy(33, 16);
			printf("----------------------YOUR RANK-----------------------\n");
			gotoxy(38, 18);
			printf("%c랭크: 이름 %s, 시도횟수 %d, 경과시간 %d초\n", data.rank, data.name, data.tryNum, data.rtime);
			gotoxy(45, 20);
			printf("Press Any Button to Continue");
			if (_kbhit()) {
				break;
			}
		}
	}
	else exit(0);
	if (!levelcount) {
		cls(BLACK, WHITE);
		gotoxy(40, 16);
		textcolor(WHITE, BLACK);
		printf("Get Ready for The Next Stage!");
		gotoxy(40, 20);
		printf("Are You Ready? (Y) or (N) ");
		while (1) {
			if (_kbhit()) {
				ch = _getch();
				if (ch == 'y' || ch == 'n')
					break;
			}
		}
	}
	else {
		gotoxy(45, 21);
		exit(0);
	}
	if (ch == 'y')
		goto PRE;
	else
		exit(0);

PRE:
	startTime = time(NULL);
	int monsterDIe;
	monsterDIe = 0;
	tryn = 0;
	score = 0;
NEXT:
	cls(WHITE, BLACK);
	oldx = newx = 2;
	oldy = newy = 21;
	
	int newx2, newy2;
	int oldx2 = newx2 = 57;
	int oldy2 = newy2 = 21;
	
	while (1) {
		for (y = 0; y < 30; y++) {
			gotoxy(0, y);
			for (x = 0; x < 60; x++) {
				if (map2[y][x] == 0 || map2[y][x] == 28)
					printf("  ");
				else if (map[y][x] == 1) {
					textcolor(WHITE, BLACK);
					printf("□");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 2) {
					textcolor(WHITE, BLACK);
					printf("■");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 3) {
					textcolor(CYAN2, WHITE);
					printf("◎");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 4) {
					textcolor(BLACK, GRAY1);
					printf("▶");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 5) {
					if (i % 2) {
						textcolor(YELLOW2, GREEN1);
						printf("★");
						textcolor(BLACK, WHITE);
					}
					else {
						textcolor(YELLOW2, GREEN1);
						printf("☆");
						textcolor(BLACK, WHITE);
					}
				}
				else if (map2[y][x] == 6) {
					textcolor(BLACK, WHITE);
					printf("△");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 7) {
					textcolor(BLACK, GRAY1);
					printf("▲");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 8) {
					textcolor(BLACK, WHITE);
					printf("▣");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 9) {
					textcolor(YELLOW1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 10) {
					textcolor(BLACK, GRAY1);
					printf("◀");
					textcolor(BLACK, WHITE);
				}
				else if (map2[y][x] == 11) {
					textcolor(RED1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
			}
			showTryn(tryn);
			showScore(score);
			runtime = time(NULL) - startTime;
			showTime(runtime);
		}
		i = i ? 0 : 1;
		Sleep(50);

		if (_kbhit() == 1) {
			ch2 = ch = _getch();
			if (ch == ESC)
				exit(0);
			if (ch == SPECIAL1 || ch == SPECIAL2 && ch2 == SPECIAL1 || ch2 == SPECIAL2) {
				ch = ch2 = _getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default:
					keep_moving = 0;
				}
				switch (ch2) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving2 = 1;
					break;
				default:
					keep_moving2 = 0;
				}
			}
		}
		if (keep_moving) {
			switch (ch) {
			case UP:
				if (map2[oldy + 1][oldx] == 2) {
					newy = oldy - 2;
				}
				else if (map2[oldy + 1][newx] == 7) {
					newy = oldy;
					newy -= 3;
				}
				else if (map2[oldy + 1][newx] != 2) {
					newy = oldy + 1;
					ch = DOWN;
				}
				if (map2[oldy - 2][oldx] != 0) {
					newy = oldy - 1;
				}
				keep_moving = 1;
				break;
			case DOWN:
				if (map2[oldy + 1][oldx] != 2) {
					newy = oldy + 1;
					ch = DOWN;
				}
				else if (map2[oldy + 1][oldx] == 5) {
					newy = oldy + 1;
					score++;
				}
				else if (map2[oldy + 1][oldx] == 0) {
					newy = oldy + 1;
					ch = DOWN;
				}
				else
					newy = oldy;
				if (map2[oldy + 1][oldx] == 7) {
					newy = oldy;
					newy -= 3;
				}
				if (map2[oldy + 1][oldx] == 10) {
					newx = oldx - 1;
					erasestar2(oldx, oldy);
					for (oldx; map2[oldy][oldx - 1] != 2; newx = oldx--)
						keep_moving = 1;
				}
				keep_moving = 1;
				break;
			case LEFT:
				if (oldx > 1) {
					if (map2[oldy][oldx - 1] == 0 || map2[oldy][oldx - 1] == 5)
						newx = oldx - 1;
					else if (map2[oldy][oldx - 1] == 2 || map2[oldy][oldx - 1] == 1)
						newx = oldx;
					else if (map2[oldy][oldx - 1] == 10) {
						newx = oldx - 1;
						erasestar2(oldx, oldy);
						for (oldx; map2[oldy][oldx - 1] != 2; newx = oldx--)
							keep_moving = 1;
					}
					else if (map2[oldy][oldx - 1] == 3) {
						newy = oldx - 1;
						newy = 11;
						newx = 3;
					}
				}
				if (map2[oldy + 1][oldx - 1] == 6) {
					newx = oldx - 1;
					tryn++;
					erasestar(oldx, oldy);
					erasestar2(oldx2, oldy2);
					goto NEXT;
				}
				if (map2[oldy][oldx - 1] == 7) {
					newx = oldx - 1;
					newy -= 3;
				}
				if (map2[newy][newx] == 6) {
					erasestar(oldx, oldy);
					erasestar2(oldx2, oldy2);
					tryn++;
					goto NEXT;
				}
				if (map2[oldy + 1][oldx - 1] == 0 || map2[oldy + 1][oldx - 1] == 28) {
					newy = oldy + 1;
					ch = DOWN;
				}
				keep_moving = 0;
				break;
			case RIGHT:
				if (oldx < WIDTH - 2) {
					if (map2[oldy][oldx + 1] == 0 || map2[oldy][oldx + 1] == 5)
						newx = oldx + 1;
					else if (map2[oldy][oldx + 1] == 4) {
						newx = oldx + 1;
						erasestar2(oldx, oldy);
						for (oldx; map2[oldy][oldx + 1] != 2; newx = oldx++)
							keep_moving = 1;
					}
					else if (map[oldy][oldx + 1] == 3) {
						newx = oldx + 1;
						newx = 48;
						newy = 6;
					}
					else
						newx = oldx;
				}
				if (map2[oldy + 1][oldx + 1] == 6) {
					newx = oldx + 1;
					erasestar2(oldx, oldy);
					erasestar2(oldx2, oldy2);
					tryn++;
					goto NEXT;
				}
				if (map2[oldy + 1][oldx + 1] == 0 || map2[oldy + 1][oldx + 1] == 28) {
					newy = oldy + 1;
					ch = DOWN;
				}
				if (map2[oldy][oldx + 1] == 7) {
					newx = oldx + 1;
					newy -= 3;
				}
				if (map2[oldy][oldx+1] == 10) {
					newx = oldx - 1;
					erasestar2(oldx, oldy);
					for (oldx; map2[oldy][oldx - 1] != 2; newx = oldx--)
						keep_moving = 1;
				}
				keep_moving = 0;
				break;
			default:
				break;
			}
			erasestar2(oldx, oldy);

			if (map2[newy][newx] == 5) {
				erasestar2(oldx, oldy);
				putstar2(newx, newy, 9);
				score++;
			}

			if (map2[newy + 1][newx] == 0) {
				ch = DOWN;
				keep_moving = 1;
			}
			if (map2[newy][newx] == 28 || map2[newy][newx] == 6) {
				erasestar2(oldx, oldy);
				erasestar2(oldx2, oldy2);
				tryn++;
				goto NEXT;
			}
			putstar2(newx, newy, 9);

			if (score == 3) {
				levelcount++;
				goto END;
			}
			oldx = newx;
			oldy = newy;
		}

		if (!monsterDIe) {
			if (keep_moving2) {
				switch (ch2) {
				case UP:
					if (map2[oldy2 + 1][oldx2] == 2) {
						newy2 = oldy2 - 2;
					}
					else if (map2[oldy2 + 1][newx2] != 2) {
						newy2 = oldy2 + 1;
						ch2 = DOWN;
					}
					keep_moving2 = 1;
					break;
				case DOWN:
					if (map2[oldy2 + 1][oldx2] != 2) {
						newy2 = oldy2 + 1;
						ch2 = DOWN;
					}
					else if (map2[oldy2 + 1][oldx2] == 5) {
						newy2 = oldy2 + 1;
					}
					else if (map2[oldy2 + 1][oldx2] == 0 || map2[oldy2 + 1][oldx2] == 4) {
						newy2 = oldy2 + 1;
						ch2 = DOWN;
					}
					else if (map2[oldy2 + 1][oldx2] == 28) {
						newy2 = oldy2 + 1;
					}
					else
						newy2 = oldy2;

					keep_moving2 = 1;
					break;
				case RIGHT:
					if (oldx2 > 1) {
						if (map2[oldy2][oldx2 - 1] == 0 || map2[oldy2][oldx2 - 1] == 5)
							newx2 = oldx2 - 1;
						else if (map2[oldy2][oldx2 - 1] == 2 || map2[oldy2][oldx2 - 1] == 1)
							newx2 = oldx2;
					}
					if (map2[oldy2 + 1][oldx2 - 1] == 6) {
						newx2 = oldx2 - 1;
						erasestar2(oldx2, oldy2);
						monsterDIe=1;
					}
					if (map2[newy2][newx2] == 6) {
						erasestar2(oldx2, oldy2);
						monsterDIe=1;
					}
					if (map2[oldy2 + 1][oldx2 - 1] == 0 || map2[oldy2 + 1][oldx2 - 1] == 28) {
						newy2 = oldy2 + 1;
						erasestar2(oldx2, oldy2);
						ch2 = DOWN;
					}
					keep_moving2 = 0;
					break;

				case LEFT:
					if (oldx2 < WIDTH - 2) {
						if (map2[oldy2][oldx2 + 1] == 0 || map2[oldy2][oldx2 + 1] == 5)
							newx2 = oldx2 + 1;
						else
							newx2 = oldx2;
					}
					if (map2[oldy2 + 1][oldx2 + 1] == 0 || map2[oldy2 + 1][oldx2 + 1] == 28) {
						newy2 = oldy2 + 1;
						ch2 = DOWN;
					}
					keep_moving2 = 0;
					break;
				default:
					break;
				}
				erasestar2(oldx2, oldy2);

				if (map2[newy2 + 1][newx2] == 0) {
					ch2 = DOWN;
					keep_moving2 = 1;
				}
				if (map2[newy2][newx2] == 28 || map2[newy2][newx2] == 6) {
					erasestar2(newx2, newy2);
					monsterDIe = 1;
				}
				putstar2(newx2, newy2, 11);
				oldx2 = newx2;
				oldy2 = newy2;
			}
		}
	}
}