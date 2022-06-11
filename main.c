/************************************************************
*C programming Team project(Treasure hunt Game) by Team 7
*https://github.com/trollonion03/Cpre_Tp1
*First build: May. 3rd, 2022
*Latest build:JUN. 8th, 2022
*
*Target: Windows(x86-64)
*Language : C(MSVC, v142)
************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

//Constants
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAP_WIDTH 50
#define MAP_HEIGHT 18
#define PY_MIN 3
#define PY_MAX 21
#define PX_MIN 1
#define PX_MAX 50
#define POS_S1 22
#define POS_S2 37
#define POS_S3 52
#define POS_S4 67
#define BLK 0
#define WTE 7
#define YLW 14
#define SC2 2
#define GRE 10
#define RED 12

//Global variables
int32_t map_g[MAP_WIDTH-2][MAP_HEIGHT-2];
uint16_t d_t = 0;

//functions
void gotoxy(int32_t, int32_t);
void init();
void CngTxtClr(uint16_t);
void CreateTitleScreen();
void Game_Core(int32_t);
void Create_Ground(int16_t, int16_t);
void movekey(int32_t*, int32_t*);
void sel_lv(int32_t*);
void Story();
void LoadScreen(uint16_t, int32_t);
void CreateObstacle(int32_t lv);
void StatusPrint(int32_t, int32_t, int32_t);
void GameOver(int32_t);
void GameClear(int32_t);

int32_t main() {
	/***********************************************
	*Modularize it as much as possible
	*Use this function to import other functions
	***********************************************/
	int32_t gch,g, lv;
	
	init();
	CreateTitleScreen();
	gch = _getch();
	if (gch != 'Q' && gch != 'q') {
		Story();
		g = _getch();
		if (g == 'Q' || g == 'q')
			return 0;
	}
	else
		return 0;
	
	while (1) {
		sel_lv(&lv);
		LoadScreen(SC2, lv);
		Game_Core(lv);
	}
}

void gotoxy(int32_t x, int32_t y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void init() {
	//system("mode con cols=79 lines=23 | title game"); //Display option and windows name - for release
	srand((uint32_t)time(NULL));
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; 
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CngTxtClr(uint16_t clr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void CreateTitleScreen() {
	//TODO: New design required!
	//x : 56, y : 20
	uint8_t* ch;
	int32_t i;

	system("cls");
	gotoxy(11, 6);  printf("|�� game.konkuk.ac.kr:23   |");
	gotoxy(59, 6);  printf("��|�� |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|           <�Ǵ� �������� ����ο� ���л�Ȱ>           |");
	gotoxy(11, 9);  printf("|                      -0439  7��-                      |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                       Loading..                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(68, 22); printf("| Q: exit |");

	gotoxy(22, 12);
	CngTxtClr(YLW);
	ch = "�������������������";      
	int32_t length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}
	Sleep(200);
	CngTxtClr(WTE);

	gotoxy(28, 14);
	Sleep(100);

	//Print one character per 0.1 second
	//TODO: change "press y key" to "press any key"
	ch = "Press any key to start!";
	length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(100);
	}

	
}

void LoadScreen(uint16_t sc, int32_t lv) {
	uint8_t* ch;
	int32_t i, length;
	
	system("cls");
	switch (sc) {
	case 1:
		gotoxy(26, 7); printf("LOADING...");
		gotoxy(12, 8); printf("-------------------------------------");
		gotoxy(12, 9); printf("|                                   |");
		gotoxy(12, 10); printf("-------------------------------------");
		gotoxy(13, 9);
		ch = "###################################";
		length = strlen(ch);
		for (i = 0; i < length; i++) {
			printf("%c", ch[i]);
			Sleep(50);
		} break;
	case 2:
		gotoxy(11, 6);  printf("|�� game.konkuk.ac.kr:23/loading/tips   |");
		gotoxy(59, 6);  printf("��|�� |X|");
		gotoxy(11, 7);  printf("---------------------------------------------------------");
		gotoxy(11, 8);  printf("|                                                       |");
		gotoxy(11, 9);  printf("|                                                       |");
		gotoxy(11, 10); printf("|                                                       |");
		gotoxy(11, 11); printf("|                       Loading..                       |");
		gotoxy(11, 12); printf("|                                                       |");
		gotoxy(11, 13); printf("---------------------------------------------------------");
		
		gotoxy(27, 9); printf("%d�г��� ������ ��ġ�ÿ�!!", lv);

		gotoxy(22, 12);
		CngTxtClr(YLW);
		ch = "�������������������";
		length = strlen(ch);
		for (i = 0; i < length; i++) {
			printf("%c", ch[i]);
			Sleep(25);
		}CngTxtClr(WTE);  break; 

	default:
		break;
	}
	Sleep(200);
}


void Story() {
	uint8_t* ch;
	int32_t i;

	system("cls");
	gotoxy(64, 6); printf("��|�� |X|");
	gotoxy(6, 6);  printf("|�� game.konkuk.ac.kr:23/Story1   |");
	gotoxy(6, 7);  printf("-------------------------------------------------------------------");
	gotoxy(6, 8);  printf("|                                                                 |");
	gotoxy(6, 9);  printf("|                                                                 |");
	gotoxy(6, 10); printf("|                                                                 |");
	gotoxy(6, 11); printf("|                                                                 |");
	gotoxy(6, 12); printf("|                                                                 |");
	gotoxy(6, 13); printf("|                                                                 |");
	gotoxy(6, 14); printf("|                                                                 |");
	gotoxy(6, 15); printf("|                                                                 |");
	gotoxy(6, 16); printf("|                                                                 |");
	gotoxy(6, 17); printf("|                                                                 |");
	gotoxy(6, 18); printf("-------------------------------------------------------------------");
	
	gotoxy(8, 8);
	ch = "�ڷγ� �ҵ����̶�� ��Ȳ���� �ұ��ϰ� ������ �����Ͽ�";
	int32_t length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}

	gotoxy(8, 10);
	ch = "�Ǵ� �İ��� �հ��� ���!";
	length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}

	gotoxy(8, 12);
	ch = "���� ���Ǻ��� ��� ����, ����, ���� �׸���";
	length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}

	gotoxy(8, 14);
	ch = "����, ������ �Բ��ϴ� ��Ƽ����..!!";
	length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}

	gotoxy(8, 16);
	ch = "�Ǵ� �������� ����ο� �б���Ȱ�� ���� ���۵˴ϴ�!";
	length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(25);
	}
	
	gotoxy(28, 19); printf("Press any key to start");
}

