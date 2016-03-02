#ifndef _NODE_H_
#define _NODE_H_

#include <set>

class Node
{
public:
    template<typename T>
    T* AddComponent();
    template<typename T>
    T* GetComponent();

    static Node* Create(Node* parent);
private:
    Node* parent;
    std::set<Node*> children;
};

#endif