#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace easyGL {

    Shader::Shader(const std::string& verterShader, const std::string& fragmentShader)
        :m_RendererID(0)
    {
        m_RendererID = CreateShader(verterShader, fragmentShader);
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(m_RendererID));
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const{
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE){
            int lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* message = (char*)alloca(lenght * sizeof(char));
            glGetShaderInfoLog(id, lenght, &lenght, message);
            std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << "message : ";
            std::cout << message << std::endl << std::endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    unsigned int Shader::CreateShader(const std::string& verterShader, const std::string& fragmentShader) const{
        unsigned int program = glCreateProgram();

        unsigned int vs = CompileShader(GL_VERTEX_SHADER, verterShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& name, int v0)
    {
        GLCall(glUniform1i(GetUniformLocation(name), v0));
    }

    void Shader::SetUniform1f(const std::string& name, float v0)
    {
        GLCall(glUniform1f(GetUniformLocation(name), v0));
    }

    void Shader::SetUniform2f(const std::string& name, float v0, float v1)
    {
        GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
    }

    void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
    {
        GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 matrix)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    void Shader::SetUniform1iv(const std::string& name, int count, const int* v0)
    {
        GLCall(glUniform1iv(GetUniformLocation(name), count, v0));
    }
    void Shader::SetUniform1fv(const std::string& name, int count, const float* v0)
    {
        GLCall(glUniform1fv(GetUniformLocation(name), count, v0));
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
            return m_UniformLocationCache[name];
        }

        GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1){
            std::cout << "Warning : uniform '" << name << "' doesn't exist!" << std::endl; 
        }
        m_UniformLocationCache[name] = location;
        
        return location;
    }
}