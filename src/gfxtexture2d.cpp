#include "gfxtexture2d.h"

#include <vector>

GFXTexture2D GFXTexture2D::Create()
{
    GFXTexture2D texture;
    glGenTextures(1, &texture.buffer);
    return texture;
}

GFXTexture2D GFXTexture2D::Create(File file)
{
    GFXTexture2D texture = GFXTexture2D::Create();
    float pixels[] = 
    { 0.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, pixels);
    
    return texture;
}

void GFXTexture2D::Use(unsigned int layer)
{
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, buffer);
}