#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Node;
class Component
{
public:
    virtual ~Component(){}
    
    friend Node;
protected:
    Component(){}
    
    Node* parent;
};

#endif