void sel_lv(int32_t *lv) {
	//TODO: New design needed
	int32_t gch1, y = 22, count = 1;

	system("cls");
	gotoxy(34, 1); printf("==========");
	gotoxy(33, 2); printf("||��������||");
	gotoxy(34, 3); printf("==========");
	gotoxy(64, 6); printf("��|�� |X|");
	gotoxy(6, 6);  printf("|�� game.konkuk.ac.kr:23/sel_lv   |");
	gotoxy(6, 7);  printf("-------------------------------------------------------------------");
	gotoxy(6, 8);  printf("|                                                                 |");
	gotoxy(6, 9);  printf("|                                                                 |");
	gotoxy(6, 10); printf("|     |Stage 1 |     |Stage 2 |     |Stage 3 |     |Stage 4 |     |");
	gotoxy(6, 11); printf("|     |1�г�   |     |2�г�   |     |3�г�   |     |4�г�   |     |");
	gotoxy(6, 12); printf("|                                                                 |");
	gotoxy(6, 13); printf("|     �� ����                                                     |");
	gotoxy(6, 14); printf("|     | 1. Ŭ���� ���� : ������ 100 ä���                        |");
	gotoxy(6, 15); printf("|     | 2. ���� ����   : ü�� 100 ��� �Ҹ�                       |");
	gotoxy(6, 16); printf("|     | 3. ��ֹ�(#)�� ���ؼ� @�� ã�ư�����!!                    |");
	gotoxy(6, 17); printf("|     | 4. �÷��̾�� �ʷϻ� O �Դϴ�!!                           |");
	gotoxy(6, 18); printf("|                                                                 |");
	gotoxy(6, 19); printf("-------------------------------------------------------------------");
	gotoxy(68, 22); printf("| Q: exit |");

	while (1) {
		CngTxtClr(YLW);
		gotoxy(y, 10);
		printf("��");
		CngTxtClr(WTE);
		gch1 = _getch();
		printf("\b\b  ");
		switch (gch1) {
		case RIGHT:
			count++;
			break;
		case LEFT:
			count--;
			break;
		case 'q':
			exit(0);
			break;
		case 'Q':
			exit(0);
			break;
		default:
			break;
		}

		if (count == 5) {
			count = 1;
		}
		else if (count < 1) {
			count = 4;
		}
		
		switch (count){
		case 1:
			y = POS_S1;
			break;
		case 2:
			y = POS_S2;
			break;
		case 3:
			y = POS_S3;
			break;
		case 4:
			y = POS_S4;
			break;
		default:
			break;
		}

		if (gch1 == '\r') {
			*lv = count;
			break;
		}
	}
}

