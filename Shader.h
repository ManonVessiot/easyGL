#pragma once

#include <unordered_map>

#include <string>

#include <glm/glm.hpp>

namespace easyGL {

    class Shader
    {
    private:
        unsigned int m_RendererID;
        // caching for uniforms
        std::unordered_map<std::string, int> m_UniformLocationCache;
    public:
        Shader(const std::string& verterShader, const std::string& fragmentShader);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int v0);

        void SetUniform1f(const std::string& name, float v0);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

        void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);
        void SetUniform1iv(const std::string& name, int count, const int* v0);
        void SetUniform1fv(const std::string& name, int count, const float* v0);
        

    private:
        unsigned int CompileShader(unsigned int type, const std::string& source) const;
        unsigned int CreateShader(const std::string& verterShader, const std::string& fragmentShader) const;
        int GetUniformLocation(const std::string& name);
    };
}