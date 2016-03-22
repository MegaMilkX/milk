#ifndef _GFXMESH_H_
#define _GFXMESH_H_

#include <vector>
#include <map>
#include "glextutil.h"

#include "geometrybuffer.h"

#include "macro\macro_vertex_def.h"

#include "filesystem\file.h"

#include "util\r3ddata.h"

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
    std::vector<T> vertices;
    std::vector<unsigned short> indices;
    
    R3DData r3d = R3DData::Read(file);
    
    r3d.VertexCount();
    
    for(int i = 0; i < AttribCount(); ++i)
    {   
        R3DData::Attrib* attrib = GetAttrib(i);

        if(attrib.type == R3D_POSITION)
        {
            
        }
        else if(attrib.type == R3D_NORMAL)
        {
            
        }
        else if(attrib.type == R3D_TANGENT)
        {
            
        }
        else if(attrib.type == R3D_BITANGENT)
        {
            
        }
        else if(attrib.type == R3D_UV)
        {
            
        }
        else if(attrib.type == R3D_COLOR)
        {
            
        }
        else if(attrib.type == R3D_BONE)
        {
            
        }
        else if(attrib.type == R3D_WEIGHT)
        {
            
        }
        else if(attrib.type == R3D_INDEX)
        {
            
        }
    }
    
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