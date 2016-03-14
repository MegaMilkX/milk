#include "scene.h"
#include "gfx.h"
#include "input.h"

#include "fontmap.h"

#include "window.h"

#include <iostream>

#include "math3f.h"

#include "camera.h"
#include "renderable.h"

#include "resource.h"

//GFX = graphics
//SFX = sound effects
//STG = stage
//SCN = scene
//DAT = filesystem
//PHY - physics

Window window;
GFXTarget* gfxTarget;

bool Init()
{
    window = Window::Create(L"REDREDRED", 1280, 720);
    if(!InputInit(window.GetHandle()))
        std::cout << "Input initialization fucked up\n";
    //TODO: Look into SetCapture and ClipCursor functions
    //InputShowCursor(false);
    
    gfxTarget = GFXInit(window.GetHandle());
    if(!gfxTarget)
    {
        std::cout << "GFX initialization fucked up\n";
        return false;
    }
    
    return true;
}

void Cleanup()
{
    GFXCleanup();
    InputCleanup();
}

struct Vertex
{
    VERTEX
    (
        (AttrPosition) position,
        (AttrNormal) normal,
        (AttrUV) uv
    )
};

#include "transform.h"

int main()
{
    Init();
    
    File mesh_file = File::Open("data\\mesh.obj", File::READ);
    GFXMesh<Vertex> mesh = GFXMesh<Vertex>::Create(mesh_file);
    
    File shader_file = File::Open("data\\shader140.glsl", File::READ);
    GFXShader shader = GFXShader::Create(shader_file);
    shader.Use();
    
    File texture_file = File::Open("data\\texture.png", File::READ);
    GFXTexture2D texture = GFXTexture2D::Create(texture_file);
    texture.Use(0);
    
    mat4f perspective = ::perspective(1.5f, 16.0f/9.0f, 0.1f, 100.0f);
    Transform camera_transform;
    camera_transform.Translate(0.0f, -0.0f, -2.0f);
    Transform transform;
    
    Scene scene = Scene::Create();
    Camera* cam = Camera::Create(&scene);
    Renderable* cube = Renderable::Create(&scene);
    //cube->SetMesh(Resource<GFXMesh<Vertex>>::Create(mymesh));
    //cube->SetShader(Resource<GFXShader>::Create(shader));
    //cam->Translate(0.0f, 0.7f, 2.0f);
    
    //=======================================================
    // Mockups
    //=======================================================

    
    float time = 0;
    while(window.Update())
    {
        InputUpdate();
        transform.Rotate(0.01f, vec3f(0.0f, 1.0f, 0.0f));
        transform.Rotate(-0.005f, vec3f(1.0f, 0.0f, 0.0f));
        shader.Uniform(std::string("perspective"), perspective);
        shader.Uniform(std::string("view"), camera_transform.GetTransform());
        shader.Uniform(std::string("model"), transform.GetTransform());
        shader.Uniform(std::string("time"), time);
        shader.Uniform(std::string("tex"), 0);
        
        gfxTarget->Clear();
        mesh.Render();
        GFXSwapBuffers();
        
        //cam->Render(gfxTarget);
        //GFXSwapBuffer();
        
        //cube->Rotate(0.01f, vec3f(0.0f, 1.0f, 0.0f));
        time += 0.001f;
    }
    
    shader.Free();
    
    Cleanup();
    return 0;
}
