#include "VertexBufferLayout.h"

namespace easyGL {

    void VertexBufferLayout::Push_float(unsigned int count){
        m_Element.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void VertexBufferLayout::Push_uint(unsigned int count){
        m_Element.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void VertexBufferLayout::Push_uchar(unsigned int count){
        m_Element.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    void VertexBufferLayout::Push(unsigned int type, unsigned int count){
            switch (type)
            {
            case GL_FLOAT:          return Push_float(count);
            case GL_UNSIGNED_INT:   return Push_uint(count);
            case GL_UNSIGNED_BYTE:  return Push_uchar(count);
            }
            assert(false);
            return;
        }
}