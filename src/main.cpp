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

class Scene;

class Node
{
public:
    Node(){}
    ~Node(){}
    Node Create(Scene scene){ return Node(); }
};

class Scene
{
public:
    Scene Create(){ return Scene(); }
};

class Component;
class GFXCamera
{
public:
    GFXCamera Create(Scene scene){ return Node::Create(scene).AddComponent<GFXCamera>(); }
};

int main()
{
    Window window = Window::Create(L"Cryptic");
    if(!InputInit(window.GetHandle()))
        std::cout << "Input initialization fucked up\n";
    if(!GFXInit(window.GetHandle()))
        std::cout << "GFX initialization fucked up\n";

    Scene scene = Scene::Create();
    
    //Scene scene = Scene::Create();
    //Camera cam = Camera::Create(scene);
        
    //GFXTarget screen = GFXTarget::Create(window);
    
    
    //Load font file into memory
    //void* font_data;
    //size_t font_data_sz;
    
    //Rasterize
    //FontMap fontmap = FontMap::Create(font_data, font_data_sz);
    //fontmap.Rasterize(0, 256);
    
    //GFXScene scene = GFXScene::Create();
    //GFXCamera::Create(scene, "MyCamera");
    //GFXMesh::Create(scene, "box");
    //GFXNode::Create(scene, "test").CreateComponent<GFXCamera>();
    
    while(window.Update())
    {
        //window.Poll();
        GFXRender();
    }
    
    GFXCleanup();
    InputCleanup();
    return 0;
}