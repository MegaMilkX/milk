#ifndef _GFXMESH_H_
#define _GFXMESH_H_

#include <vector>
#include <map>
#include "glextutil.h"

#include "geometrybuffer.h"

#include "macro\macro_vertex_def.h"

#include "macro\macro_readers_def.h"

//#include "resourceobject.h"

//#include "filesystem\file.h"

//#include "util\r3ddata.h"

extern std::map<int, int> type_to_gltype;

class GFXMesh
{
public:
    READERS
    (
        (ReaderR3D) r3d,
        (ReaderFBX) fbx
    )
    
    enum
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };
    static GFXMesh Create(int usage = STATIC);
    static GFXMesh Create(File file, int usage = STATIC);
    GFXMesh() : vao(0) {}
    template<typename T>
    void SetVertices(std::vector<T> vertices);
    void SetIndices(std::vector<unsigned short> indices);
    void Bind()
    {
        glBindVertexArray(vao);
    }
    void Render()
    {
        Bind();
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
void GFXMesh::SetVertices(std::vector<T> vertices)
{
    if(vertices.size() == 0)
        return;
    
    Bind();
    
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

#endif