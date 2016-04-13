#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

#include "macro\macro_readers_def.h"

class GFXVertexShader
{
public:
    READERS
    (
        (ReadVERT) "vert"
    )
    bool ReadVERT(File file);
    
    static GFXVertexShader Create();
    
    void Bind();
private:
};

#endif