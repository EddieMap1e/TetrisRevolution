//Code By Eddie Zhao
#pragma comment(lib, "User32")
#pragma comment(lib,"GDI32")
#pragma comment(lib,"Advapi32")
extern unsigned long score = 0;		//����
extern unsigned long topScore = 0;	//��ʷ��߷�
extern int speed = 800;	//�����ٶ�
extern bool dead = false;	//�Ƿ���Ϸʧ��
extern bool start = true;	//��ʼ����

bool pause = false;

#include <Windows.h>

#include "resource.h"

static HDC hdc;		//��Ļ���

#include <tchar.h>
#include <time.h>
#include "Brick.h"
#include "Tetris.h"
#include "Game.h"

using namespace std;

RECT UserRect = { 0,0,750,750 };	//�û����ڴ�С
extern Tetris *CurrentTetris = nullptr;		//��ǰ�ķ���
int godir = DIR_DOWN;		//���䷽��

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
	case WM_CLOSE:		//�رմ���
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE: {		//�ո���任
			if (start || dead)break;
			CurrentTetris->transform();
			updateWindow();
			break;
		}
		case VK_LEFT: {			//����
			if (start || dead)break;
			CurrentTetris->move(DIR_LEFT, godir);
			updateWindow();
			break;
		}
		case VK_RIGHT: {		//����
			if (start || dead)break;
			CurrentTetris->move(DIR_RIGHT, godir);
			updateWindow();
			break;
		}
		case VK_UP: {			//����
			if (start || dead)break;
			CurrentTetris->move(DIR_UP, godir);
			updateWindow();
			break;
		}
		case VK_DOWN: {			//����
			if (start || dead)break;
			CurrentTetris->move(DIR_DOWN, godir);
			updateWindow();
			break;
		}
		case VK_RETURN: {		//�س�
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
	case WM_PAINT:		//�ػ洰��
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

	WNDCLASS WndCls = {};		//���嶨��
	WndCls.style = CS_HREDRAW | CS_VREDRAW;
	WndCls.lpfnWndProc = WinMainCallBack;
	WndCls.hInstance = hInstance;
	WndCls.lpszClassName = _T("TetrisRevolution");
	WndCls.hbrBackground = CreateSolidBrush(Brick::getColor(BLACK));
	WndCls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON3));

	RegisterClass(&WndCls);		//ע�����

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

	hdc = GetDC(hWnd);		//��ȡ��Ļ���

	ShowWindow(hWnd, SW_SHOW);
	SetFocus(hWnd);

	startInit();

	getHistoryScore();

	MSG msg;
	long long Ptime1 = GetTickCount();
	while (true)		//��Ϣ����ѭ��
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)return 0;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!pause && !dead && !start) {
			long long NTime1 = GetTickCount();

			if (NTime1 - Ptime1 > speed) {		//��������
				if (!CurrentTetris || !CurrentTetris->move(godir, godir))	//��ǰ�޷���������䵽����ƽ̨
				{
					if (check())
						updateWindow();
					godir = rand() % 4;
					Delay(200);
					if (!createTetris(godir, CurrentTetris)) {		//�޷����� ��Ϸʧ��
						gameOver();
					}
				}
				updateWindow();
				Ptime1 = GetTickCount();
			}
		}
	}
}