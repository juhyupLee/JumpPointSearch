﻿// JumpPointSearch.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "JumpPointSearch.h"
#include "MyLinkedList.h"
#include <Windows.h>
#include <iostream>
#include <windowsx.h>
#include "StraightLine.h"
#include "GlobalVariable.h"
#include "Global.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JUMPPOINTSEARCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JUMPPOINTSEARCH));

    MSG msg;

    Init_GDI();
    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JUMPPOINTSEARCH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JUMPPOINTSEARCH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:

        if (wParam == 'L')
        {
            if (bLine)
            {
                bLine = false;
            }
            else
            {
                bLine = true;
            }
        }

        if (wParam == 'O')
        {
            if (bOpti)
            {
                bOpti = false;
            }
            else
            {
                bOpti = true;
            }
        }
        if (wParam == 'D')
        {
            Draw_OptimizationPath();
        }

        if (wParam == 'C')
        {
            Clear_Except();
        }
        if (wParam == VK_ESCAPE)
        {
            Clear_Tile();
        }

        if (wParam == VK_SPACE)
        {
            JPSStart();
        }
        break;
    case WM_LBUTTONDOWN:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        int xGrid = x / LENGTH;
        int yGrid = y / LENGTH;

        if ((xGrid > MAX_WIDTH - 1) || (yGrid > MAX_HEIGHT - 1))
        {
            break;
        }
        if (xGrid < 0 || yGrid < 0)
        {
            break;
        }

        if (bStartSetting == false)
        {
            bStartSetting = true;
            bEndSetting = false;
            g_Grid[g_PrevStartY][g_PrevStartX] = NOTHING;
            Draw_Nothing(g_PrevStartX * LENGTH, g_PrevStartY * LENGTH);

            g_StartX = xGrid;
            g_StartY = yGrid;
            g_PrevStartX = xGrid;
            g_PrevStartY = yGrid;

            g_Grid[yGrid][xGrid] = START;
            Draw_Start(xGrid * LENGTH, yGrid * LENGTH);
        }
        else if (bEndSetting == false)
        {
            bStartSetting = false;
            bEndSetting = true;
            g_Grid[g_PrevEndY][g_PrevEndX] = NOTHING;
            Draw_Nothing(g_PrevEndX * LENGTH, g_PrevEndY * LENGTH);

            g_EndX = xGrid;
            g_EndY = yGrid;
            g_PrevEndX = xGrid;
            g_PrevEndY = yGrid;

            g_Grid[yGrid][xGrid] = END;
            Draw_End(xGrid * LENGTH, yGrid * LENGTH);
        }
        break;
    }

    case WM_RBUTTONDOWN:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        int xGrid = x / LENGTH;
        int yGrid = y / LENGTH;

        if ((xGrid > MAX_WIDTH - 1) || (yGrid > MAX_HEIGHT - 1))
        {
            break;
        }
        if (xGrid < 0 || yGrid < 0)
        {
            break;
        }


        if (g_Grid[yGrid][xGrid] == BLOCK)
        {
            g_Grid[yGrid][xGrid] = NOTHING;
            Draw_Nothing(xGrid * LENGTH, yGrid * LENGTH);
            break;
        }

        if (bBlockSetting == false)
        {
            bBlockSetting = true;
        }

        break;
    }

    case WM_RBUTTONUP:
        if (bBlockSetting == true)
        {
            bBlockSetting = false;
        }
        break;
    case WM_MOUSEMOVE:
        if (bLine)
        {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            int xGrid = x / LENGTH;
            int yGrid = y / LENGTH;
            Clear_Except();
            //LineTest(g_StartX, g_StartY, xGrid, yGrid)
            std::vector<StraightLine::Point*> temp= straightLine.GetLineValue(g_StartX, g_StartY, xGrid, yGrid);

            for (size_t i = 0; i < temp.size(); i++)
            {
                Draw_Check2(temp[i]->m_X, temp[i]->m_Y);
            }
        }
        if (bBlockSetting)
        {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            int xGrid = x / LENGTH;
            int yGrid = y / LENGTH;

            if ((xGrid > MAX_WIDTH - 1) || (yGrid > MAX_HEIGHT - 1))
            {
                break;
            }
            if (xGrid < 0 || yGrid < 0)
            {
                break;
            }
            g_Grid[yGrid][xGrid] = BLOCK;
            Draw_Block(xGrid * LENGTH, yGrid * LENGTH);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            Clear_Tile(hdc);
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

// 정보 대화 상자의 메시지 처리기입니다.
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
