#include "scene.h"
#include "gfx.h"
#include "input.h"

#include "fontmap.h"

#include "window.h"

#include <iostream>

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
    window = Window::Create(L"Cryptic", 1280, 720);
    if(!InputInit(window.GetHandle()))
        std::cout << "Input initialization fucked up\n";
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

int main()
{
    Init();
    
    Scene scene = Scene::Create();
    Node* node = Node::Create(&scene);
    GFXCamera* cam = GFXCamera::Create(&scene);
    //GFXMesh* cube = GFXMesh::CreateTeapot(1.0f);
    //SFXSource* beep = SFXSource::Create(cube);
    
    while(window.Update())
    {
        gfxTarget->Render(cam);
    }
    
    Cleanup();
    return 0;
}