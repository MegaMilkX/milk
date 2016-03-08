#include "scene.h"

Scene Scene::Create()
{
    return Scene();
}

void Scene::AddEntity(int type, Entity* entity)
{
    entity_containers[type].push_back(entity);
}

Scene::Scene(){}