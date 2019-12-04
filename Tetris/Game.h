#pragma once

#include <Windows.h>
#include "Brick.h"
#include "Tetris.h"
#include "regedit.h"

extern HDC hdc;
extern int speed;
extern unsigned long score;
extern bool start;
extern bool dead;
extern unsigned long topScore;
extern Tetris *CurrentTetris;


static void Delay(unsigned long ms)
{
	unsigned long t = GetTickCount();
	while (GetTickCount() - t < ms)continue;
}

static bool createTetris(int dir, Tetris* &T)
{
	delete T;
	T = nullptr;
	int shape = rand() % 7;
	if (dir == DIR_DOWN) {
		if (shape == SHAPE_O) {
			if (Brick::map[24][0] || Brick::map[25][0] || Brick::map[24][1] || Brick::map[25][1])
				return false;
		}
		else if (shape == SHAPE_I) {
			if (Brick::map[23][0] || Brick::map[24][0] || Brick::map[25][0] || Brick::map[26][0])
				return false;
		}
		else if (shape == SHAPE_Z) {
			if (Brick::map[23][0] || Brick::map[24][0] || Brick::map[24][1] || Brick::map[25][1])
				return false;
		}
		else if (shape == SHAPE_S) {
			if (Brick::map[24][0] || Brick::map[25][0] || Brick::map[24][1] || Brick::map[23][1])
				return false;
		}
		else if (shape == SHAPE_T) {
			if (Brick::map[23][0] || Brick::map[24][0] || Brick::map[25][0] || Brick::map[24][1])
				return false;
		}
		else if (shape == SHAPE_L) {
			if (Brick::map[23][0] || Brick::map[24][0] || Brick::map[25][0] || Brick::map[23][1])
				return false;
		}
		else if (shape == SHAPE_J) {
			if (Brick::map[23][0] || Brick::map[24][0] || Brick::map[25][0] || Brick::map[25][1])
				return false;
		}

		T = new Tetris(hdc, shape, 24, 0);
	}
	else if (dir == DIR_UP) {
		if (shape == SHAPE_O) {
			if (Brick::map[24][48] || Brick::map[25][48] || Brick::map[24][49] || Brick::map[25][49])
				return false;

		}
		else if (shape == SHAPE_I) {
			if (Brick::map[23][48] || Brick::map[24][48] || Brick::map[25][48] || Brick::map[26][48])
				return false;
		}
		else if (shape == SHAPE_Z) {
			if (Brick::map[23][48] || Brick::map[24][48] || Brick::map[24][49] || Brick::map[25][49])
				return false;
		}
		else if (shape == SHAPE_S) {
			if (Brick::map[24][48] || Brick::map[25][48] || Brick::map[24][49] || Brick::map[23][49])
				return false;
		}
		else if (shape == SHAPE_T) {
			if (Brick::map[23][48] || Brick::map[24][48] || Brick::map[25][48] || Brick::map[24][49])
				return false;
		}
		else if (shape == SHAPE_L) {
			if (Brick::map[23][48] || Brick::map[24][48] || Brick::map[25][48] || Brick::map[23][49])
				return false;
		}
		else if (shape == SHAPE_J) {
			if (Brick::map[23][48] || Brick::map[24][48] || Brick::map[25][48] || Brick::map[25][49])
				return false;
		}

		T = new Tetris(hdc, shape, 24, 48);
	}
	else if (dir == DIR_RIGHT) {
		if (shape == SHAPE_O) {
			if (Brick::map[0][24] || Brick::map[0][25] || Brick::map[1][24] || Brick::map[1][25])
				return false;
			T = new Tetris(hdc, shape, 0, 24);
		}
		else if (shape == SHAPE_I) {
			if (Brick::map[0][24] || Brick::map[1][24] || Brick::map[2][24] || Brick::map[3][24])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
		else if (shape == SHAPE_S) {
			if (Brick::map[1][24] || Brick::map[2][24] || Brick::map[0][25] || Brick::map[1][25])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
		else if (shape == SHAPE_Z) {
			if (Brick::map[0][24] || Brick::map[1][24] || Brick::map[1][25] || Brick::map[2][25])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
		else if (shape == SHAPE_T) {
			if (Brick::map[0][24] || Brick::map[1][24] || Brick::map[2][24] || Brick::map[1][25])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
		else if (shape == SHAPE_L) {
			if (Brick::map[0][24] || Brick::map[1][24] || Brick::map[2][24] || Brick::map[0][25])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
		else if (shape == SHAPE_J) {
			if (Brick::map[0][24] || Brick::map[1][24] || Brick::map[2][24] || Brick::map[2][25])
				return false;
			T = new Tetris(hdc, shape, 1, 24);
		}
	}
	else if (dir == DIR_LEFT) {
		if (shape == SHAPE_O) {
			if (Brick::map[48][24] || Brick::map[48][25] || Brick::map[49][24] || Brick::map[49][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
		else if (shape == SHAPE_I) {
			if (Brick::map[46][24] || Brick::map[47][24] || Brick::map[48][24] || Brick::map[49][24])
				return false;
			T = new Tetris(hdc, shape, 47, 24);
		}
		else if (shape == SHAPE_S) {
			if (Brick::map[48][24] || Brick::map[49][24] || Brick::map[47][25] || Brick::map[48][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
		else if (shape == SHAPE_Z) {
			if (Brick::map[47][24] || Brick::map[48][24] || Brick::map[48][25] || Brick::map[49][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
		else if (shape == SHAPE_T) {
			if (Brick::map[47][24] || Brick::map[48][24] || Brick::map[49][24] || Brick::map[48][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
		else if (shape == SHAPE_L) {
			if (Brick::map[47][24] || Brick::map[48][24] || Brick::map[49][24] || Brick::map[47][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
		else if (shape == SHAPE_J) {
			if (Brick::map[47][24] || Brick::map[48][24] || Brick::map[49][24] || Brick::map[49][25])
				return false;
			T = new Tetris(hdc, shape, 48, 24);
		}
	}
	return true;
}

static void updateWindow()
{
	if (!dead) {
		Brick::paint(hdc);
	}
	else {
		HDC screen = CreateCompatibleDC(hdc);
		HBITMAP bufbmp = CreateCompatibleBitmap(hdc, 750, 750);
		SelectObject(screen, bufbmp);
		RECT UserRect = { 0,0,750,750 };
		HBRUSH brush = CreateSolidBrush(Brick::getColor(BLACK));
		SelectObject(screen, brush);
		FillRect(screen, &UserRect, brush);
		SetTextColor(screen, Brick::getColor(RED));
		SetBkMode(screen, TRANSPARENT);
		HFONT Font = CreateFont(120, 0, 0, 0, 0, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
		SelectObject(screen, Font);
		DrawText(screen, _T("GAME OVER"), -1, &UserRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DeleteObject(Font);
		Font = CreateFont(20, 0, 0, 0, 0, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
		SetTextColor(screen, Brick::getColor(IVORY));
		SelectObject(screen, Font);
		DrawText(screen, _T("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Enter to continue..."), -1, &UserRect, DT_CENTER | DT_VCENTER);
		DeleteObject(Font);
		Font = CreateFont(30, 0, 0, 0, 0, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
		SetTextColor(screen, Brick::getColor(GOLD));
		SelectObject(screen, Font);
		char ScoreStr[100];
		sprintf_s(ScoreStr, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n你的分数是: %d\n\n历史最高分: %d", score, topScore);
		DrawText(screen, _T(ScoreStr), -1, &UserRect, DT_CENTER | DT_VCENTER);
		BitBlt(hdc, 0, 0, 750, 750, screen, 0, 0, SRCCOPY);
		DeleteObject(Font);
		DeleteObject(brush);
		DeleteObject(screen);
		DeleteObject(bufbmp);
	}
}

static void gameInit()
{
	CurrentTetris = nullptr;
	score = 0;
	speed = 800;
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			Brick::map[i][j] = 0;

	for (int i = 20; i <= 29; i++)
		for (int j = 20; j <= 29; j++)Brick::map[i][j] = BLACK;
	updateWindow();
}

static bool check()
{
	int rt = false;
	int x = 0;	//倍数
	for (int i = 0; i < 19; i++) {		//从最里层开始判断
		bool flag = true;
		for (int row = 19 - i, col = 19 - i; col <= 30 + i; col++)if (!Brick::map[row][col])flag = false;	//判断上面行
		for (int row = 30 + i, col = 19 - i; col <= 30 + i; col++)if (!Brick::map[row][col])flag = false;	//判断下面行
		for (int row = 19 - i, col = 19 - i; row <= 30 + i; row++)if (!Brick::map[row][col])flag = false;	//判断左面列
		for (int row = 19 - i, col = 30 + i; row <= 30 + i; row++)if (!Brick::map[row][col])flag = false;	//判断右面列
		if (flag) {		//消除成功
			rt = true;
			x++;
			//向里面缩一圈
			for (int j = 0; j < 19; j++) {
				for (int row = 19 - j, col = 19 - j; col <= 30 + j; col++)Brick::map[row][col] = Brick::map[row - 1][col];
				for (int row = 30 + j, col = 19 - j; col <= 30 + j; col++)Brick::map[row][col] = Brick::map[row + 1][col];
				for (int row = 19 - j, col = 19 - j; row <= 30 + j; row++)Brick::map[row][col] = Brick::map[row][col - 1];
				for (int row = 19 - j, col = 30 + j; row <= 30 + j; row++)Brick::map[row][col] = Brick::map[row][col + 1];
			}
			for (int i = 0; i < 50; i++)	//消除成功最外圈必定为空
			{
				Brick::map[i][0] = 0;
				Brick::map[i][49] = 0;
				Brick::map[49][i] = 0;
				Brick::map[0][i] = 0;
			}
			i--;		//重新判断该层
		}
	}
	if (rt) {
		score += (1000 - speed) / 10 * x * x;	//增加分数
		speed += speed >= 80 ? -20 : 0;	//改变速度
	}
	return rt;
}

static void gameOver()
{
	dead = true;
	if (score > topScore) {
		topScore = score;
		char path[] = "Software";
		char file[] = "TetrisRevolution";
		char key[] = "score";
		write_dword(path, file, key, score);
	}
	updateWindow();
}

static void startInit() {
	//进行绘制开始界面
	for (int x = 5; x <= 9; x++)Brick::map[x][15] = RED;
	for (int y = 16; y <= 21; y++)Brick::map[7][y] = RED;
	for (int x = 12; x <= 16; x++)Brick::map[x][15] = ORANGE;
	for (int x = 12; x <= 16; x++)Brick::map[x][18] = ORANGE;
	for (int x = 12; x <= 16; x++)Brick::map[x][21] = ORANGE;
	for (int y = 16; y <= 21; y++)Brick::map[12][y] = ORANGE;
	for (int x = 19; x <= 23; x++)Brick::map[x][15] = YELLOW;
	for (int y = 16; y <= 21; y++)Brick::map[21][y] = YELLOW;
	for (int y = 15; y <= 21; y++)Brick::map[26][y] = GREEN;
	for (int x = 27; x <= 29; x++)Brick::map[x][15] = GREEN;
	for (int x = 27; x <= 29; x++)Brick::map[x][18] = GREEN;
	Brick::map[30][16] = Brick::map[30][17] = Brick::map[28][19] = Brick::map[29][20] = Brick::map[30][21] = GREEN;
	for (int x = 34; x <= 36; x++)Brick::map[x][15] = BLUE;
	for (int x = 34; x <= 36; x++)Brick::map[x][21] = BLUE;
	for (int y = 16; y <= 20; y++)Brick::map[35][y] = BLUE;
	Brick::map[44][16] = Brick::map[43][15] = Brick::map[42][15] = Brick::map[41][15] =
		Brick::map[40][16] = Brick::map[40][17] = Brick::map[41][18] = Brick::map[42][18] =
		Brick::map[43][19] = Brick::map[44][20] = Brick::map[43][21] = Brick::map[42][21] =
		Brick::map[41][21] = Brick::map[40][20] = PURPLE;
	for (int y = 27; y <= 33; y++)Brick::map[24][y] = PINK;
	for (int x = 24; x <= 27; x++)Brick::map[x][27] = PINK;
	for (int x = 24; x <= 27; x++)Brick::map[x][30] = PINK;
	Brick::map[28][28] = Brick::map[28][29] = Brick::map[26][31] = Brick::map[27][32] = Brick::map[28][33] = PINK;
	for (int x = 31; x <= 35; x++)Brick::map[x][27] = IVORY;
	for (int x = 31; x <= 35; x++)Brick::map[x][30] = IVORY;
	for (int x = 31; x <= 35; x++)Brick::map[x][33] = IVORY;
	for (int y = 27; y <= 33; y++)Brick::map[31][y] = IVORY;
	for (int y = 27; y <= 29; y++)Brick::map[38][y] = GOLD;
	for (int y = 27; y <= 29; y++)Brick::map[42][y] = GOLD;
	for (int y = 30; y <= 32; y++)Brick::map[39][y] = GOLD;
	for (int y = 30; y <= 32; y++)Brick::map[41][y] = GOLD;
	Brick::map[40][33] = GOLD;
	Brick::map[45][33] = CYAN;

}

static void getHistoryScore()
{
	char totalpath[] = "Software\\TetrisRevolution";
	char keyname[] = "score";
	unsigned long v = get_dowrd(totalpath, keyname);
	if (v == ULONG_MAX)
	{
		char path[] = "Software";
		char file[] = "TetrisRevolution";
		char key[] = "score";
		write_dword(path, file, key, 0);
	}
	else topScore = v;
}