#ifndef _GFXMESH_H_
#define _GFXMESH_H_

#include <vector>
#include <map>
#include "glextutil.h"

#include "geometrybuffer.h"

#include "macro\macro_vertex_def.h"

#include "filesystem\filesystem.h"

extern std::map<int, int> type_to_gltype;

template<typename T>
class GFXMesh
{
public:
    enum
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };
    static GFXMesh Create(int usage = STATIC);
    static GFXMesh Create(File file, int usage = STATIC);
    GFXMesh() : vao(0) {}
    void SetVertices(std::vector<T> vertices);
    void SetIndices(std::vector<unsigned short> indices);
    void Render()
    {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, index_count, index_type, 0);
    }
    
    bool IsValid() { return vao; }
    
private:
    GLuint vao;
    GeometryBuffer vertex_buffer;
    GeometryBuffer index_buffer;
    
    int index_count;
    unsigned int index_type;
};

template<typename T>
GFXMesh<T> GFXMesh<T>::Create(int usage)
{
    GFXMesh<T> mesh;
    glGenVertexArrays(1, &mesh.vao);
    return mesh;
}

template<typename T>
GFXMesh<T> GFXMesh<T>::Create(File file, int usage)
{
    GFXMesh<T> mesh = Create(usage);
    float rawverts[64] = 
    {
        -0.5f, -0.5f, 0.5f, 0.5f, 0.1f, 0.1f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.1f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.5f, 0.1f, 0.1f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.5f, 0.3f, 0.1f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.1f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.5f, 0.3f, 0.1f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 0.1f, 0.0f, 1.0f 
    };
    std::vector<T> vertices;
    
    for(int i = 0; i < 8; ++i)
    {
        AttrPosition pos;
        AttrNormal normal;
        AttrUV uv;
        pos.value.x = rawverts[0 + i * 8]; pos.value.y = rawverts[1 + i * 8]; pos.value.z = rawverts[2 + i * 8]; 
        normal.value.x = rawverts[3 + i * 8]; normal.value.y = rawverts[4 + i * 8]; normal.value.z = rawverts[5 + i * 8];
        uv.value.x = rawverts[6 + i * 8]; uv.value.y = rawverts[7 + i * 8];
        T vert;
        vert.Set(pos);
        vert.Set(normal);
        vert.Set(uv);
        vertices.push_back(vert);
    }
    
    std::vector<unsigned short> indices = { 0, 1, 2, 2, 3, 0, 3, 2, 6, 6, 7, 3, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 0, 1, 5, 5, 4, 0, 1, 5, 6, 6, 2, 1 };
    
    mesh.SetVertices(vertices);
    mesh.SetIndices(indices);
    
    return mesh;
}

template<typename T>
void GFXMesh<T>::SetVertices(std::vector<T> vertices)
{
    if(vertices.size() == 0)
        return;
    
    glBindVertexArray(vao);
    vertex_buffer = GeometryBuffer::Create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vertex_buffer.Data(vertices.data(), sizeof(T) * vertices.size());
    size_t offset = 0;
    for(int i = T::attribCount() - 1; i >= 0; --i)
    {
        int attrIndex = T::attribCount() - 1 - i;
        AttrInfo attrInfo = T::getAttrInfo(i);
        glVertexAttribPointer(attrIndex,                          /*attrib index*/
                              attrInfo.elemCount,                 /*attrib element count*/
                              type_to_gltype[attrInfo.elemType],  /*element type*/
                              GL_FALSE,                           /*normalize?*/
                              sizeof(T),                          /*stride*/
                              (void*)offset);                     /*offset*/
        offset += attrInfo.size;
        glEnableVertexAttribArray(attrIndex);
    }
}

template<typename T>
void GFXMesh<T>::SetIndices(std::vector<unsigned short> indices)
{
    if(indices.size() == 0)
        return;
    
    glBindVertexArray(vao);
    index_buffer = GeometryBuffer::Create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    index_buffer.Data(indices.data(), sizeof(unsigned short) * indices.size());
    index_count = indices.size();
    index_type = GL_UNSIGNED_SHORT;
}

#endif