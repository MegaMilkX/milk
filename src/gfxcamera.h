#ifndef _GFXCAMERA_H_
#define _GFXCAMERA_H_

#include "node.h"

class GFXCamera
{
public:
    //Creates a child node for parent argument with attached component created
    static GFXCamera* Create(Node* parent);
private:
    GFXCamera(){}
};

#endif