void Game_Core(int32_t lvs) {
	//TODO: Implementation of core functionality
	//int ground[25][15];
	int32_t px = 0, py = 0, count = 0, count2 = 0, st = 0;
	int32_t score, hp;

	system("cls");
	printf("\n");
	gotoxy(70, 1); printf("��|�� |X|");
	gotoxy(0, 1); printf("|�� game.konkuk.ac.kr:23/Stage%d   | %d�г�\n", lvs, lvs);
	printf("-------------------------------------------------------------------------------\n");
	Create_Ground(MAP_WIDTH, MAP_HEIGHT);
	CreateObstacle(lvs);
	gotoxy(0, 21); printf("| ������ ����                                                                 |");
	gotoxy(0, 22); printf("|                                                                             |");
	gotoxy(0, 23); printf("-------------------------------------------------------------------------------");
	gotoxy(65, 22); printf("|");
	gotoxy(52, 15); printf("����Ű");
	gotoxy(52, 16); printf("�� �� �� ��");
	gotoxy(52, 18); printf("��ǥ");
	gotoxy(52, 19); printf("�������� 100�� ä��ÿ�");

	px = 1; py = 4;
	score = 0; hp = 100;
	
	//TODO: Add game over & game clear conditions
	while (1) {
		if (count2 == 0)
			px = 1; py = 4; count2++;
		StatusPrint(score, hp, st);
		movekey(&px, &py);
		
		switch (map_g[px - 1][py - 4]) {
		case 1:
			score += 30;
			map_g[px - 1][py - 4] = 0;
			st = 1;
			break;
		case 3:
			score += 20;
			hp -= 10;
			map_g[px - 1][py - 4] = 0;
			st = 3;
			break;
		case 4:
			score += 10;
			hp += 10;
			map_g[px - 1][py - 4] = 0; 
			st = 4;
			break;
		case 5:
			score += 10;
			map_g[px - 1][py - 4] = 0;
			st = 5;
			break;
		case 6:
			hp -= 30;
			map_g[px - 1][py - 4] = 0;
			st = 6;
			break;
		case 7:
			hp -= 20;
			map_g[px - 1][py - 4] = 0;
			st = 7;
			break;
		case 8:
			hp -= 20;
			map_g[px - 1][py - 4] = 0;
			st = 8;
			break;
		case 9:
			hp -= 10;
			map_g[px - 1][py - 4] = 0;
			st = 9;
			break;
		}

		if (score >= 100 && hp > 0) {
			GameClear(lvs);
			Sleep(500);
			break;
		}
		else if (hp < 1) {
			d_t++;
			GameOver(d_t);
			Sleep(500);
			break;
		}
	}	
}

void movekey(int32_t *x, int32_t *y) {
	//TODO: Add Input-delay
	static int32_t count, px, py;
	int32_t ch;

	gotoxy(px, py);
	CngTxtClr(GRE);
	printf("O");
	CngTxtClr(WTE);
	
	if (count == 0) {
		px = 1; py = 4;
		count++;
	}
	else {
		ch = _getch();
		switch (ch) {
		case DOWN:
			if (py > PY_MIN && py < PY_MAX && py + 1 != PY_MAX-1 && map_g[px-1][py-3] != 2)
				py++;
			break;

		case UP:
			if (py > PY_MIN && py < PY_MAX && py - 1 != PY_MIN && map_g[px-1][py-5] != 2)
				py--;
			break;

		case LEFT:
			if (px >= PX_MIN && px < PX_MAX && px - 1 != PX_MIN-1 && map_g[px-2][py-4] != 2)
				px--;		
			break;

		case RIGHT:
			if (px >= PX_MIN && px < PX_MAX && px + 1 != PX_MAX-1 && map_g[px][py-4] != 2)
				px++;
			break;

		default:
			break;
		}
		printf("\b ");
		gotoxy(px, py);
		CngTxtClr(GRE);
		printf("O");
		CngTxtClr(WTE);
		*x = px;
		*y = py;
	}

}

