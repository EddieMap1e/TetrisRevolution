//Code By Eddie Zhao
#pragma comment(lib, "User32")
#pragma comment(lib,"GDI32")
#pragma comment(lib,"Advapi32")
extern unsigned long score = 0;		//分数
extern unsigned long topScore = 0;	//历史最高分
extern int speed = 800;	//下落速度
extern bool dead = false;	//是否游戏失败
extern bool start = true;	//开始界面

bool pause = false;

#include <Windows.h>

#include "resource.h"

static HDC hdc;		//屏幕句柄

#include <tchar.h>
#include <time.h>
#include "Brick.h"
#include "Tetris.h"
#include "Game.h"

using namespace std;

RECT UserRect = { 0,0,750,750 };	//用户窗口大小
extern Tetris *CurrentTetris = nullptr;		//当前的方块
int godir = DIR_DOWN;		//下落方向

LRESULT CALLBACK WinMainCallBack(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (Msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:		//关闭窗口
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE: {		//空格键变换
			if (start || dead)break;
			CurrentTetris->transform();
			updateWindow();
			break;
		}
		case VK_LEFT: {			//向左
			if (start || dead)break;
			CurrentTetris->move(DIR_LEFT, godir);
			updateWindow();
			break;
		}
		case VK_RIGHT: {		//向右
			if (start || dead)break;
			CurrentTetris->move(DIR_RIGHT, godir);
			updateWindow();
			break;
		}
		case VK_UP: {			//向上
			if (start || dead)break;
			CurrentTetris->move(DIR_UP, godir);
			updateWindow();
			break;
		}
		case VK_DOWN: {			//向下
			if (start || dead)break;
			CurrentTetris->move(DIR_DOWN, godir);
			updateWindow();
			break;
		}
		case VK_RETURN: {		//回车
			if (start) {
				start = false;
				gameInit();
			}
			else if (dead) {
				dead = false;
				gameInit();
			}
			break;
		}
		default:
			break;
		}
	case WM_PAINT:		//重绘窗口
	{
		updateWindow();
	}
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	srand((unsigned int)time(NULL));

	WNDCLASS WndCls = {};		//窗体定义
	WndCls.style = CS_HREDRAW | CS_VREDRAW;
	WndCls.lpfnWndProc = WinMainCallBack;
	WndCls.hInstance = hInstance;
	WndCls.lpszClassName = _T("TetrisRevolution");
	WndCls.hbrBackground = CreateSolidBrush(Brick::getColor(BLACK));
	WndCls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON3));

	RegisterClass(&WndCls);		//注册进程

	AdjustWindowRect(&UserRect, WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX, false);

	HWND hWnd = CreateWindow(
		WndCls.lpszClassName,
		_T("Tetris"),
		WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		UserRect.right - UserRect.left,
		UserRect.bottom - UserRect.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	hdc = GetDC(hWnd);		//获取屏幕句柄

	ShowWindow(hWnd, SW_SHOW);
	SetFocus(hWnd);

	startInit();

	getHistoryScore();

	MSG msg;
	long long Ptime1 = GetTickCount();
	while (true)		//消息队列循环
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)return 0;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!pause && !dead && !start) {
			long long NTime1 = GetTickCount();

			if (NTime1 - Ptime1 > speed) {		//进行下落
				if (!CurrentTetris || !CurrentTetris->move(godir, godir))	//当前无方块或者下落到任意平台
				{
					if (check())
						updateWindow();
					godir = rand() % 4;
					Delay(200);
					if (!createTetris(godir, CurrentTetris)) {		//无法生成 游戏失败
						gameOver();
					}
				}
				updateWindow();
				Ptime1 = GetTickCount();
			}
		}
	}
}