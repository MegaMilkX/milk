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
    
    Resource<GFXMesh>::AddSearchPath("data\\meshes");
    //Resource<GFXMesh>::AddSearchPath("data\\meshes.pak");
    Resource<GFXShader>::AddSearchPath("data\\shaders");
    Resource<GFXTexture2D>::AddSearchPath("data\\textures");
    
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
    if(state_stack.size()>0)
        state_stack.top()->OnSwitch();
}

bool GameState::Update()
{
    state_stack.top()->OnUpdate();
    
    state_stack.top()->OnRender();
    
    
    GFXSwapBuffers();
    return window.Update();
}