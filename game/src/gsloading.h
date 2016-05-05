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
        //shader = Resource<GFXMesh>::Get("shader");
        
        perspective_ = ::perspective(1.5f, 16.0f/9.0f, 0.1f, 100.0f);
        camera_transform.Translate(0.0f, -0.0f, -2.0f);
        
        
        GFXS::Position3D pos3d;
        pos3d.pos = GFXS::Position();
        shader = pos3d;
        GFXS::Texture2DColor tex2dcol;
        tex2dcol.texture_sampler = GFXS::Texture2D();
        tex2dcol.uv = GFXS::UV();
        //shader = tex2dcol;
        shader = GFXS::RGBA();
        shader.Compile();
    }
    void OnSwitch()
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        mesh->Bind();
        shader.Bind();
    }
    void OnUpdate()
    {
        time = GetTickCount();
        transform.Rotate(0.0001f, vec3f(0.0f, 1.0f, 0.0f));
        transform.Rotate(-0.0005f, vec3f(1.0f, 0.0f, 0.0f));
        
        
        if (time - start_time >= 5000)
        {
            GameState::Pop();
        }
    }
    void OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    ResHdl<GFXMesh> mesh;
    Transform camera_transform;
    Transform transform;
    mat4f perspective_;
    
    GFXShader shader;
};

#endif