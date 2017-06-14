// ����������.cpp : ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "����������.h"
#include"cClearGame.h"

#define MAX_LOADSTRING 100
#define CLIENTX 1133
#define CLIENTY 520

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

cClearGame g_Play;

// �˴���ģ���а����ĺ�����ǰ������: 

ATOM                MyRegisterClass(HINSTANCE hInstance);

BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

VOID MoveToCenter(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣



	// ��ʼ��ȫ���ַ���

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 

	if (!InitInstance(hInstance, nCmdShow))

	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	MSG msg;

	// ����Ϣѭ��: 

	while (GetMessage(&msg, nullptr, 0, 0))

	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//

//  ����: MyRegisterClass()

//

//  Ŀ��: ע�ᴰ���ࡣ

//

ATOM MyRegisterClass(HINSTANCE hInstance)

{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//

//   ����: InitInstance(HINSTANCE, int)

//

//   Ŀ��: ����ʵ�����������������

//

//   ע��: 

//

//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������

//        ��������ʾ�����򴰿ڡ�

//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW &~WS_THICKFRAME &~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	MoveToCenter(hWnd);
	ShowWindow(hWnd, nCmdShow);
	g_Play.GameStart(hWnd);
	UpdateWindow(hWnd);

	return TRUE;
}

//

//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)

//

//  Ŀ��:    ���������ڵ���Ϣ��

//

//  WM_COMMAND  - ����Ӧ�ó���˵�

//  WM_PAINT    - ����������

//  WM_DESTROY  - �����˳���Ϣ������

//

//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �����˵�ѡ��: 

		switch (wmId)

		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONUP:
		g_Play.CheckMouse();
		break;
	case WM_RBUTTONUP:
		g_Play.ClickRButton();
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...

		EndPaint(hWnd, &ps);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)

{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

VOID MoveToCenter(HWND hWnd)
{
	int screenX, screenY;
	RECT rect;
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
	GetClientRect(hWnd, &rect);
	MoveWindow(hWnd, (screenX - (rect.right - rect.left)) / 2 - 60, (screenY - (rect.bottom - rect.top)) / 2 - 30, CLIENTX + 12, CLIENTY + 10, FALSE);
}
