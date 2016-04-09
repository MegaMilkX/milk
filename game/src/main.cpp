//#include <libgame.h>
#include "gsloading.h"
#include "gsmainmenu.h"

struct Vertex
{
    VERTEX
    (
        (AttrPosition) position,
        (AttrNormal) normal,
        (AttrUV) uv
    )
};

bool ReadR3D(std::string path, void* data_out)
{
    GFXMesh* mesh = (GFXMesh*)data_out;
    
    std::vector<Vertex> vertices =
    {
        {vec3f(-0.5f, -0.5f, 0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(1.0f, 0.0f)},
        {vec3f(0.5f, -0.5f, 0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f)},
        {vec3f(0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 1.0f)},
        {vec3f(-0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(1.0f, 1.0f)},
        {vec3f(-0.5f, -0.5f, -0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(0.0f, 0.0f)},
        {vec3f(0.5f, -0.5f, -0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(1.0f, 0.0f)},
        {vec3f(0.5f, 0.5f, -0.5f), vec3f(0.5f, 0.3f, 0.1f), vec2f(1.0f, 1.0f)},
        {vec3f(-0.5f, 0.5f, -0.5f), vec3f(0.5f, 0.1f, 0.1f), vec2f(0.0f, 1.0f)}
    };
    std::vector<unsigned short> indices = { 0, 1, 2, 2, 3, 0, 3, 2, 6, 6, 7, 3, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 0, 1, 5, 5, 4, 0, 1, 5, 6, 6, 2, 1 };
    
    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    
    return true;
}

int main()
{
    if(!GameState::Init())
        return 0;
    
    Resource<GFXMesh>::AddReader(ResourceReader("r3d", ReadR3D));
    
    GameState::Push<GSMainMenu>();
    GameState::Push<GSLoading>();
    
    while(GameState::Update()){}
    
    GameState::Cleanup();
    return 0;
}