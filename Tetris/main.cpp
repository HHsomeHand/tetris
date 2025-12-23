#include <Windows.h>
#include <windowsx.h>
#include "resource.h"
#include <math.h>
#include <stdexcept>
#include <tchar.h>
#include "corn_app_common.h"
#include "corn_debug.h"
#include <iostream>
#include "CShape.h"
#include "CGame.h"
#include "CShape.h"
#include "main.h"

using namespace corn;
using namespace std;

#define chHANDLE_DLGMSG(hwnd, message, fn) case (message): return (SetDlgMsgResult(hwnd, uMsg, HANDLE_##message((hwnd), (wParam), (lParam), (fn))))

HINSTANCE g_hInstance;

HWND g_hWinMain;

constexpr int TIMER_FLASH = 1;
void MainDlg_OnClose(HWND hDlg)
{
	DestroyWindow(hDlg);
}

void SetWindowCenter(HWND hwnd)
{
	RECT pos;
	GetClientRect(hwnd, &pos);

	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);

	int newLeft = width / 2 - pos.right / 2;
	int newTop = height / 2 - pos.bottom / 2;

	SetWindowPos(hwnd, NULL, newLeft, newTop, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

BOOL MainDlg_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{

	SetTimer(hDlg, TIMER_FLASH, 400, NULL);

    g_hWinMain = hDlg;
    
	DWORD dwStyle = GetClassLongW(hDlg, GCL_STYLE);
	dwStyle |= CS_HREDRAW;
	dwStyle |= CS_VREDRAW;
	SetClassLongW(hDlg, GCL_STYLE, dwStyle);

	SetWindowCenter(hDlg);

	HMENU hMainMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MAIN_MENU));
	if (NULL == hMainMenu) {
		ErrorReport();
	}
    
	SetMenu(hDlg, hMainMenu);
	// SendMessageW(hDlg, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_MAIN)));
	
	return TRUE;
}

void MainDlg_OnPaint(HWND hDlg)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hDlg, &ps);

	HDC hMemDc = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(hDlg, &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;


	// 创建和窗口大小兼容的位图
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);

	// 把位图选入内存 DC，保存之前的旧位图
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDc, hBitmap);

	FillRect(hMemDc, &rc, (HBRUSH)(COLOR_WINDOW + 1));

	CGame::GetInstance().Paint(hMemDc);

	// 把内存 DC 内容拷贝到窗口 DC
	BitBlt(hdc, 0, 0, width, height, hMemDc, 0, 0, SRCCOPY);

	// 清理资源
	SelectObject(hMemDc, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDc);

	EndPaint(hDlg, &ps);
}

void MainDlg_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {
	case IDM_EXIT:
		DestroyWindow(hDlg);

		break;
	}
}

void MainDlg_OnDestory(HWND hwnd) {
	PostQuitMessage(0);
}

void OnTimerFlash(HWND hwnd) {
	InvalidateRect(hwnd, NULL, false);
	
	CGame::GetInstance().DownShape(hwnd);
}

void MainDlg_OnTimer(HWND hwnd, UINT id) {
	switch (id) {
	case TIMER_FLASH: 
		OnTimerFlash(hwnd);
		break;
	}
}

void MainDlg_OnChar(HWND hwnd, TCHAR ch, int cRepeat) {
	Vector2D v = { 0 };
	switch (ch) {
	case 'W':
	case 'w':
		CGame::GetInstance().RotateCurrShape();
		return;
	case 'S':
	case 's':
		v = VECTOR2D_DOWN;
		break;
	case 'A':
	case 'a':
		v = VECTOR2D_LEFT;
		break;
	case 'D':
	case 'd':
		v = VECTOR2D_RIGHT;
		break;
	default:
		return;
	}
	CGame::GetInstance().Move(v);
}

void OnGameOver(HWND hDlg) {
	KillTimer(hDlg, TIMER_FLASH);
}

INT_PTR CALLBACK DialogProc(
	HWND hDlg,  // handle to dialog box
	UINT uMsg,     // message  
	WPARAM wParam, // first message parameter
	LPARAM lParam  // second message parameter
)
{
	switch (uMsg)
	{
		chHANDLE_DLGMSG(hDlg, WM_COMMAND, MainDlg_OnCommand);
		chHANDLE_DLGMSG(hDlg, WM_INITDIALOG, MainDlg_OnInitDialog);
		chHANDLE_DLGMSG(hDlg, WM_CLOSE, MainDlg_OnClose);
		chHANDLE_DLGMSG(hDlg, WM_PAINT, MainDlg_OnPaint);
		chHANDLE_DLGMSG(hDlg, WM_DESTROY, MainDlg_OnDestory);
		chHANDLE_DLGMSG(hDlg, WM_TIMER, MainDlg_OnTimer);
		chHANDLE_DLGMSG(hDlg, WM_CHAR, MainDlg_OnChar);

	case WM_GAME_OVER:
		OnGameOver(hDlg);
		break;
	}
	return FALSE;
}

int WINAPI _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nShowCmd
)
{
#if _DEBUG
	{
		InitConsole();
	}
#endif

	srand((unsigned int)time(NULL));

	CGame::GetInstance();

    g_hInstance = hInstance;

    //DialogBoxParam(hInstance, MAKEINTRESOURCEW(IDD_MAIN), NULL, DialogProc, NULL);

    HWND hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCEW(IDD_MAIN), NULL, DialogProc, NULL);

	if (NULL == hDlg) {
		ErrorReport();
	}
	
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDA_MAIN));
	if (NULL == hAccel) {
		ErrorReport();
	}

    ShowWindow(hDlg, SW_SHOW);

    MSG msg = { 0 };
	BOOL bRet;

	while ((bRet = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			ErrorReport();
		}
		else
		{
			if (!TranslateAccelerator(
				hDlg,      
				hAccel,
				&msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	CShape::StaticRelease();
	return 0;
}