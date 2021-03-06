#include "VertexArray.h"
#include "Renderer.h"

namespace easyGL {
    
    VertexArray::VertexArray(){
        
        GLCall(glGenVertexArrays(1, &m_RendererID));
    }

    VertexArray::~VertexArray(){
		GLCall(glBindVertexArray(0));
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }


    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
        Bind();
        /* buffer for data */  
        vb.Bind();

        const auto& elements = layout.GetElements();
        intptr_t offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++){
            const auto& element = elements[i];

            /* layout : "explain" what the data is, in the buffer */
            GLCall(glEnableVertexAttribArray(i));
                /* link buffer with vao (GLFW_OPENGL_CORE_PROFILE) */
            GLCall(glVertexAttribPointer(i, element.count, element.type, 
                element.normalized, layout.GetStride(), (const void*)offset));
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    void VertexArray::Bind() const {
        GLCall(glBindVertexArray(m_RendererID));
    }

    void VertexArray::Unbind() const {
        GLCall(glBindVertexArray(0));
    }
}