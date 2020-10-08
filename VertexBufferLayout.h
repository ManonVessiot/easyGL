#pragma once

#include <GL/glew.h> 
#include <assert.h> 
#include <vector>
using namespace std;

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type)
        {
        case GL_FLOAT:          return 4;
        case GL_UNSIGNED_INT:   return 4;
        case GL_BYTE:           return 1;
        }
        assert(false);
        return 0;
    }
};


class VertexBufferLayout
{
private:
    vector<VertexBufferElement> m_Element;
    unsigned int m_Stride;

    void Push_float(unsigned int count){
        m_Element.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void Push_uint(unsigned int count){
        m_Element.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void Push_uchar(unsigned int count){
        m_Element.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
public:
    VertexBufferLayout()
        :m_Stride(0){}

    void Push(unsigned int type, unsigned int count){
        switch (type)
        {
        case GL_FLOAT:          return Push_float(count);
        case GL_UNSIGNED_INT:   return Push_uint(count);
        case GL_UNSIGNED_BYTE:  return Push_uchar(count);
        }
        assert(false);
        return;
    }

    inline const vector<VertexBufferElement> GetElements() const { return m_Element; }
    inline unsigned int GetStride() const { return m_Stride; }
};