void Create_Ground(int16_t x, int16_t y) {
	/******************************************************************
	*if you use a emoji like '��', the emojis consume 2 spaces.
	*If you want to move one coordinate, you have to move two spaces.
	*TODO: Find the right ground size
	******************************************************************/
	int32_t i, j;

	CngTxtClr(YLW);
	for (i = 1; i <= x; i++) {
		printf("|");
	}
	printf("\n");
	for (i = 1; i <= y - 2; i++) {
		printf("|");
		for (j = 1; j <= x - 2; j++) {
			printf(" ");
		}
		printf("|\n");
	}
	for (i = 1; i <= x; i++) {
		printf("|");
	}
	
	CngTxtClr(WTE);
	gotoxy(0, 3);
	for (i = 0; i < 25; i++) printf("��");
	for (i = 0; i < 29; i++) printf("-");
	
	gotoxy(0, 20);
	for (i = 0; i < 25; i++) printf("��");
	for (i = 0; i < 29; i++) printf("-");

	for (i = 0; i < 17; i++) {
		gotoxy(78, i + 3); printf("|");
	}
	
	printf("\n");
}

void CreateObstacle(int32_t lv) {
	/***************************************************************************
	*Emoji test list
	*��!@#$%^&*()_+|
	* -------------------------
	* MT: 1, wall: 2, drinking party: 3, class absence: 4
	* dining : 5, Team project: 6, homework: 7,  class: 8, online class: 9
	*TODO: Add the verification method to check obstacles are created correctly
	*TODO: Add spawn area protection
	***************************************************************************/
	int32_t item[MAP_WIDTH - 2][MAP_HEIGHT - 2] = { 0, };
	int32_t i, j, k, x, y, col, row;
	uint16_t count = 0;
	int32_t mt=0, dp=0, ca=0, di=0, tp=0, hw=0, cl=0, oc=0; //without wall

	switch (lv) {
	case 1:
		mt = 1; dp = 2; ca = 3; di = 4; tp = 1; hw = 2; cl = 3; oc = 4;
		break;
	case 2:
		mt = 1; dp = 2; ca = 2; di = 4; tp = 1; hw = 2; cl = 4; oc = 3;
		break;
	case 3:
		mt = 1; dp = 2; ca = 2; di = 3; tp = 2; hw = 2; cl = 3; oc = 3;
		break;
	case 4:
		mt = 0; dp = 3; ca = 3; di = 2; tp = 2; hw = 3; cl = 3; oc = 3;
		break;
	
	default:
		break;
	}

	col = sizeof(item[0]) / sizeof(int32_t);
	row = sizeof(item) / sizeof(item[0]);
	
	//init
	memset(map_g, 0, sizeof(map_g));

	//spawn area protection
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			item[i][j] = 27;
		}
	}

	//Create random item
	for (i = 0; i <= mt; i++) {
		x = rand() % MAP_WIDTH-2;
		y = rand() % MAP_HEIGHT - 2;
		
		if (item[x][y] == 0) item[x][y] = 1;
		else i--;
	}
	
	for (i = 0; i <= dp; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 3;
		else i--;
	}

	for (i = 0; i <= ca; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 4;
		else i--;
	}

	for (i = 0; i <= di; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 5;
		else i--;
	}

	for (i = 0; i <= tp; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 6;
		else i--;
	}
	
	for (i = 0; i <= hw; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 7;
		else i--;
	}
	
	for (i = 0; i <= cl; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 8;
		else i--;
	}

	for (i = 0; i <= oc; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 9;
		else i--;
	}

	//Create random wall
	for (i = 0; i <= 70; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 2;
		else i--;
	}

	//print
	for (j = 0; j < row; j++) {
		for (k = 0; k < col; k++) {
			if (item[j][k] != 0 && item[j][k] != 2 && item[j][k] != 27) {
				gotoxy(j+1, k+4);
				printf("@");
			}
			else if (item[j][k] == 2) {
				gotoxy(j+1, k+4);
				CngTxtClr(YLW);
				printf("#");
				CngTxtClr(WTE);
			}
		}
	}

	//copy
	memmove(map_g, item, sizeof(item));
	memset(item, 0, sizeof(item));
}

