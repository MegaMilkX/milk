#include "gfxcamera.h"

GFXCamera* GFXCamera::Create(Node* parent)
{
    return Node::Create(parent)->AddComponent<GFXCamera>();
}