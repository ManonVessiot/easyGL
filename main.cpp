// opengl = specification
// written in graphic drivers
// legacy opengl != modern opengl (shader)

// glew links opengl specification and the function in the graphic drivers

#include <GL/glew.h> // needs to be included first
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/TestClearColor.h"

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
/*
int main(int argc, char const *argv[])
{
    GLFWwindow * window;

    // Initialize the library
    if (!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    int height = 540;
    int width = 960;
    // glfwGetWindowSize(&width, &height);
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    glfwGetWindowSize(window, &width, &height);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(3);

    // Init glew after making context current 
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
        // buffer for data       
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        
        Shader shader("shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        // MVP matrix
        glm::mat4 proj = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 model2 = glm::mat4(1.0f);
        
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);

        view = glm::translate(view, glm::vec3(-0.5f, 0.2f, 0.0f));
        
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
        model2 = glm::translate(model2, glm::vec3(0.5f, 0.0f, 0.0f));
        model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);

        Texture texture("textures/zelda.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        // unbind
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        // ImGui : INIT
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        glm::vec3 cameraTranslation(0.005f, -0.002f, 0.0f);

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float incrementR = 0.02f;
        float incrementG = 0.01f;
        float incrementB = 0.03f;
        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            // Render here
            renderer.Clear();

            // ImGui : INIT NEW FRAME
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            updateColor(r, g, b, incrementR, incrementG, incrementB);

            shader.Bind();
            
            // move camera
            view = glm::translate(view, cameraTranslation);

            // first object
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);
            mvp = proj * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);            
            renderer.Draw(va, ib, shader);
            
            // second object
            shader.SetUniform4f("u_Color", 1, 1, 1, 1.0f);
            mvp = proj * view * model2;
            shader.SetUniformMat4f("u_MVP", mvp);            
            renderer.Draw(va, ib, shader);


            {
                // ImGui : WINDOW'S DATA
                ImGui::SliderFloat3("cameraTranslation", &cameraTranslation.x, -1.0f, 1.0f);
            }
            // ImGui : RENDER
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }
    // ImGui : DESTROY
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext(); // create a file

    glfwTerminate();
    return 0;
}*/


int main(int argc, char const *argv[])
{
    GLFWwindow * window;

    // Initialize the library
    if (!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    int height = 540;
    int width = 960;
    // glfwGetWindowSize(&width, &height);
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    glfwGetWindowSize(window, &width, &height);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(3);

    // Init glew after making context current 
    if (glewInit() != GLEW_OK){
        std::cout << "Error!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {   // use {} to "contains" our object and make sure, they are destroyed before glfwTerminate();

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        // ImGui : INIT
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        tests::TestClearColor test;

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            // Render here
            renderer.Clear();

            test.OnUpdate(0.0f);
            test.OnRender();

            // ImGui : INIT NEW FRAME
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            test.OnImGuiRender();

            // ImGui : RENDER
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }
    // ImGui : DESTROY
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext(); // create a file

    glfwTerminate();
    return 0;
}