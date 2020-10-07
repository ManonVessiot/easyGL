#include "Renderer.h"


void GLClearError(){
    while (glGetError() != GL_NO_ERROR);    
}

bool GLLogCall(const char* function, const char* file, int line){
    bool gotError = false;
    while (GLenum error = glGetError()){
        gotError = true;
        cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << endl;
    }
    return gotError;
}