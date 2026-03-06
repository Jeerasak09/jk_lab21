#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_BTN_ADD 201
#define ID_BTN_SUB 202
#define ID_BTN_MUL 203
#define ID_BTN_DIV 204

HWND hEdit1, hEdit2;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "Please input two numbers", 
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                25, 20, 185, 20, hwnd, NULL, NULL, NULL);

            hEdit1 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                25, 45, 185, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);

            hEdit2 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                25, 75, 185, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                40, 110, 30, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                80, 110, 30, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                120, 110, 30, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                160, 110, 30, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            return 0;
        }
        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            if (wmId >= ID_BTN_ADD && wmId <= ID_BTN_DIV) {
                char buf1[100], buf2[100];
                GetWindowText(hEdit1, buf1, 100);
                GetWindowText(hEdit2, buf2, 100);

                double num1 = atof(buf1);
                double num2 = atof(buf2);
                double result = 0.0;
                
                if (wmId == ID_BTN_ADD) result = num1 + num2;
                else if (wmId == ID_BTN_SUB) result = num1 - num2;
                else if (wmId == ID_BTN_MUL) result = num1 * num2;
                else if (wmId == ID_BTN_DIV) {
                    if (num2 == 0) {
                        MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                    result = num1 / num2;
                }

                char t[100];
                sprintf(t, "%f", result);
                MessageBox(hwnd, t, "Result", MB_OK);
            }
            return 0;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetBkMode(hdcStatic, TRANSPARENT);
            SetTextColor(hdcStatic, RGB(255, 255, 255));
            return (INT_PTR)CreateSolidBrush(RGB(219, 10, 91)); 
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "CalculatorClass";
    
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    wc.hbrBackground = CreateSolidBrush(RGB(219, 10, 91)); 

    if (!RegisterClass(&wc)) return 0;

    DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "My Calculator", style,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}