#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "entity.h"
#include "node.h"

class Renderable : public Entity
{
public:
    static Renderable* Create(Node* scene);
    
    void OnAttach(Node* parent);
    
    friend Node;
private:
    Renderable(){}
};

#endif