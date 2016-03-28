//#include <libgame.h>
#include "gsloading.h"
#include "gsmainmenu.h"

int main()
{
    //GameState::Init();
    
    GameState::Push<GSMainMenu>();
    GameState::Push<GSLoading>();
    
    while(true)
    {
        GameState::Update();
    }
    
    //GameState::Cleanup();
    return 0;
}