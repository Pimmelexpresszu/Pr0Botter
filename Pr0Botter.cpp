// Pr0Botter.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "windows.h"
#include <thread>
#include <chrono>
#include "winuser.h"
#include "psapi.h"
#include "tlhelp32.h"

#define VK_Q 0x51
#define VK_F 0x46

HHOOK KeyboardHook;

static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
    int length = GetWindowTextLength(hWnd);
    WCHAR buffer[600];
    GetWindowText(hWnd, buffer, 600);
    std::wstring windowTitle(buffer);


    if (windowTitle.find(L"pr0gramm") != std::wstring::npos)
    {
        int ret = SendMessage(hWnd, WM_KEYDOWN, (int)lparam, NULL);
    }

    return true;
}

void sendMessageToWindow(int key)
{


    EnumWindows(enumWindowCallback, key);

}




LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN)
        {
            switch (p->vkCode)
            {
                case VK_NUMPAD6: sendMessageToWindow(VK_RIGHT); break;
                case VK_NUMPAD4: sendMessageToWindow(VK_LEFT); break;
                case VK_NUMPAD2: sendMessageToWindow(VK_DOWN); break;
                case VK_NUMPAD8: sendMessageToWindow(VK_UP); break;
                case VK_NUMPAD7: sendMessageToWindow(VK_Q); break;
                case VK_NUMPAD9: sendMessageToWindow(VK_F); break;
                case VK_ADD: sendMessageToWindow(VK_ADD); break;
                case VK_SUBTRACT: sendMessageToWindow(VK_SUBTRACT); break;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int main()
{
    KeyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL, // low-level keyboard input events
        HookProcedure, // pointer to the hook procedure
        GetModuleHandle(NULL), // A handle to the DLL containing the hook procedure 
        NULL //desktop apps, if this parameter is zero
    );

    if (!KeyboardHook) {

    }
    else {
        MSG Msg;
        while (GetMessage(&Msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }
}




