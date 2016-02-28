#include "gfx.h"
#include "input.h"

#include "fontmap.h"

#include "window.h"

#include <iostream>

int main()
{
    Window window = Window::Create(L"yup");
    if(!InputInit(window.GetHandle()))
        std::cout << "Input initialization fucked up\n";
    if(!GFXInit(window.GetHandle()))
        std::cout << "GFX initialization fucked up\n";
        
    GFXTarget screen = GFXTarget::Create(window);
    
    
    //Load font file into memory
    void* font_data;
    size_t font_data_sz;
    
    //Rasterize
    FontMap fontmap = FontMap::Create(font_data, font_data_sz);
    fontmap.Rasterize(0, 256);
    
    GFXScene scene = GFXScene::Create();
    GFXCamera::Create(scene, "MyCamera");
    GFXMesh::Create(scene, "box");
    GFXNode::Create(scene, "test").CreateComponent<GFXCamera>();
    
    while(window.Valid())
    {
        window.Poll();
        GFXRender();
    }
    
    GFXCleanup();
    InputCleanup();
    return 0;
}