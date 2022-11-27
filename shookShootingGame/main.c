#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include <time.h>
#include <mmsystem.h>
#include <stdbool.h>
#pragma comment(lib, "winmm.lib")

static int randX[10] = { 0 }, randY[10] = { 0 };
int count = 0;
int score = 0;
int charX, charY;
bool b = true;

// 커서를 해당 위치로 이동
void gotoxy(int x, int y) {
	COORD Pos; 
	Pos.X = 2 * x; 
	Pos.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); 
}

// 커서 디자인
void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE; // FALSE: 커서 숨김
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printChar(int x, int y) {
	gotoxy(x, y + 2);
	printf("     ■  ■    ");
	gotoxy(x, y + 4);
	printf("    ■    ■   ");
	gotoxy(x, y + 5);
	printf("    ■■■■   ");
}

void cleanChar(int x, int y) {
	for (int i = 0; i < 8; i++) {
		gotoxy(x, y + i);
		printf("               ");
	}
}

void printEnemy(int x, int y) {
	gotoxy(x, y);
	printf(".  ^--^");
	gotoxy(x, y + 1);
	printf("(* ^ *  )");
	gotoxy(x, y + 2);
	printf(" /U U  \\");
}

void cleanEnemy(int x, int y) {
	for (int i = 0; i < 3; i++) {
		gotoxy(x, y+i);
		printf("          ");
	}
}

void shoot() {
	int x = charX + 3;
	int y = 28;
	for (int i = 0; i < 25; i++) {
		gotoxy(x, y);
		printf("슉");
		Sleep(20);
		gotoxy(x-1, y);
		printf("      ");
		y--;
		if (y == 2) {
			break;
		}
	}
}

