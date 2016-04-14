#ifndef _GFXSHADER_H_
#define _GFXSHADER_H_

#include "filesystem\file.h"
#include "macro\macro_readers_def.h"

namespace GFXShader
{
    enum
    {
        PIXEL = 0,
        VERTEX = 1,
        GEOMETRY = 2,
        COMPUTE = 3,
        TESS_CONTROL = 4,
        TESS_EVALUATION = 5
    };
}

class GFXShaderVertex
{
public:
    //Required by RESOURCE SYSTEM
    READERS
    (
        (ReadVERT) "vert"
    )
    bool ReadVERT(File file);
    
    static GFXShaderVertex Create();
    //
    
    void Bind();
private:
};

class GFXShaderPixel
{
public:
    //Required by RESOURCE SYSTEM
    READERS
    (
        (ReadFRAG) "frag"
    )
    bool ReadFRAG(File file);
    
    static GFXShaderPixel Create();
    //
    
    void Bind();
private:
};

#endif