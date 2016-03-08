#include "gfxshader.h"

GFXShader GFXShader::Create()
{
    GFXShader shader;
    return shader;
}

void GFXShader::Compile(unsigned int type, std::string source)
{
    if(shaders[type] != 0)
        glDeleteShader(shaders[type]);
    
    shaders[type] = glCreateShader(type);
    
    const char* c_str = source.c_str();
    glShaderSource(shaders[type], 1, &c_str, 0);
    glCompileShader(shaders[type]);
}

void GFXShader::Link()
{
    if(program != 0)
        glDeleteProgram(program);
        
    program = glCreateProgram();
    std::map<unsigned int, unsigned int>::iterator it = shaders.begin();
    
    for(it; it != shaders.end(); ++it)
        glAttachShader(program, it->second);
        
    glLinkProgram(program);
}

void GFXShader::Use()
{
    glUseProgram(program);
}

void GFXShader::Free()
{
    glDeleteProgram(program);
    std::map<unsigned int, unsigned int>::iterator it = shaders.begin();
    for(it; it != shaders.end(); ++it)
    {
        glDeleteShader(it->second);
    }
    shaders.clear();
}

void GFXShader::Uniform(std::string& name, float value){ glUniform1f(glGetUniformLocation(program, name.c_str()), value); }
void GFXShader::Uniform(std::string& name, vec2f& value){ glUniform2f(glGetUniformLocation(program, name.c_str()), value.x, value.y); }
void GFXShader::Uniform(std::string& name, vec3f& value){ glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z); }
void GFXShader::Uniform(std::string& name, vec4f& value){ glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w); }
void GFXShader::Uniform(std::string& name, int value){ glUniform1i(glGetUniformLocation(program, name.c_str()), value); }
void GFXShader::Uniform(std::string& name, vec2i& value){ glUniform2i(glGetUniformLocation(program, name.c_str()), value.x, value.y); }
void GFXShader::Uniform(std::string& name, vec3i& value){ glUniform3i(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z); }
void GFXShader::Uniform(std::string& name, vec4i& value){ glUniform4i(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w); }
void GFXShader::Uniform(std::string& name, unsigned int value){ glUniform1ui(glGetUniformLocation(program, name.c_str()), value); }
void GFXShader::Uniform(std::string& name, vec2ui& value){ glUniform2ui(glGetUniformLocation(program, name.c_str()), value.x, value.y); }
void GFXShader::Uniform(std::string& name, vec3ui& value){ glUniform3ui(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z); }
void GFXShader::Uniform(std::string& name, vec4ui& value){ glUniform4ui(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w); }
void GFXShader::Uniform(std::string& name, mat3f& value){ glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, (float*)&value); }
void GFXShader::Uniform(std::string& name, mat4f& value){ glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, (float*)&value); }
