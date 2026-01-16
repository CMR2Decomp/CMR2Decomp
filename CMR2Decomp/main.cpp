#include "main.h"
#include "Graphics.h"
#include "Logger.h"
#include "Game.h"
#include "Input.h"

HINSTANCE CMain::m_hInstance;
HWND CMain::m_hWndList[1];
int CMain::m_hWndIx = 0;

char CMain::m_logFileLocation[14] = "c:\\error.txt";
char CMain::m_gameName[20] = "Colin McRae Rally 2";
char CMain::m_logFileHeader1[29] = "FILE_PRINT DEBUG INFORMATION";
char CMain::m_logFileAsterisks[29] = "****************************";
char CMain::m_logFileBlankLine[1] = "";
char CMain::m_logFileFinishedNormally[30] = "* Program finished normally *";
BOOL CMain::m_isShowingCursor = TRUE;

MSG CMain::m_win32Msg;

// GLOBAL: CMR2 0x00520b94
char m_lpszMenuName[5] = "menu";

int WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	return CMain::Initialize(hInstance, 0, lpCmdLine); // TODO: params aren't correct
}

// FUNCTION: CMR2 0x004a9720
unsigned char CMain::Initialize(HINSTANCE hInstance, unsigned char param2, LPSTR param3)
{
	HWND hWnd;
	BOOL isMessageAvailable;

	hWnd = FindWindowA(m_gameName, m_gameName);
	if (hWnd != NULL)
		return 0;

	CLogger::OpenLogFile(m_logFileLocation);
	CLogger::LogToFile(m_logFileHeader1);
	CLogger::LogToFile(m_logFileAsterisks);
	CLogger::LogToFile(m_logFileBlankLine);
	m_hInstance = hInstance;

	CreateGameWindow(hInstance, &m_hWndList[m_hWndIx], m_gameName, MessageHandler);

	MSG msg;
	while (!CGame::m_shouldExit)
	{
		if (!CGame::m_isActive)
			isMessageAvailable = PeekMessageA(&m_win32Msg, NULL, 0, 0, 1);
		else
			isMessageAvailable = GetMessageA(&m_win32Msg, NULL, 0, 0);

		if ((m_win32Msg.message == WM_ACTIVATEAPP) || (isMessageAvailable == 0))
		{
			if (!CGame::m_isActive)
			{
				CGame::FUN_004b7a40();
				CGame::FUN_004d0780();
			}
		}
		else
		{
			if (m_win32Msg.message == WM_QUIT)
				break;

			TranslateMessage(&m_win32Msg);
			DispatchMessageA(&m_win32Msg);
		}

		if (g_pGraphics->isFullscreen == FALSE)
		{
			if (m_isShowingCursor == FALSE)
			{
				ShowCursor(1);
				m_isShowingCursor = TRUE;
			}
		}
		else if (m_isShowingCursor != FALSE)
		{
			ShowCursor(0);
			m_isShowingCursor = FALSE;
		}
	}

	FUN_0049c130();
	CLogger::LogToFile(m_logFileBlankLine);
	CLogger::LogToFile(m_logFileAsterisks);
	CLogger::LogToFile(m_logFileFinishedNormally);
	CLogger::LogToFile(m_logFileAsterisks);
	CLogger::CloseLogFile();

	return m_win32Msg.wParam;
}

// STUB: CMR2 0x004a8270
BOOL FUN_004a8270(void)
{
	// todo
	return 1;
}

// FUNCTION: CMR2 0x004a8140
BOOL CMain::CreateGameWindow(HINSTANCE hInstance, HWND *pHWND, LPCSTR sWindowName, WNDPROC wndProc)
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
	wndClass.lpszMenuName = m_lpszMenuName;
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

	m_hWndList[m_hWndIx] = hWnd;
	if (hWnd == NULL)
		return FALSE;

	if (!g_pGraphics->isFullscreen)
		nCmdShow = SW_HIDE;
	else
		nCmdShow = SW_MAXIMIZE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	*pHWND = hWnd;
	CInput::FUN_0049c0a0(FUN_004a8270, NULL);
	return TRUE;
}

// FUNCTION: CMR2 0x004a98b0
LRESULT CMain::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

// STUB: CMR2 0x0049c130
void CMain::FUN_0049c130(void)
{
}
