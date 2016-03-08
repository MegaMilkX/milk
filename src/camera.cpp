#include "scene.h"

#include "camera.h"

Camera* Camera::Create(Node* scene)
{
    return Node::Create(scene)->AddEntity<Camera>();
}

void Camera::OnAttach(Node* parent)
{
    scene = parent->GetRoot();
    Entity::OnAttach(parent);
}

void Camera::Render(GFXTarget* target)
{
    // 1. Get all the renderables belonging to our scene
    // 2. Sort them by visibility
    // 3. Draw
}