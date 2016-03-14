#ifndef _GFXTEXTURE2D_H_
#define _GFXTEXTURE2D_H_

#include "glextutil.h"
#include "filesystem\filesystem.h"

class GFXTexture2D
{
public:
    static GFXTexture2D Create();
    static GFXTexture2D Create(File file);
    
    void Use(unsigned int layer = 0);
private:
  unsigned int buffer;
};

#endif