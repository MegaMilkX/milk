#include <vector>
#include <iostream>

#include "gfx.h"

#include "gfxshader.h"

std::map<int, int> glsl_version =
{ { 200, 110 },
  { 210, 120 },
  { 300, 130 },
  { 310, 140 },
  { 320, 150 },
  { 330, 330 },
  { 400, 400 },
  { 410, 410 },
  { 420, 420 },
  { 430, 430 },
  { 440, 440 },
  { 450, 450 } };

GFXShader GFXShader::Create()
{
    GFXShader shader;
    return shader;
}

GFXShader GFXShader::Create(File file)
{
    GFXShader shader;
    file.Seek(0, File::BEGIN);
    unsigned int bytesRead;
    void* data = file.Read(file.Size(), bytesRead);
    std::string source((const char*)data, bytesRead);
    shader.Compile(GFXShader::VERTEX, source);
    shader.Compile(GFXShader::PIXEL, source);
    shader.Link();
    return shader;
}

void GFXShader::Compile(unsigned int type, std::string source)
{
    if(shaders[type] != 0)
        glDeleteShader(shaders[type]);
    
    shaders[type] = glCreateShader(type);
    
    int version = glsl_version[GFXVersion()];
    
    switch(type)
    {
    case VERTEX:
        source = "#version " + std::to_string(version) + "\n#define _VERTEX_\n" + source;
        break;
    case PIXEL:
        source = "#version " + std::to_string(version) + "\n#define _FRAGMENT_\n" + source;
        break;
    }
    
    const char* c_str = source.c_str();
    glShaderSource(shaders[type], 1, &c_str, 0);
    glCompileShader(shaders[type]);
    
    // Check compilation status
    
    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shaders[type], GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaders[type], GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 1)
    {
        std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shaders[type], InfoLogLength, NULL, &ShaderErrorMessage[0]);
        std::cout <<  &ShaderErrorMessage[0] << "\n";
    }
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
    
    // Check the program
    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage[0] << "\n";
    }
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