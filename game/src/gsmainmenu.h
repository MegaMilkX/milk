#ifndef _GSMAINMENU_H_
#define _GSMAINMENU_H_

#include "GameState.h"

class GSMainMenu : public GameState
{
public:
    void OnStart()
    {
        
    }
    void OnUpdate()
    {
        std::cout << "MAIN_MENU" << std::endl;
    }
    void OnRender()
    {

    }
    void OnCleanup()
    {

    }
};

#endif