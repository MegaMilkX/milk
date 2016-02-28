#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>

class Window
{
public:
    Window();
    ~Window();
    
    static Window Create(LPCWSTR name);
    bool Valid();
    HWND GetHandle();
    void Poll();
private:
    HWND hWnd;
    MSG msg;
};

#endif