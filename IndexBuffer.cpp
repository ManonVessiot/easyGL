#include "IndexBuffer.h"
#include "Renderer.h"

namespace easyGL {

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, unsigned int drawMode)
        : m_Count(count)
    {
        assert(sizeof(unsigned int) == sizeof(GLuint));
        
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, drawMode));

    }

    IndexBuffer::~IndexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void IndexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void IndexBuffer::WriteData(unsigned int offsetCount, unsigned int count, const void* data){
        m_Count = offsetCount + count;
        GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetCount * sizeof(unsigned int), count * sizeof(unsigned int), data));
    }
}