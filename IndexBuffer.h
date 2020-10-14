#pragma once

#include <GL/glew.h> 

namespace easyGL {
    class IndexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count, unsigned int drawMode = GL_STATIC_DRAW);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        void WriteData(unsigned int offsetCount, unsigned int count, const void* data);

        inline unsigned int GetCount() const {return m_Count;}
    };
}