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

void GFXShader::Compile(std::string source)
{        
    int version = glsl_version[GFXVersion()];
    
    source = "#version " + std::to_string(version) + "\n" + source;
    
    const char* c_str = source.c_str();
    glShaderSource(shader, 1, &c_str, 0);
    glCompileShader(shader);
    
    // Check compilation status
    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 1)
    {
        std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shader, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        std::cout <<  &ShaderErrorMessage[0] << "\n";
    }
}

void GFXShader::Bind()
{
    GLProgram::Bind(this);
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