
#include "pch.h"
#include <Windows.h>

HWND window;
WNDPROC originalWndProc;

static LRESULT __stdcall wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // do anything...
    HDC hdc = GetDC(window);
    LineTo(hdc, 100, 100);
    ReleaseDC(window, hdc);

    return CallWindowProcW(originalWndProc, window, msg, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // find the window handle
        window = FindWindowW(L"YodaoMainWndClass", nullptr);
        // modify window process functions
        originalWndProc = WNDPROC(SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(wndProc)));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

