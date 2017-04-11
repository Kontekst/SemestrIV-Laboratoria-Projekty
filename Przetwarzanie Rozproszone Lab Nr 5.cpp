/*----- Tomasz Kontek 160553 Grupa Numer 4 -----*/
/*----- Przetwarzanie Rozproszone Laboratorium Numer 5 -----*/

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Przetwarzanie Rozproszone Lab Nr 5.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool drawningInProgress;
HWND hWnd1;
HWND hWnd2;
int colors[3],brushSize;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	srand(time(NULL));
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRZETWARZANIEROZPROSZONELABNR5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRZETWARZANIEROZPROSZONELABNR5));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRZETWARZANIEROZPROSZONELABNR5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRZETWARZANIEROZPROSZONELABNR5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd1 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   hWnd2 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd1 || !hWnd2)
   {
      return FALSE;
   }

   ShowWindow(hWnd1, nCmdShow);
   ShowWindow(hWnd2, nCmdShow);
   UpdateWindow(hWnd1);
   UpdateWindow(hWnd2);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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

    case WM_PAINT:
	    {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

	case WM_RBUTTONDOWN:
	{
		colors[0] = rand() % 256;
		colors[1] = rand() % 256;
		colors[2] = rand() % 256;

	}break;

	case WM_MBUTTONDOWN:
	{
	HDC hdc1 = GetDC(hWnd1);
	HDC hdc2 = GetDC(hWnd2);
	for (int i = -20; i < 21; i++) {
		for (int j = -20; j < 21; j++) {
			if (abs(i)+abs(j)>20)
				continue;
			SetPixel(hdc1, LOWORD(lParam) + i, HIWORD(lParam) + j, RGB(colors[0], colors[1], colors[2]));
			SetPixel(hdc2, LOWORD(lParam) + i, HIWORD(lParam) + j, RGB(colors[0], colors[1], colors[2]));
		}
	}

	ReleaseDC(hWnd1, hdc1);
	ReleaseDC(hWnd2, hdc2);
		
	}break;

	case WM_LBUTTONDOWN:
	{
		drawningInProgress = true;
	}break;

	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_UP:
			brushSize++;
			break;

		case VK_DOWN:
			brushSize--;
			break;

		}
	}break;

	case WM_LBUTTONUP:
	{
		drawningInProgress = false;
	}break;
	
	case WM_MOUSEMOVE:
	{
		if (drawningInProgress) {
			HDC hdc1 = GetDC(hWnd1);
			HDC hdc2 = GetDC(hWnd2);
			for (int i = -3 - brushSize; i < 4 +brushSize; i++) {
				for (int j = -3 - brushSize; j < 4 + brushSize; j++) {
					if (i*i + j*j>brushSize*brushSize)
					continue;
					SetPixel(hdc1, LOWORD(lParam) + i, HIWORD(lParam) + j, RGB(colors[0], colors[1], colors[2]));
					SetPixel(hdc2, LOWORD(lParam) + i, HIWORD(lParam) + j, RGB(colors[0], colors[1], colors[2]));
				}
			}

			ReleaseDC(hWnd1, hdc1);
			ReleaseDC(hWnd2, hdc2);
		}

	}break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
