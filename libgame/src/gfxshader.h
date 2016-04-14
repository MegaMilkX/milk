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

class GFXShader
{
public:
    GFXShader : shader(0) {}
    void Compile(std::string source);
    void Bind();

    void Uniform(std::string& name, float value);
    void Uniform(std::string& name, vec2f& value);
    void Uniform(std::string& name, vec3f& value);
    void Uniform(std::string& name, vec4f& value);
    void Uniform(std::string& name, int value);
    void Uniform(std::string& name, vec2i& value);
    void Uniform(std::string& name, vec3i& value);
    void Uniform(std::string& name, vec4i& value);
    void Uniform(std::string& name, unsigned int value);
    void Uniform(std::string& name, vec2ui& value);
    void Uniform(std::string& name, vec3ui& value);
    void Uniform(std::string& name, vec4ui& value);
    void Uniform(std::string& name, mat3f& value);
    void Uniform(std::string& name, mat4f& value);
protected:
    unsigned int shader;
};

class GFXShaderVertex : public GFXShader
{
public:
    //Required by RESOURCE SYSTEM
    READERS
    (
        (ReadVERT) "vert"
    )
    bool ReadVERT(File file);
    
    static GFXShaderVertex Create()
    {
        GFXShaderVertex gfxshader;
        gfxshader.shader = glCreateShader(GL_VERTEX_SHADER);
        return gfxshader;
    }
    //
    
    void Bind();
private:
};

class GFXShaderPixel : public GFXShader
{
public:
    //Required by RESOURCE SYSTEM
    READERS
    (
        (ReadFRAG) "frag"
    )
    bool ReadFRAG(File file);
    
    static GFXShaderPixel Create()
    {
        GFXShaderPixel gfxshader;
        gfxshader.shader = glCreateShader(GL_FRAGMENT_SHADER);
        return gfxshader;
    }
    //
    
    void Bind();
private:
};

#endif