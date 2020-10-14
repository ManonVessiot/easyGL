#pragma once

#include <GL/glew.h> 
#include <assert.h> 
#include <vector>

namespace easyGL {

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
        std::vector<VertexBufferElement> m_Element;
        unsigned int m_Stride;

        void Push_float(unsigned int count);
        void Push_uint(unsigned int count);
        void Push_uchar(unsigned int count);
    public:
        VertexBufferLayout()
            :m_Stride(0){}

        void Push(unsigned int type, unsigned int count);

        inline const std::vector<VertexBufferElement> GetElements() const { return m_Element; }
        inline unsigned int GetStride() const { return m_Stride; }
    };
}