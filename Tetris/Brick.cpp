
#include "Brick.h"

using namespace std;

extern unsigned long score;
extern bool start;

vector<int> col(50, 0);
vector<vector<int>> row(50, col);

vector<vector<int>> Brick::map = row;

void Brick::paint(HDC hdc)
{
	HDC screen = CreateCompatibleDC(hdc);
	HBITMAP bufbmp = CreateCompatibleBitmap(hdc, 750, 750);
	SelectObject(screen, bufbmp);
	RECT UserRect = { 0,0,750,750 };
	HBRUSH brush = CreateSolidBrush(Brick::getColor(BLACK));
	SelectObject(screen, brush);
	FillRect(screen, &UserRect, brush);
	//»æÖÆ·½¿é
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			if (Brick::map[i][j]) {
				HBRUSH tbrush = CreateSolidBrush(Brick::getColor(Brick::map[i][j]));
				HPEN tpen = CreatePen(PS_INSIDEFRAME, 1, Brick::getColor(GRAY));
				SelectObject(screen, tbrush);
				SelectObject(screen, tpen);
				Rectangle(screen, i * 15, j * 15, i * 15 + 15, j * 15 + 15);
				DeleteObject(tbrush);
				DeleteObject(tpen);
			}
	//»æÖÆ·ÖÊý
	if (!start) {
		RECT ScoreRect = { 315,315,435,345 };
		SetTextColor(screen, Brick::getColor(GOLD));
		SetBkMode(screen, TRANSPARENT);
		HFONT ScoreFont = CreateFont(25, 0, 0, 0, 0, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
		FillRect(screen, &ScoreRect, brush);
		char ScoreStr[13];
		sprintf_s(ScoreStr, "%d", score);
		SelectObject(screen, ScoreFont);
		DrawText(screen, _T(ScoreStr), -1, &ScoreRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DeleteObject(ScoreFont);
	}
	else {		//¿ªÊ¼½çÃæ
		RECT txtRect = { 300,615,450,630 };
		SetTextColor(screen, Brick::getColor(SKYBLUE));
		SetBkMode(screen, TRANSPARENT);
		HFONT Font = CreateFont(20, 0, 0, 0, 600, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
		FillRect(screen, &txtRect, brush);
		SelectObject(screen, Font);
		DrawText(screen, _T("Press Enter to start!"), -1, &txtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DeleteObject(Font);
		Font = CreateFont(12, 0, 0, 0, 200, false, false, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
		SetTextColor(screen, Brick::getColor(LIGHTGRAY));
		RECT nameRect = { 680,10,730,20 };
		SelectObject(screen, Font);
		FillRect(screen, &nameRect, brush);
		DrawText(screen, _T("EddieMap1e"), -1, &nameRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DeleteObject(Font);
	}
	BitBlt(hdc, 0, 0, 750, 750, screen, 0, 0, SRCCOPY);
	DeleteObject(brush);
	DeleteObject(screen);
	DeleteObject(bufbmp);
}

COLORREF Brick::getColor(int color)
{
	switch (color)
	{
	case RED:
		return RGB(255, 0, 0);
	case ORANGE:
		return RGB(255, 122, 0);
	case YELLOW:
		return RGB(238, 238, 0);
	case GREEN:
		return RGB(0, 255, 127);
	case CYAN:
		return RGB(0, 255, 255);
	case BLUE:
		return RGB(0, 0, 255);
	case PURPLE:
		return RGB(255, 0, 255);
	case BLACK:
		return RGB(33, 33, 33);
	case GRAY:
		return RGB(119, 136, 153);
	case LIGHTGRAY:
		return RGB(211, 211, 211);
	case PINK:
		return RGB(255, 192, 203);
	case SKYBLUE:
		return RGB(0, 191, 255);
	case GOLD:
		return RGB(255, 215, 0);
	case IVORY:
		return RGB(255, 232, 205);
	default:
		return RGB(33, 33, 33);
	}
}

bool Brick::setBrick(int x, int y, int color)
{
	if (x < 0 || y < 0 || x>49 || y>49)return false;
	Brick::map[x][y] = color;
	return true;
}


