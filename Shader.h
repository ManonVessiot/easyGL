#pragma once

#include <unordered_map>

#include <string>
using namespace std;


struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};

class Shader
{
private:
    string m_FilePath;
    unsigned int m_RendererID;
    // cahcing for uniforms
    unordered_map<string, unsigned int> m_UniformLocationCache;
public:
    Shader(const string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1f(const string& name, float v0);
    void SetUniform2f(const string& name, float v0, float v1);
    void SetUniform3f(const string& name, float v0, float v1, float v2);
    void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader(const string& filepath);
    unsigned int CompileShader(unsigned int type, const string& source);
    unsigned int CreateShader(const string& verterShader, const string& fragmentShader);
    unsigned int GetUniformLocation(const string& name);
};
