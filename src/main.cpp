#include "data.h"

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
    InputShowCursor(false);
    
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
    
    Data<GFXCamera> cam0 = Data<GFXCamera>::Get("test");
    //Data<GFXTexture2D> tex = Data::Get<GFXTexture2D>("data\\test.png");
    //Data<GFXMesh<GFXVertex>> mesh = Data::Get<GFXMesh<GFXVertex>>("data\\fuk.fbx");
    //Data<SFXClip> audioClip = Data::Get<SFXClip>("data\\music.ogg");
    
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
