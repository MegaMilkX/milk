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

struct Attrib
{
    int elementCount;
    int elementType;
    size_t sz;
};

struct Vertex
{
    ATTRIB(float, 3, position);
    ATTRIB(float, 3, normal);
    ATTRIB(float, 4, color);
    ATTRIB(float, 2, uv);
    ATTRIB(float, 4, weigths);
    ATTRIB(int, 4, bones);
};

struct Vertex
{
    vec3f position;
    vec3f normal;
    vec4f color;
    vec2f uv;
    vec4f weights;
    vec4i bones;
    static int attribCount;
    static Attrib attribs[6];
};
int Vertex::attribCount = 6;
Attrib Vertex::attribs[6] =
{ { 3, GL_FLOAT, sizeof(vec3f) },
  { 3, GL_FLOAT, sizeof(vec3f) },
  { 4, GL_FLOAT, sizeof(vec4f) },
  { 2, GL_FLOAT, sizeof(vec2f) },
  { 4, GL_FLOAT, sizeof(vec4f) },
  { 4, GL_INT, sizeof(vec4i) }
};
  
std::vector<Attrib> vertexDesc = 
{ { 3, float, position },
  { 3, float, normal },
  { 4, float, color },
  { 2, float, uv },
  { 4, float, weights },
  { 4, int, bones }
};

int main()
{
    Init();
    
    GFXMesh mesh(vertexDesc);
    GFXMesh<Vertex> mymesh;
    //Resource<GFXTexture2D> texture = Resource<GFXTexture2D>::Get("test.tga");
    
    Scene scene = Scene::Create();
    GFXCamera* cam = GFXCamera::Create(&scene);
    //GFXRenderable* cube = GXFRenderable::Create(&scene);
    //cam->Translate(0.0f, 0.6f, 3.0f);
    
    while(window.Update())
    {
        InputUpdate();
        //cube->Rotate(0.01f, vec3f(0.0f, 1.0f, 0.0f));
        gfxTarget->Render(cam);
    }
    
    Cleanup();
    return 0;
}
