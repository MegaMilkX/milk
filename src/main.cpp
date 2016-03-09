#include "data.h"

#include "scene.h"
#include "gfx.h"
#include "input.h"

#include "fontmap.h"

#include "window.h"

#include <iostream>

#include "math3f.h"

#include "camera.h"
#include "renderable.h"

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
    
    std::vector<Vertex> vertices = {
        { vec3f(-0.5f, -0.5f, 0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, -0.5f, 0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, -0.5f, -0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, -0.5f, -0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, 0.5f, -0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, 0.5f, -0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 0.0f) } };
    std::vector<unsigned short> indices = { 0, 1, 2, 2, 3, 0, 3, 2, 6, 6, 7, 3, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 0, 1, 5, 5, 4, 0, 1, 5, 6, 6, 2, 1 };
    GFXMesh<Vertex> mymesh = GFXMesh<Vertex>::Create(GFXMesh<Vertex>::STATIC);
    mymesh.SetVertices(vertices);
    mymesh.SetIndices(indices);
    
    GFXShader shader;
    shader.Compile(GFXShader::VERTEX,
        R"(#version 450

        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 normal;
        layout(location = 2) in vec2 uv;

        uniform mat4 model = mat4(1.0);
        uniform mat4 perspective = mat4(1.0);
        uniform mat4 view = mat4(1.0);
        uniform float time;    
        out vec3 color;    

        void main()
        {
            color = normal * ((sin(time) * 0.5) + 0.7);
            gl_Position = perspective * view * model * vec4(position, 1.0);
        })");
    shader.Compile(GFXShader::PIXEL, 
        R"(#version 450

        out vec4 frag_color;
        in vec3 color;        

        void main()
        {
            frag_color = vec4(color, 1.0);
        })");
    shader.Link();
    shader.Use();
    
    mat4f perspective = ::perspective(1.5f, 16.0f/9.0f, 0.1f, 100.0f);
    Transform camera_transform;
    camera_transform.Translate(0.0f, -0.7f, -2.0f);
    Transform transform;
    //Resource<GFXTexture2D> texture = Resource<GFXTexture2D>::Get("test.tga");
    
    Scene scene = Scene::Create();
    Camera* cam = Camera::Create(&scene);
    Renderable* cube = Renderable::Create(&scene);
    //cube->SetMesh(Resource<GFXMesh<Vertex>>::Create(mymesh));
    //cube->SetShader(Resource<GFXShader>::Create(shader));
    //cam->Translate(0.0f, 0.7f, 2.0f);

    while(window.Update())
    {
        InputUpdate();
        transform.Rotate(0.01f, vec3f(0.3f, 0.7f, 0.0f));
        shader.Uniform(std::string("perspective"), perspective);
        shader.Uniform(std::string("view"), camera_transform.GetTransform());
        shader.Uniform(std::string("model"), transform.GetTransform());
        
        gfxTarget->Clear();
        mymesh.Render();
        GFXSwapBuffers();
        
        //cam->Render(gfxTarget);
        //GFXSwapBuffer();
        
        //cube->Rotate(0.01f, vec3f(0.0f, 1.0f, 0.0f));
    }
    
    shader.Free();
    
    Cleanup();
    return 0;
}
