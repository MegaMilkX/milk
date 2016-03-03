#ifndef _GFXCAMERA_H_
#define _GFXCAMERA_H_

#include "component.h"
#include "node.h"

class GFXCamera : public Component
{
public:
    //Creates a child node for parent argument with attached component created
    static GFXCamera* Create(Node* parent);
    
    friend Node;
private:
    GFXCamera(){}
};

#endif