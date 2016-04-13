//#include <libgame.h>
#include "gsloading.h"
#include "gsmainmenu.h"

int main()
{
    if(!GameState::Init())
        return 0;
    
    GameState::Push<GSMainMenu>();
    GameState::Push<GSLoading>();
    
    while(GameState::Update()){}
    
    GameState::Cleanup();
    return 0;
}