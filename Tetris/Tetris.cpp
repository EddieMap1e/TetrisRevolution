#include "Tetris.h"
#include "Brick.h"

Tetris::Tetris(HDC hdc, int shape, int x, int y) :shape(shape), x(x), y(y)
{
	state = 0;
	switch (shape)
	{
	case SHAPE_O:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x + 1,y };
		Bricks[2] = { x,y + 1 };
		Bricks[3] = { x + 1,y + 1 };
		//  01
		//  23
		break;
	}
	case SHAPE_I:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x - 1,y };
		Bricks[2] = { x + 1,y };
		Bricks[3] = { x + 2,y };
		//  1023
		break;
	}
	case SHAPE_Z:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x - 1,y };
		Bricks[2] = { x,y + 1 };
		Bricks[3] = { x + 1,y + 1 };
		//  10
		//   23
		break;
	}
	case SHAPE_S:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x + 1,y };
		Bricks[2] = { x,y + 1 };
		Bricks[3] = { x - 1,y + 1 };
		//   01
		//  32
		break;
	}
	case SHAPE_T:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x - 1,y };
		Bricks[2] = { x + 1,y };
		Bricks[3] = { x,y + 1 };
		//  102
		//   3
		break;
	}
	case SHAPE_L:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x - 1,y };
		Bricks[2] = { x + 1,y };
		Bricks[3] = { x - 1,y + 1 };
		//  102
		//  3
		break;
	}
	case SHAPE_J:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x - 1,y };
		Bricks[2] = { x + 1,y };
		Bricks[3] = { x + 1,y + 1 };
		//  102
		//    3
		break;
	}
	default:
	{
		Bricks[0] = { x,y };
		Bricks[1] = { x + 1,y };
		Bricks[2] = { x,y + 1 };
		Bricks[3] = { x + 1,y + 1 };
		//  01
		//  23
		break;
	}
	}
	int color = rand() % 11 + 1;
	for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
}

