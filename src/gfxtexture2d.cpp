#include "gfxtexture2d.h"

#include <vector>

#include "math3f.h"

GFXTexture2D GFXTexture2D::Create()
{
    GFXTexture2D texture;
    glGenTextures(1, &texture.buffer);
    return texture;
}

GFXTexture2D GFXTexture2D::Create(File file)
{
    GFXTexture2D texture = GFXTexture2D::Create();
    //float pixels[] = 
    //{ 0.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
    //  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f };
    vec4f pixels[4096];
    for(int i = 0; i < 4096; ++i)
    {
        pixels[i] = vec4f(rand()%1000 * 0.001f, rand()%1000 * 0.001f, rand()%1000 * 0.001f, 1.0f);
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return texture;
}

void GFXTexture2D::Use(unsigned int layer)
{
    glActiveTexture(GL_TEXTURE0 + layer);
    glBindTexture(GL_TEXTURE_2D, buffer);
}