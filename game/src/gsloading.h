#ifndef _GSLOADING_H_
#define _GSLOADING_H_

#include <Windows.h>

#include "GameState.h"

class GSLoading : public GameState
{
public:
    GSLoading() : start_time(0), time(0), scene(Scene::Create()) {}
    void OnInit()
    {
        
        start_time = GetTickCount();
        
        camera = Camera::Create(&scene);
        mesh = Resource<GFXMesh>::Get("cube");
    }
    void OnSwitch()
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        //mesh->Bind();
        //vert_shader->Use();
        //pixel_shader->Use();
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //pixel_shader->Uniform(std::string("time"), time * 0.001f);
        //mesh->Render();
    }
    void OnCleanup()
    {

    }

private:
    DWORD start_time;
    DWORD time;
    
    Scene scene;
    Camera* camera;
    ResHdl<GFXMesh> mesh;
    ResHdl<GFXShader> vert_shader;
    ResHdl<GFXShader> pixel_shader;
};

#endif