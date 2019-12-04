#pragma once

#include "Brick.h"

#define SHAPE_O 0
#define SHAPE_I 1
#define SHAPE_Z 2
#define SHAPE_S 3
#define SHAPE_T 4
#define SHAPE_L 5
#define SHAPE_J 6
#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_DOWN 3

class Tetris
{
public:
	Tetris(HDC hdc, int shape, int x, int y);
	void transform();
	bool move(int dir, int godir);
private:
	pair<int, int> Bricks[4];
	int state;
	int shape;
	int x, y;
};