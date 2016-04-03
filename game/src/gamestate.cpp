#include "GameState.h"

std::stack<GameState*> GameState::state_stack;
Window GameState::window;

bool GameState::Init()
{
    window = Window::Create(L"game");
    
    GFXTarget* gfxTarget = GFXInit(window.GetHandle());
    if(!gfxTarget)
    {
        std::cout << "GFX initialization fucked up\n";
        return false;
    }
    
    return true;
}

void GameState::Cleanup()
{
    GFXCleanup();
}

void GameState::Pop()
{
    delete state_stack.top();
    state_stack.pop();
}

bool GameState::Update()
{
    state_stack.top()->OnUpdate();
    state_stack.top()->OnRender();
    
    
    
    return window.Update();
}