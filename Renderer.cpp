#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);    
}

bool GLLogCall(const char* function, const char* file, int line)
{
    bool gotError = false;
    while (GLenum error = glGetError()){
        gotError = true;
        cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << endl;
    }
    return gotError;
}



Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}


void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}