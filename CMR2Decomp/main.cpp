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
	Initialize(hInstance, 0, ""); // TODO: params aren't correct

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
	}
	return 1;
}

// STUB: CMR2 0x004a9720
unsigned char Initialize(HINSTANCE hInstance, unsigned char param2, char *param3)
{
	HWND hWnd;
	hWnd = FindWindowA("Colin McRae Rally 2", "Colin McRae Rally 2");
	if (hWnd != NULL)
	{
		return 0;
	}

	g_hInstance = hInstance;
	CreateGameWindow(hInstance, &g_hWndList[g_hWndIx], "Colin McRae Rally 2", NULL);
}

// STUB: CMR2 0x004a8270
void FUN_004a8270(void)
{
	// todo
}

// STUB: CMR2 0x0049c0a0
int __stdcall FUN_0049c0a0(void *param1, void *param2)
{
	// todo
	return -1;
}

// FUNCTION: CMR2 0x004a8140
BOOL __stdcall CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC *param_4)
{
	ATOM AVar1;
	int nScreenHeight;
	int nScreenWidth;
	HWND hWnd;
	DWORD dwStyle;
	HWND hWndParent;
	HMENU hMenu;
	LPVOID lpParam;
	WNDCLASSA wndClass;

	wndClass.lpfnWndProc = *param_4;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIconA(hInstance, (const char *)0x6e);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(4);
	wndClass.lpszMenuName = g_lpszMenuName;
	wndClass.lpszClassName = sWindowName;
	wndClass.style = 3;

	if (!g_pGraphics->isFullscreen)
	{
		wndClass.hCursor = LoadCursorA(NULL, (const char *)0x7f00);
		dwStyle = 0x81cf0000;
	}
	else
	{
		wndClass.hCursor = NULL;
		dwStyle = 0;
	}

	AVar1 = RegisterClassA(&wndClass);
	if (AVar1 == 0)
		return FALSE;

	lpParam = NULL;
	hMenu = NULL;
	hWndParent = NULL;
	nScreenWidth = GetSystemMetrics(0);
	nScreenHeight = GetSystemMetrics(1);

	hWnd = CreateWindowExA(0x40000, sWindowName, sWindowName, dwStyle, 0, 0, nScreenWidth, nScreenHeight,
						   hWndParent, hMenu, hInstance, lpParam);

	*(&g_hWndList[g_hWndIx]) = hWnd;
	if (hWnd == NULL)
		return FALSE;

	if (!g_pGraphics->isFullscreen)
		nScreenHeight = 0;
	else
		nScreenHeight = 3;

	ShowWindow(hWnd, nScreenHeight);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	*pHWND = hWnd;
	FUN_0049c0a0(FUN_004a8270, NULL);
	return TRUE;
}
