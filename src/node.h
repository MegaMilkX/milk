#ifndef _NODE_H_
#define _NODE_H_

#include <set>
#include <map>

#include "typeid.h"
#include "component.h"

class Node
{
public:
    virtual ~Node();
    template<typename T>
    T* AddComponent();
    template<typename T>
    T* GetComponent();

    static Node* Create(Node* parent);
private:
    Node* parent;
    std::set<Node*> children;
    
    std::map<int, Component*> components;
};

template<typename T>
T* Node::AddComponent()
{
    if(components.find(TypeInfo<T>::GetId()) != components.end())
        return 0;
        
    T* t = new T();
    t->parent = this;
    components.insert(std::make_pair(TypeInfo<T>::GetId(), t));
    return t;
}
template<typename T>
T* Node::GetComponent()
{
    std::map<int, Component*>::iterator it = components.find(TypeInfo<T>::GetId());
    if(it != components.end())
        return it->second;
    else
        return 0;
}

#endif