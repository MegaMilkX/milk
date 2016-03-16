//==================================================================================
// TODO: automatic #version XXX append to the beginning of source before compiling?
// version should be available in gfx after initialization
//==================================================================================

#ifndef _GFXSHADER_H_
#define _GFXSHADER_H_

#include <string>
#include <map>

#include "glextutil.h"
#include "math3f.h"
#include "filesystem\file.h"

class GFXShader
{
public:
    enum
    {
        PIXEL = GL_FRAGMENT_SHADER,
        VERTEX = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        COMPUTE = GL_COMPUTE_SHADER,
        TESS_CONTROL = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER
    };
    static GFXShader Create();
    static GFXShader Create(File file);
    GFXShader::GFXShader() : program(0){}
    void Compile(unsigned int type, std::string source);
    void Link();
    void Use();
    void Free();
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
private:
    std::map<unsigned int, unsigned int> shaders;
    unsigned int program;
};

#endif