#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <stack>
#include <iostream>

#include <libgame.h>

class GameState
{
public:
    virtual ~GameState(){}

    virtual void OnInit() = 0;
    virtual void OnSwitch() = 0;
    virtual void OnCleanup() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    
    static bool Init();
    static void Cleanup();

    template<typename T>
    static void Push();
    static void Pop();

    static bool Update();
protected:
    static std::stack<GameState*> state_stack;
    static Window window;
};

template<typename T>
void GameState::Push()
{
    T* state = new T();
    state_stack.push(state);
    state->OnInit();
    state->OnSwitch();
}

#endif