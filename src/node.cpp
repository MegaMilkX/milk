#include "node.h"

Node::~Node()
{
    std::set<Node*>::iterator it = children.begin();
    for(it; it != children.end(); ++it)
    {
        delete (*it);
    }
    children.clear();
}

Node* Node::Create(Node* parent)
{
    Node* node = new Node();
    node->parent = parent;
    parent->children.insert(node);    
    return node;
}