void Tetris::transform()
{
	int color = Brick::map[Bricks[0].first][Bricks[0].second];
	for (int i = 0; i < 4; i++) Brick::map[Bricks[i].first][Bricks[i].second] = 0;
	if (shape == SHAPE_I)
	{
		state = (state + 1) % 2;
		if (state == 0 && x > 0 && x + 2 < 50 && !Brick::map[x - 1][y] && !Brick::map[x + 1][y] && !Brick::map[x + 2][y])
		{
			Bricks[1] = { x - 1,y };
			Bricks[2] = { x + 1,y };
			Bricks[3] = { x + 2,y };
		}
		else if (state == 1 && y > 0 && y + 2 < 50 && !Brick::map[x][y - 1] && !Brick::map[x][y + 1] && !Brick::map[x][y + 2])
		{
			Bricks[1] = { x ,y - 1 };
			Bricks[2] = { x,y + 1 };
			Bricks[3] = { x,y + 2 };
		}
		else state = (state == 0 ? 1 : 0);
	}
	else if (shape == SHAPE_S)
	{
		state = (state + 1) % 2;
		if (state == 0 && x + 1 < 50 && !Brick::map[x + 1][y] && !Brick::map[x - 1][y + 1])
		{
			Bricks[1] = { x + 1,y };
			Bricks[2] = { x,y + 1 };
			Bricks[3] = { x - 1,y + 1 };
		}
		else if (state == 1 && y > 0 && !Brick::map[x - 1][y - 1] && !Brick::map[x - 1][y])
		{
			Bricks[1] = { x - 1 ,y };
			Bricks[2] = { x,y + 1 };
			Bricks[3] = { x - 1,y - 1 };
		}
		else state = (state == 0 ? 1 : 0);
	}
	else if (shape == SHAPE_Z)
	{
		state = (state + 1) % 2;
		if (state == 0 && x > 0 && !Brick::map[x - 1][y] && !Brick::map[x + 1][y + 1])
		{
			Bricks[1] = { x - 1,y };
			Bricks[2] = { x,y + 1 };
			Bricks[3] = { x + 1,y + 1 };
		}
		else if (state == 1 && y > 0 && !Brick::map[x][y - 1] && !Brick::map[x - 1][y + 1])
		{
			Bricks[1] = { x - 1 ,y };
			Bricks[2] = { x,y - 1 };
			Bricks[3] = { x - 1,y + 1 };
		}
		else state = (state == 0 ? 1 : 0);
	}
	else if (shape == SHAPE_T)
	{
		state = (state + 1) % 4;
		if (state == 0 && x > 0 && !Brick::map[x - 1][y])
		{
			Bricks[1] = { x - 1,y };
			Bricks[2] = { x + 1,y };
			Bricks[3] = { x ,y + 1 };
		}
		else if (state == 1 && y > 0 && !Brick::map[x][y - 1])
		{
			Bricks[1] = { x,y - 1 };
			Bricks[2] = { x ,y + 1 };
			Bricks[3] = { x - 1 ,y };
		}
		else if (state == 2 && x + 1 < 50 && !Brick::map[x + 1][y])
		{
			Bricks[1] = { x + 1 ,y };
			Bricks[2] = { x - 1 ,y };
			Bricks[3] = { x,y - 1 };
		}
		else if (state == 3 && y + 1 < 50 && !Brick::map[x][y + 1])
		{
			Bricks[1] = { x ,y + 1 };
			Bricks[3] = { x + 1 ,y };
			Bricks[2] = { x,y - 1 };
		}
		else state = (state == 0 ? 3 : state - 1);
	}
	else if (shape == SHAPE_J)
	{
		state = (state + 1) % 4;
		if (state == 0 && x > 0 && !Brick::map[x - 1][y] && !Brick::map[x + 1][y] && !Brick::map[x + 1][y + 1])
		{
			Bricks[1] = { x - 1,y };
			Bricks[2] = { x + 1,y };
			Bricks[3] = { x + 1 ,y + 1 };
		}
		else if (state == 1 && y > 0 && !Brick::map[x][y - 1] && !Brick::map[x][y + 1] && !Brick::map[x - 1][y + 1])
		{
			Bricks[1] = { x - 1 ,y + 1 };
			Bricks[2] = { x ,y - 1 };
			Bricks[3] = { x ,y + 1 };
		}
		else if (state == 2 && x + 1 < 50 && !Brick::map[x - 1][y] && !Brick::map[x - 1][y - 1] && !Brick::map[x + 1][y])
		{
			Bricks[1] = { x - 1 ,y };
			Bricks[2] = { x - 1,y - 1 };
			Bricks[3] = { x + 1 ,y };
		}
		else if (state == 3 && y + 1 < 50 && !Brick::map[x][y - 1] && !Brick::map[x][y + 1] && !Brick::map[x + 1][y - 1])
		{
			Bricks[1] = { x + 1 ,y - 1 };
			Bricks[2] = { x,y - 1 };
			Bricks[3] = { x ,y + 1 };
		}
		else state = (state == 0 ? 3 : state - 1);
	}
	else if (shape == SHAPE_L)
	{
		state = (state + 1) % 4;
		if (state == 0 && x > 0 && !Brick::map[x + 1][y] && !Brick::map[x - 1][y] && !Brick::map[x - 1][y + 1])
		{
			Bricks[1] = { x - 1,y };
			Bricks[2] = { x + 1,y };
			Bricks[3] = { x - 1 ,y + 1 };
		}
		else if (state == 1 && y > 0 && !Brick::map[x][y - 1] && !Brick::map[x][y + 1] && !Brick::map[x - 1][y - 1])
		{
			Bricks[1] = { x - 1 ,y - 1 };
			Bricks[2] = { x ,y - 1 };
			Bricks[3] = { x ,y + 1 };
		}
		else if (state == 2 && x + 1 < 50 && !Brick::map[x + 1][y] && !Brick::map[x + 1][y - 1] && !Brick::map[x - 1][y])
		{
			Bricks[1] = { x - 1 ,y };
			Bricks[2] = { x + 1,y - 1 };
			Bricks[3] = { x + 1 ,y };
		}
		else if (state == 3 && y + 1 < 50 && !Brick::map[x][y - 1] && !Brick::map[x][y + 1] && !Brick::map[x + 1][y + 1])
		{
			Bricks[1] = { x + 1 ,y + 1 };
			Bricks[2] = { x,y - 1 };
			Bricks[3] = { x ,y + 1 };
		}
		else state = (state == 0 ? 3 : state - 1);
	}
	for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
}

