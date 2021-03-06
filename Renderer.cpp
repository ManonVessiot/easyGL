#include "Renderer.h"

namespace easyGL {
    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);    
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        bool gotError = false;
        while (GLenum error = glGetError()){
            gotError = true;
            std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
        }
        return gotError;
    }

    void Renderer::Blend(bool enable){
        if (enable){
            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        }
        else
        {
            GLCall(glDisable(GL_BLEND));
        }
        
    }

    void Renderer::Depth(bool enable){
        if (enable){
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            GLCall(glDisable(GL_DEPTH_TEST));
        }
    }

    void Renderer::Clear(float r, float g, float b, float a )
    {
        GLCall(glClearColor(r, g, b, a));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
    {
        shader.Bind();
        va.Bind();
        ib.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}