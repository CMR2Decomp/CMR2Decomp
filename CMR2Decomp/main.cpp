#include "main.h"
#include "Graphics.h"

// GLOBAL: CMR2 0x00663db0
HINSTANCE g_hInstance;
// GLOBAL: CMR2 0x00663c84
HWND g_hWndList[1];
// GLOBAL: CMR2 0x00663dac
int g_hWndIx = 0;

// GLOBAL: CMR2 0x00520b94
char g_lpszMenuName[5] = "menu";

int WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	return Initialize(hInstance, 0, lpCmdLine); // TODO: params aren't correct
}

// FUNCTION: CMR2 0x004a9720
unsigned char Initialize(HINSTANCE hInstance, unsigned char param2, LPSTR param3)
{
	HWND hWnd;
	hWnd = FindWindowA("Colin McRae Rally 2", "Colin McRae Rally 2");
	if (hWnd != NULL)
		return 0;

	g_hInstance = hInstance;
	CreateGameWindow(hInstance, &g_hWndList[g_hWndIx], "Colin McRae Rally 2", MessageHandler);

	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}

// STUB: CMR2 0x004a8270
BOOL FUN_004a8270(void)
{
	// todo
	return 1;
}

// STUB: CMR2 0x0049c0a0
int __stdcall FUN_0049c0a0(void *param1, void *param2)
{
	// todo
	return -1;
}

// FUNCTION: CMR2 0x004a8140
BOOL __stdcall CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC wndProc)
{
	ATOM AVar1;
	int nScreenHeight;
	int nScreenWidth;
	HWND hWnd;
	DWORD dwStyle = 0;
	HWND hWndParent;
	HMENU hMenu;
	LPVOID lpParam;
	WNDCLASSA wndClass;
	int nCmdShow;

	wndClass.lpfnWndProc = wndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIconA(hInstance, (const char *)0x6e);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(4);
	wndClass.lpszMenuName = g_lpszMenuName;
	wndClass.lpszClassName = sWindowName;
	wndClass.style = 3;

	dwStyle = 0x81cf0000;
	if (!g_pGraphics->isFullscreen)
		wndClass.hCursor = LoadCursorA(NULL, (const char *)0x7f00);
	else
		wndClass.hCursor = NULL;

	AVar1 = RegisterClassA(&wndClass);
	if (AVar1 == 0)
		return FALSE;

	lpParam = NULL;
	hMenu = NULL;
	hWndParent = NULL;
	nScreenHeight = GetSystemMetrics(1);
	nScreenWidth = GetSystemMetrics(0);

	hWnd = CreateWindowExA((DWORD)0x40000, sWindowName, sWindowName, dwStyle, 0, 0, nScreenWidth, nScreenHeight,
						   hWndParent, hMenu, hInstance, lpParam);

	g_hWndList[g_hWndIx] = hWnd;
	if (hWnd == NULL)
		return FALSE;

	if (!g_pGraphics->isFullscreen)
		nCmdShow = SW_SHOWDEFAULT; // TODO: should be SW_HIDE
	else
		nCmdShow = SW_MAXIMIZE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	*pHWND = hWnd;
	FUN_0049c0a0(FUN_004a8270, NULL);
	return TRUE;
}

// FUNCTION: CMR2 0x004a98b0
LRESULT __stdcall MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	default:
		break;

	case WM_SIZE:
		break;

	case WM_SETFOCUS:
		break;

	case WM_KILLFOCUS:
		break;

	case WM_PAINT:
		break;

	case WM_CLOSE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}
