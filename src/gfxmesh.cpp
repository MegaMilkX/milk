#include "gfxmesh.h"

#include "node.h"

GFXMesh* GFXMesh::Create(Node* parent)
{
    return Node::Create(parent)->AddComponent<GFXMesh>();
}

GFXMesh::GFXMesh()
{
    
}