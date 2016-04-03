#ifndef _GSLOADING_H_
#define _GSLOADING_H_

#include <Windows.h>

#include "GameState.h"

class GSLoading : public GameState
{
public:
    GSLoading() : start_time(0), time(0) {}
    void OnInit()
    {
        start_time = GetTickCount();
    }
    void OnUpdate()
    {
        time = GetTickCount();

        if (time - start_time >= 5000)
        {
            GameState::Pop();
        }
    }
    void OnRender()
    {

    }
    void OnCleanup()
    {

    }

private:
    DWORD start_time;
    DWORD time;
};

#endif