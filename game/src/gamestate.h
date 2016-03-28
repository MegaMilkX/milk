#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <stack>

#include <iostream>

class GameState
{
public:
    virtual ~GameState(){}

    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    virtual void OnCleanup() = 0;

    template<typename T>
    static void Push();
    static void Pop();

    static void Input();
    static void Update();
    static void Render();
protected:
    static std::stack<GameState*> state_stack;
};

template<typename T>
void GameState::Push()
{
    T* state = new T();
    state_stack.push(state);
    state->OnStart();
}

#endif