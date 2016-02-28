#include "input.h"

#define RID_COUNT 2
#define RID_MOUSE 0x02
#define RID_KEYBOARD 0x06

WNDPROC OldWndProc;
RAWINPUTDEVICE rid[RID_COUNT];

LRESULT CALLBACK InputWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_INPUT:
        
        break;
    default:
        return CallWindowProc(OldWndProc, hWnd, msg, wParam, lParam);
    }
    return 0;
}

bool InputInit(HWND hWnd)
{
    // Replacing the window procedure with our own one
    OldWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)InputWndProc);
    if(!OldWndProc)
        return false;
    
    // Initizlize raw input
    rid[0].usUsagePage = 0x01;
    rid[0].usUsage = RID_MOUSE;
    rid[0].dwFlags = RIDEV_NOLEGACY;
    rid[0].hwndTarget = hWnd;
    
    rid[1].usUsagePage = 0x01;
    rid[1].usUsage = RID_KEYBOARD;
    rid[1].dwFlags = RIDEV_NOLEGACY;
    rid[1].hwndTarget = hWnd;
    
    if(!RegisterRawInputDevices(rid, RID_COUNT, sizeof(RAWINPUTDEVICE)))
        return false;
    
    return true;
}

void InputCleanup()
{
    
}