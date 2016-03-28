#include "GameState.h"

std::stack<GameState*> GameState::state_stack;

void GameState::Pop()
{
    delete state_stack.top();
    state_stack.pop();
}

void GameState::Input()
{
    
}

void GameState::Update()
{
    state_stack.top()->OnUpdate();
}

void GameState::Render()
{
    state_stack.top()->OnRender();
}