void StatusPrint(int32_t score, int32_t hp, int32_t st) {
	//explain about item information (2, 22). 5, 7
	gotoxy(52, 5); printf("������:       "); gotoxy(60, 5); printf("%d", score);
	gotoxy(52, 7); printf("ü��:          "); gotoxy(60, 7); printf("%d", hp);
	gotoxy(2, 22); printf("                                                              ");
	gotoxy(2, 22);
	switch (st) {
	case 1:
		printf("���л�Ȱ�� ������ mt�� �� ���, �������� 30 �ö󰩴ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+30  "); CngTxtClr(WTE);
		break;
	case 3:
		printf("���ڸ��� �� ���, �������� 20�ö����� ü���� 10 �������ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+20  "); CngTxtClr(RED); printf("-10"); CngTxtClr(WTE);
		break;
	case 4:
		printf("������ ���� ���, �������� ü���� ��� 10 �ö󰩴ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+10  "); printf("+10"); CngTxtClr(WTE);
		break;
	case 5:
		printf("���ӿ� �� ���, �������� 10 �ö󰩴ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+10  "); CngTxtClr(WTE);
		break;
	case 6:
		printf("������ ���� ��š� ü���� 30 �������ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-30"); CngTxtClr(WTE);
		break;
	case 7:
		printf("������ ���� ��š� ü���� 20 �������ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-20"); CngTxtClr(WTE);
		break;
	case 8:
		printf("��� ������ �� ��š� ü���� 20 �������ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-20"); CngTxtClr(WTE);
		break;
	case 9:
		printf("�ǽð� ���Ǹ� ���� ��š� ü���� 10 �������ϴ�.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-10"); CngTxtClr(WTE);
		break;
	default:
		break;
	}
}

void GameOver(int32_t count) {
	int32_t g;
	system("cls");
	gotoxy(11, 6);  printf("|�� game.konkuk.ac.kr:23/GameOver   |");
	gotoxy(59, 6);  printf("��|�� |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|                      Game Over!                       |");
	gotoxy(11, 9);  printf("|                                                       |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                                                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(32, 14); printf("Press Any Key!!");
	gotoxy(68, 22); printf("| Q: exit |");

	switch (count) {
	case 1:
		gotoxy(28, 11); printf("�ʹ� ������ �ϼ̱���");
		gotoxy(26, 12); printf("���δ� �޽��� �ʿ��մϴ�.");
		break;
	case 2:
		gotoxy(23, 11); printf("�ʹ� ���� ������ ���� ���Ƚ��ϴ�.");
		gotoxy(20, 12); printf("���� �Ϸ�� ħ��� �� ���� �Ǿ����");
		break;
	case 3:
		gotoxy(18, 11); printf("������ �� ���� ������ ü���� �� ��ҽ��ϴ�.");
		gotoxy(26, 12); printf("���� �� �ð��� �ʿ��մϴ�");
		break;
	case 4:
		gotoxy(25, 11); printf("���ÿ� ��� ���� ��Ƴ� ���");
		gotoxy(24, 12); printf("���� �Ϸ絿�� �ῡ ��� �˴ϴ�.");
		break;
	default:
		gotoxy(25, 10); printf("��𼱰� ��ȭ�� �ɷ��ɴϴ�");
		gotoxy(25, 11); printf("\"�������� �ڳ׸� �� �Գ�,,");
		gotoxy(22, 12); printf("�ڳ�,, ���п��� �� ������ ����??\"");
		d_t = 0;
		break;
	}
	
	g = _getch();
	if (g != 'q' && g != 'Q') {

	}
	else {
		exit(0);
	}
}

void GameClear(int32_t lv) {
	int32_t g;
	system("cls");
	gotoxy(11, 6);  printf("|�� game.konkuk.ac.kr:23/GameClear   |");
	gotoxy(59, 6);  printf("��|�� |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|                     Game Clear!                       |");
	gotoxy(11, 9);  printf("|                                                       |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                                                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(27, 14); printf("Press Any Key to next Level");
	gotoxy(27, 11);
	switch (lv) {
	case 1: 
		gotoxy(20, 11); printf("�Ǵ뿡�� ù �ظ� ���������� ��ģ ���");
		gotoxy(21, 12); printf("�����⸦ ����� ���� �����մϴ�!");
		break;
	case 2:
		gotoxy(18, 11); printf("�Ǵ뿡�� �ι�° �ظ� ���������� ��ģ ���");
		gotoxy(18, 12); printf("���� ���л�Ȱ�� ���� ���� ���� �����մϴ�!");
		break;
	case 3:
		gotoxy(18, 11); printf("�Ǵ뿡�� ����° �ظ� ���������� ��ģ ���");
		gotoxy(14, 12); printf("���� �������� �� �عۿ� ���� ���� ���� �����մϴ�!");
		break;
	case 4:
		gotoxy(22, 11); printf("�Ǵ뿡�� ������ �ر��� ���������� ��ģ ���");
		gotoxy(27, 12); printf("������ �����մϴ�!");
		break;
	default:
		break;
	}
	gotoxy(61, 22); printf("| Q: Main menu |");
	g = _getch();
	if (g != 'q' && g != 'Q') {
		if (lv < 4) 
			Game_Core(lv + 1);
	}
	else if(g == 'q' || g == 'Q')  {

	}
}