bool Tetris::move(int dir, int godir)
{
	int color = Brick::map[Bricks[0].first][Bricks[0].second];	//获取方块颜色
	for (int i = 0; i < 4; i++) Brick::map[Bricks[i].first][Bricks[i].second] = 0;	//把当前位置抹去
	if (dir == DIR_UP && godir != DIR_DOWN) {	//向上
		if (shape == SHAPE_O) {		//正方形
			if (y - 1 < 0 || Brick::map[x][y - 1] || Brick::map[x + 1][y - 1]) {
				for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
				return false;
			}
		}
		else if (shape == SHAPE_I) {
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x][y - 1] || Brick::map[x - 1][y - 1] || Brick::map[x + 1][y - 1] || Brick::map[x + 2][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x][y - 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_S) {
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x][y - 1] || Brick::map[x - 1][y] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x][y - 1] || Brick::map[x - 1][y - 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_Z) {
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x - 1][y - 1] || Brick::map[x][y - 1] || Brick::map[x + 1][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_T) {		//T形状
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x][y - 1] || Brick::map[x + 1][y - 1] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x - 1][y - 1] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_J) {
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x + 1][y - 1] || Brick::map[x][y - 1] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x - 1][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y - 2 < 0 || Brick::map[x][y - 1] || Brick::map[x - 1][y - 2] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x + 1][y - 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_L) {
			if (state == 0) {
				if (y - 1 < 0 || Brick::map[x - 1][y - 1] || Brick::map[x][y - 1] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y - 2 < 0 || Brick::map[x - 1][y - 2] || Brick::map[x][y - 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y - 2 < 0 || Brick::map[x][y - 1] || Brick::map[x - 1][y - 1] || Brick::map[x + 1][y - 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y - 2 < 0 || Brick::map[x][y - 2] || Brick::map[x + 1][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		y--;
		Bricks[0] = { x,y };
		Bricks[1] = { Bricks[1].first,Bricks[1].second - 1 };
		Bricks[2] = { Bricks[2].first,Bricks[2].second - 1 };
		Bricks[3] = { Bricks[3].first,Bricks[3].second - 1 };
	}
	if (dir == DIR_RIGHT && godir != DIR_LEFT) {		//向右
		if (shape == SHAPE_O) {		//正方形
			if (x + 2 > 49 || Brick::map[x + 2][y] || Brick::map[x + 2][y + 1]) {
				for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
				return false;
			}
		}
		else if (shape == SHAPE_I) {
			if (state == 0) {
				if (x + 3 > 49 || Brick::map[x + 3][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x + 1][y] || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y + 2] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_S) {
			if (state == 0) {
				if (x + 2 > 49 || Brick::map[x + 2][y] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y] || Brick::map[x][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_Z) {
			if (state == 0) {
				if (x + 2 > 49 || Brick::map[x + 1][y] || Brick::map[x + 2][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x][y + 1] || Brick::map[x + 1][y] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_T) {		//T字形
			if (state == 0) {
				if (x + 2 > 49 || Brick::map[x + 2][y] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x + 1][y] || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x + 2 > 49 || Brick::map[x + 2][y] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x + 2 > 49 || Brick::map[x + 2][y] || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_J) {
			if (state == 0) {
				if (x + 2 > 49 || Brick::map[x + 2][y + 1] || Brick::map[x + 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x + 2 > 49 || Brick::map[x][y - 1] || Brick::map[x + 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x + 2 > 49 || Brick::map[x + 1][y] || Brick::map[x + 2][y - 1] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_L) {
			if (state == 0) {
				if (x + 2 > 49 || Brick::map[x][y + 1] || Brick::map[x + 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x + 1 > 49 || Brick::map[x + 1][y] || Brick::map[x + 1][y + 1] || Brick::map[x + 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x + 2 > 49 || Brick::map[x + 2][y - 1] || Brick::map[x + 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x + 2 > 49 || Brick::map[x + 1][y - 1] || Brick::map[x + 1][y] || Brick::map[x + 2][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		x++;
		Bricks[0] = { x,y };
		Bricks[1] = { Bricks[1].first + 1,Bricks[1].second };
		Bricks[2] = { Bricks[2].first + 1,Bricks[2].second };
		Bricks[3] = { Bricks[3].first + 1,Bricks[3].second };
	}
	if (dir == DIR_DOWN && godir != DIR_UP)		//向下
	{
		if (shape == SHAPE_O) {		//正方形
			if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x + 1][y + 2]) {
				for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
				return false;
			}
		}
		else if (shape == SHAPE_I) {
			if (state == 0) {
				if (y + 1 > 49 || Brick::map[x][y + 1] || Brick::map[x - 1][y + 1] || Brick::map[x + 1][y + 1] || Brick::map[x + 2][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 3 > 49 || Brick::map[x][y + 3]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_S) {
			if (state == 0) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x - 1][y + 2] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 2 > 49 || Brick::map[x - 1][y + 1] || Brick::map[x][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_Z) {
			if (state == 0) {
				if (y + 2 > 49 || Brick::map[x - 1][y + 1] || Brick::map[x][y + 2] || Brick::map[x + 1][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 2 > 49 || Brick::map[x][y + 1] || Brick::map[x - 1][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_T) {		//T字形
			if (state == 0) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x + 1][y + 1] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y + 1 > 49 || Brick::map[x][y + 1] || Brick::map[x - 1][y + 1] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_J) {
			if (state == 0) {
				if (y + 2 > 49 || Brick::map[x + 1][y + 2] || Brick::map[x][y + 1] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x - 1][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y + 1 > 49 || Brick::map[x][y + 1] || Brick::map[x - 1][y + 1] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x + 1][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_L) {
			if (state == 0) {
				if (y + 2 > 49 || Brick::map[x - 1][y + 2] || Brick::map[x][y + 1] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (y + 2 > 49 || Brick::map[x - 1][y] || Brick::map[x][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (y + 1 > 49 || Brick::map[x][y + 1] || Brick::map[x - 1][y + 1] || Brick::map[x + 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (y + 2 > 49 || Brick::map[x][y + 2] || Brick::map[x + 1][y + 2]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		y++;
		Bricks[0] = { x,y };
		Bricks[1] = { Bricks[1].first,Bricks[1].second + 1 };
		Bricks[2] = { Bricks[2].first,Bricks[2].second + 1 };
		Bricks[3] = { Bricks[3].first,Bricks[3].second + 1 };
	}
	if (dir == DIR_LEFT && godir != DIR_RIGHT)		//向左
	{
		if (shape == SHAPE_O) {		//正方形
			if (x - 1 < 0 || Brick::map[x - 1][y] || Brick::map[x - 1][y + 1]) {
				for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
				return false;
			}
		}
		else if (shape == SHAPE_I) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 1 < 0 || Brick::map[x + 1][y] || Brick::map[x - 1][y + 1] || Brick::map[x - 1][y + 2] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_S) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 1][y] || Brick::map[x - 2][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 2 < 0 || Brick::map[x - 1][y + 1] || Brick::map[x - 2][y] || Brick::map[x - 2][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_Z) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 2 < 0 || Brick::map[x - 1][y - 1] || Brick::map[x - 2][y] || Brick::map[x - 2][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_T) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x - 1][y + 1] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x - 1 < 0 || Brick::map[x - 1][y] || Brick::map[x - 1][y + 1] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_J) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 2 < 0 || Brick::map[x - 2][y + 1] || Brick::map[x - 1][y] || Brick::map[x - 1][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x - 2 < 0 || Brick::map[x - 2][y] || Brick::map[x - 2][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x - 1 < 0 || Brick::map[x - 1][y] || Brick::map[x - 1][y - 1] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		else if (shape == SHAPE_L) {
			if (state == 0) {
				if (x - 2 < 0 || Brick::map[x - 2][y + 1] || Brick::map[x - 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 1) {
				if (x - 2 < 0 || Brick::map[x - 1][y] || Brick::map[x - 1][y + 1] || Brick::map[x - 2][y - 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 2) {
				if (x - 2 < 0 || Brick::map[x][y - 1] || Brick::map[x - 2][y]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
			else if (state == 3) {
				if (x - 1 < 0 || Brick::map[x - 1][y - 1] || Brick::map[x - 1][y] || Brick::map[x - 1][y + 1]) {
					for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
					return false;
				}
			}
		}
		x--;
		Bricks[0] = { x,y };
		Bricks[1] = { Bricks[1].first - 1,Bricks[1].second };
		Bricks[2] = { Bricks[2].first - 1,Bricks[2].second };
		Bricks[3] = { Bricks[3].first - 1,Bricks[3].second };
	}
	for (int i = 0; i < 4; i++) Brick::setBrick(Bricks[i].first, Bricks[i].second, color);
	return true;
}