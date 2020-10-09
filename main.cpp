// opengl = specification
// written in graphic drivers
// legacy opengl != modern opengl (shader)

// glew links opengl specification and the function in the graphic drivers

#include <GL/glew.h> // needs to be included first
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

static void updateColor(float& r, float& g, float& b, float& incrementR, float& incrementG, float& incrementB){    
    if (r > 1.0f){
        incrementR *= -1;
    }
    else if (r < 0.0f){
        incrementR *= -1;
    }

    if (g > 1.0f){
        incrementG *= -1;
    }
    else if (g < 0.0f){
        incrementG *= -1;
    }

    if (b > 1.0f){
        incrementB *= -1;
    }
    else if (b < 0.0f){
        incrementB *= -1;
    }
    r += incrementR;
    g += incrementG;
    b += incrementB;
}

int main(int argc, char const *argv[])
{
    GLFWwindow * window;

    /* Initialize the library */
    if (!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int height = 960;
    int width = 540;
    // glfwGetWindowSize(&width, &height);
    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(3);

    /* Init glew after making context current */
    if (glewInit() != GLEW_OK){
        std::cout << "Error!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {   // use {} to "contains" our object and make sure, they are destroyed before glfwTerminate();
    
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        VertexArray va;
        /* buffer for data */        
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        
        Shader shader("shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        // projection matrix
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (width / miniSize) * borderLimit;
        float horizontalLimit = (height / miniSize) * borderLimit;
        glm::mat4 proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("textures/zelda.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        // unbind
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float incrementR = 0.02f;
        float incrementG = 0.01f;
        float incrementB = 0.03f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            updateColor(r, g, b, incrementR, incrementG, incrementB);

            shader.Bind();
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
