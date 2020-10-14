#pragma once

#include <GL/glew.h> 

namespace easyGL {
    class VertexBuffer
    {
    private:
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size, unsigned int drawMode = GL_STATIC_DRAW);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void WriteData(unsigned int offset, unsigned int size, const void* data);
    };
}
