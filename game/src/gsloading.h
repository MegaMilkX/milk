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
        vert_shader = Resource<GFXVertexShader>::Get("vertex_shader_basic");
        pixel_shader = Resource<GFXPixelShader>::Get("color_shader");
    }
    void OnSwitch()
    {
        mesh->Bind();
        vert_shader->Bind();
        pixel_shader->Bind();
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
        pixel_shader->Uniform("time", time * 0.001f);
        mesh->Render();
    }
    void OnCleanup()
    {

    }

private:
    DWORD start_time;
    DWORD time;
    
    Scene scene;
    Camera* camera;
    Resource<GFXMesh> mesh;
    Resource<GFXVertexShader> vert_shader;
    Resource<GFXPixelShader> pixel_shader;
};

#endif