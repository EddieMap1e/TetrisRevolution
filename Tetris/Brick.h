#pragma once

#include <Windows.h>
#include <vector>
#include <tchar.h>

using namespace std;

#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define CYAN 6
#define PURPLE 7
#define PINK 8
#define SKYBLUE 9
#define GOLD 10
#define IVORY 11
#define BLACK -1
#define GRAY -2
#define LIGHTGRAY -3

class Brick
{
public:
	static vector<vector<int>> map;
	static void paint(HDC hdc);
	static COLORREF getColor(int color);
	static bool setBrick(int x, int y, int color);
};