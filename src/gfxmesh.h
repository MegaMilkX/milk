#ifndef _GFXMESH_H_
#define _GFXMESH_H_

#include <vector>
#include "glextutil.h"
#include "resource.h"

template<typename T>
class GFXMesh : public Resource
{
public:
    GFXMesh();
    void SetVertices(std::vector<T> vertices);
    void SetIndices(std::vector<unsigned int> indices);
    void Render();
private:
    GLuint vao;
};

template<typename T>
void GFXMesh<T>::SetVertices(std::vector<T> vertices)
{
    if(vertices.size() == 0)
        return;
    
    glBindVertexArray(vao);
    vertex_buffer.Set(vertices);
    size_t offset = 0;
    for(int i = 0; i < T::attribCount; ++i)
    {
        glVertexAttribPointer(i, /*attrib index*/
                              T::attrib[i].elementCount, /*attrib element count*/ ATTRIB_ELEMENT_COUNT(T, i)
                              T::attrib[i].elementType, /*element type*/ ATTRIB_ELEMENT_TYPE(T, i);
                              GL_FALSE, /*normalize?*/
                              sizeof(T), /*stride*/
                              offset); /*offset*/
        offset += T::attrib[i].size; ATTRIB_SIZE(T, i);
        glEnableVertexAttribArray(i);
    }
    glVertexAttribPointer(0, 3,
}

#endif