#ifndef _GFXSHADER_H_
#define _GFXSHADER_H_

#include "math3f.h"

#include "filesystem\file.h"
#include "macro\macro_readers_def.h"

class GFXShader
{
public:
    READERS
    (
        (ReadShader) "shader"
    )
    bool ReadShader(File file)
    {
        return true;
    }
    
    GFXShader() : program(0) {}
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
    unsigned int program;
};

#endif