#pragma once

#include <GL/glew.h> 
#include <assert.h> 
#include <iostream>
using namespace std;

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// macro for debug
#define GLCall(x) GLClearError();\
    x;\
    assert(!GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
    
public:
    Renderer();
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