// 시작 화면 출력 쓰레드
unsigned _stdcall Thread_Intro(void* arg) {
	while (1) {
		system("cls");
		gotoxy(0, 0);
		printf("\n");
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		printf("                ::::::::       :::    :::       ::::::::       ::::::::       :::    :::\n");
		printf("              :+:    :+:      :+:    :+:      :+:    :+:     :+:    :+:      :+:   :+:  \n");
		printf("             +:+             +:+    +:+      +:+    +:+     +:+    +:+      +:+  +:+    \n");
		printf("            +#++:++#++      +#++:++#++      +#+    +:+     +#+    +:+      +#++:++      \n");
		printf("                  +#+      +#+    +#+      +#+    +#+     +#+    +#+      +#+  +#+      \n");
		printf("          #+#    #+#      #+#    #+#      #+#    #+#     #+#    #+#      #+#   #+#      \n");
		printf("          ########       ###    ###       ########       ########       ###    ###      \n");
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("     ::::::::  :::    :::  ::::::::   ::::::::  ::::::::::: ::::::::::: ::::    :::  ::::::::  \n");
		printf("    :+:    :+: :+:    :+: :+:    :+: :+:    :+:     :+:         :+:     :+:+:   :+: :+:    :+: \n");
		printf("    +:+        +:+    +:+ +:+    +:+ +:+    +:+     +:+         +:+     :+:+:+  +:+ +:+        \n");
		printf("    +#++:++#++ +#++:++#++ +#+    +:+ +#+    +:+     +#+         +#+     +#+ +:+ +#+ :#:        \n");
		printf("           +#+ +#+    +#+ +#+    +#+ +#+    +#+     +#+         +#+     +#+  +#+#+# +#+   +#+# \n");
		printf("    #+#    #+# #+#    #+# #+#    #+# #+#    #+#     #+#         #+#     #+#   #+#+# #+#    #+# \n");
		printf("     ########  ###    ###  ########   ########      ###     ########### ###    ####  ######## \n");
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("                                                        .         .                          \n");
		printf("          ,o888888o.             .8.                   ,8.       ,8.          8 8888888888  \n");
		printf("         8888     `88.          .888.                 ,888.     ,888.         8 8888         \n");
		printf("      ,8 8888       `8.        :88888.               .`8888.   .`8888.        8 8888         \n");
		printf("      88 8888                 . `88888.             ,8.`8888. ,8.`8888.       8 8888         \n");
		printf("      88 8888                .8. `88888.           ,8'8.`8888,8^8.`8888.      8 888888888888 \n");
		printf("      88 8888               .8`8. `88888.         ,8' `8.`8888' `8.`8888.     8 8888         \n");
		printf("      88 8888   8888888    .8' `8. `88888.       ,8'   `8.`88'   `8.`8888.    8 8888         \n");
		printf("      `8 8888       .8'   .8'   `8. `88888.     ,8'     `8.`'     `8.`8888.   8 8888         \n");
		printf("         8888     ,88'   .888888888. `88888.   ,8'       `8        `8.`8888.  8 8888         \n");
		printf("          `8888888P'    .8'       `8. `88888. ,8'         `         `8.`8888. 8 888888888888 \n");
		printf("\n");
		gotoxy(10, 33);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("1. 게임 시작         2. 게임 설명         3. 게임 종료\n");
		Sleep(300);
		gotoxy(0, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("     ::::::::  :::    :::  ::::::::   ::::::::  ::::::::::: ::::::::::: ::::    :::  ::::::::  \n");
		printf("    :+:    :+: :+:    :+: :+:    :+: :+:    :+:     :+:         :+:     :+:+:   :+: :+:    :+: \n");
		printf("    +:+        +:+    +:+ +:+    +:+ +:+    +:+     +:+         +:+     :+:+:+  +:+ +:+        \n");
		printf("    +#++:++#++ +#++:++#++ +#+    +:+ +#+    +:+     +#+         +#+     +#+ +:+ +#+ :#:        \n");
		printf("           +#+ +#+    +#+ +#+    +#+ +#+    +#+     +#+         +#+     +#+  +#+#+# +#+   +#+# \n");
		printf("    #+#    #+# #+#    #+# #+#    #+# #+#    #+#     #+#         #+#     #+#   #+#+# #+#    #+# \n");
		printf("     ########  ###    ###  ########   ########      ###     ########### ###    ####  ######## \n");
		printf("\n");
		Sleep(300);
	}
	_endthreadex(0);
}

unsigned _stdcall Thread_Enemy(void* arg) {
	while (1) {
		if (count < 10) {
			int x = rand() % 40 + 1;
			int y = rand() % 5 + 3;
			gotoxy(x, y);
			printEnemy(x, y);
			for (int i = 0; i < 10; i++) {
				if (randX[i] == 0) {
					randX[i] = x;
					randY[i] = y;
					count++;
					break;
				}
			}
		}

		system("cls");
		gotoxy(21, 0);
		printf("score:  %5d", score);
		gotoxy(0, 29);
		for (int i = 0; i < 99; i++) {
			printf("─");
		}
		gotoxy(charX, charY);
		printChar(charX, charY);

		for (int i = 0; i < 10; i++) {
			if (randX[i] != 0) {
				randY[i]++;
				cleanEnemy(randX[i], randY[i] - 1);
				printEnemy(randX[i], randY[i]);
			}
		}

		for (int i = 0; i < 10; i++) {
			if (randY[i]+3 >= 29) {
				b = false;
			}
		}

		int k = rand() % 3000;
		Sleep(k);
	}
	_endthreadex(0);
}

int main() {

	system("mode con cols=100 lines=38");
	CursorView();
	HANDLE intro_thread;
	HANDLE enemy_thread;
	srand((unsigned)time(NULL));
	PlaySound(TEXT("dance.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	while (1) {
		HANDLE intro_thread = (HANDLE)_beginthreadex(NULL, 0, Thread_Intro, NULL, 0, NULL);
		char c = NULL;

		// 반짝반짝 쓰레드랑 동시 실행
		// 버튼 입력 1. 시작 2. 설명 3. 종료
		while (1) {
			c = _getch();
			if (c != NULL) {
				TerminateThread(intro_thread, 0);
				break;
			}
		}
		
		// 2. 게임 설명
		if (c == '2') {
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			c = NULL;
			while (1) {
				gotoxy(0, 10);
				printf("                                          ! 게임 설명 !\n\n\n");
				printf("                                  A, D 키로 움직일 수 있습니다.\n\n");
				printf("                                    S 키를 누르면 공격합니다.\n\n");
				printf("                                  적을 처치하면 점수를 얻습니다.\n\n");
				printf("                           적이 선 안쪽으로 넘어오면 게임이 종료됩니다.\n\n\n");
				printf("                                          1. 게임 시작\n\n");
				printf("                                          2. 메인 화면\n\n");
				printf("                                          3. 게임 종료\n");
				c = _getch();
				if (c != NULL) {
					break;
				}
			}
		}

		// 3. 게임 종료
		if (c == '3') {
			system("cls");
			gotoxy(0, 18);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("                                        게임을 종료합니다.\n");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			exit(0);
		}

		// 1. 게임 시작
		if (c == '1') {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (int i = 3; i > 0; i--) {
				system("cls");
				gotoxy(0, 13);
				printf("                           ┌────────────────────────────────────────────┐\n");
				printf("                           │                                            │\n");
				printf("                           │          3초 뒤 게임을 시작합니다.         │\n");
				printf("                           │                                            │\n");
				printf("                           │                     %d                      │\n", i);
				printf("                           │                                            │\n");
				printf("                           └────────────────────────────────────────────┘\n");
				Sleep(1000);
			}
 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			system("cls");

			gotoxy(0, 29);
			for (int i = 0; i < 99; i++) {
				printf("─");
			}

			for (int i = 0; i < 10; i++) {
				randX[i] = 0;
				randY[i] = 0;
			}
			count = 0;
			score = 0;
			b = true;

			charX = 21; charY = 30;
			gotoxy(charX, charY);
			printChar(charX, charY);

			HANDLE enemy_thread = (HANDLE)_beginthreadex(NULL, 0, Thread_Enemy, NULL, 0, NULL);

			while (b) {
				
				gotoxy(21, 0);
				printf("score:  %5d", score);

				char ch;
				ch = _getch();

				switch (ch) {
				case 'a':
					if (charX >= 1) { cleanChar(charX, charY); charX--; gotoxy(charX, charY); printChar(charX, charY);} break;
				case 's':
					shoot();
					for (int i = 0; i < 10; i++) {
						if (randX[i] <= charX + 3 && randX[i] + 4 >= charX + 3) {
							score += 100;
							cleanEnemy(randX[i], randY[i]);
							randX[i] = 0;
							count--;
							break;
						}
					}
					break;
				case 'd':
					if (charX <= 42) { cleanChar(charX, charY); charX++; gotoxy(charX, charY); printChar(charX, charY); } break;
				}

				Sleep(50);
			}

			TerminateThread(enemy_thread, 0);

			system("cls");
			gotoxy(0, 6);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("                                ######      ###    ##     ## ######## \n");
			printf("                               ##    ##    ## ##   ###   ### ##       \n");
			printf("                               ##         ##   ##  #### #### ##       \n");
			printf("                               ##   #### ##     ## ## ### ## ######   \n");
			printf("                               ##    ##  ######### ##     ## ##       \n");
			printf("                               ##    ##  ##     ## ##     ## ##       \n");
			printf("                                ######   ##     ## ##     ## ######## \n");
			printf("\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("                         #######       ##     ##      ########      ########  \n");
			printf("                        ##     ##      ##     ##      ##            ##     ## \n");
			printf("                        ##     ##      ##     ##      ##            ##     ## \n");
			printf("                        ##     ##      ##     ##      ######        ########  \n");
			printf("                        ##     ##       ##   ##       ##            ##   ##   \n");
			printf("                        ##     ##        ## ##        ##            ##    ##  \n");
			printf("                         #######          ###         ########      ##     ## \n");
			printf("\n\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("                             당신의 점수는\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			printf("                                                %d\n", score);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("                                                           점 입니다.\n\n\n");
			printf("                              R 키를 누르면 메인 화면으로 돌아갑니다.\n");

			c = NULL;
			while (c != 'r') {
				c = _getch();
			}


		}
	}

	return 0;
}