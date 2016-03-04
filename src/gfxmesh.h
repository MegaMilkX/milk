#ifndef _GFXMESH_H_
#define _GFXMESH_H_

#include "component.h"

class GFXMesh : public Component
{
public:
    static GFXMesh* Create(Node* parent);
    
    friend Node;
private:
    GFXMesh();
};

#endif