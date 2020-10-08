
#include "main.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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
    window = glfwCreateWindow(700, 700, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //
    glfwSwapInterval(3);

    /* Init glew after making context current */
    if (glewInit() != GLEW_OK){
        cout << "Error!" << endl;
    }
    cout << glGetString(GL_VERSION) << endl;
    {   // use {} to "contains" our object and make sure, they are destroyed before glfwTerminate();
    
        float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        /* buffer for data */        
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);


        /* index buffer object */
        IndexBuffer ib(indices, 6);
        
        Shader shader("shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        // unbind
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

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
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            shader.Bind();
            updateColor(r, g, b, incrementR, incrementG, incrementB);
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);

            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
