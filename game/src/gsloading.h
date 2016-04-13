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
        
        File shader_file = File::Open("data\\shader140.glsl", File::READ);
        shader = GFXShader::Create(shader_file);
        
        perspective_ = ::perspective(1.5f, 16.0f/9.0f, 0.1f, 100.0f);
        camera_transform.Translate(0.0f, -0.0f, -2.0f);
        
        GFXShaderVertex vert_shader = Resource<GFXShaderVertex>::Get("Transform3D");
    }
    void OnSwitch()
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        mesh->Bind();
        shader.Use();
        //vert_shader->Use();
        //pixel_shader->Use();
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
        shader.Uniform(std::string("perspective"), perspective_);
        shader.Uniform(std::string("view"), camera_transform.GetTransform());
        shader.Uniform(std::string("model"), transform.GetTransform());
        //shader.Uniform(std::string("time"), time);
        shader.Uniform(std::string("tex"), 0);
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
    ResHdl<GFXShader> vert_shader;
    ResHdl<GFXShader> pixel_shader;
    Transform camera_transform;
    Transform transform;
    mat4f perspective_;
    GFXShader shader;
};

#endif