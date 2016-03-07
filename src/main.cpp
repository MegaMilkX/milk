#include "data.h"

#include "scene.h"
#include "gfx.h"
#include "input.h"

#include "fontmap.h"

#include "window.h"

#include <iostream>

#include "math3f.h"

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
    //TODO: Look into SetCapture and ClipCursor function
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

int main()
{
    Init();
    
    std::vector<Vertex> vertices = {
        { vec3f(-0.5f, -0.5f, 0.5f), vec3f(0.5f, 0.2f, 0.0f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, -0.5f, 0.5f), vec3f(0.0f, 0.5f, 0.2f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, 0.5f, 0.5f), vec3f(0.2f, 0.0f, 0.5f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, 0.5f, 0.5f), vec3f(1.0f, 0.0f, 0.0f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, -0.5f, -0.5f), vec3f(0.0f, 1.0f, 0.0f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, -0.5f, -0.5f), vec3f(0.0f, 0.0f, 1.0f), vec2f(0.0f, 0.0f) },
        { vec3f(0.5f, 0.5f, -0.5f), vec3f(0.0f, 1.0f, 0.0f), vec2f(0.0f, 0.0f) },
        { vec3f(-0.5f, 0.5f, -0.5f), vec3f(1.0f, 0.0f, 0.0f), vec2f(0.0f, 0.0f) } };
    std::vector<unsigned short> indices = { 0, 1, 2, 2, 3, 0, 3, 2, 6, 6, 7, 3, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 0, 1, 5, 5, 4, 0, 1, 5, 6, 6, 2, 1 };
    GFXMesh<Vertex> mymesh;
    mymesh.SetVertices(vertices);
    mymesh.SetIndices(indices);
    //Resource<GFXTexture2D> texture = Resource<GFXTexture2D>::Get("test.tga");
    
    Scene scene = Scene::Create();
    GFXCamera* cam = GFXCamera::Create(&scene);
    //GFXRenderable* cube = GXFRenderable::Create(&scene);
    //cam->Translate(0.0f, 0.6f, 3.0f);
    
    while(window.Update())
    {
        InputUpdate();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mymesh.Render();
        GFXSwapBuffers();
        //cube->Rotate(0.01f, vec3f(0.0f, 1.0f, 0.0f));
        //gfxTarget->Render(cam);
    }
    
    Cleanup();
    return 0;
}
