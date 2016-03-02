#include "node.h"

Node* Node::Create(Node* parent)
{
    Node* node = new Node();
    node->parent = parent;
    parent->children.insert(node);    
    return node;
}