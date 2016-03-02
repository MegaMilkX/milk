#ifndef _SCENE_H_
#define _SCENE_H_

#include "node.h"

class Scene : public Node
{
public:
    static Scene Create();
private:
    Scene();
};

#endif