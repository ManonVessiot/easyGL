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

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTriangle.h"
#include "tests/TestSquare.h"
#include "tests/TestSquareAnimatedColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestMVP.h"
#include "tests/TestCube.h"
#include "tests/TestBatching.h"
#include "tests/TestBatchingDynamic.h"
#include "tests/TestModel.h"

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

        tests::Test* currentTest = nullptr;
        tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<tests::TestClearColor>("Clear Color");
        testMenu->RegisterTest<tests::TestTriangle>("Triangle");
        testMenu->RegisterTest<tests::TestSquare>("Square");
        testMenu->RegisterTest<tests::TestSquareAnimatedColor>("Square Animated Color");
        testMenu->RegisterTest<tests::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<tests::TestMVP>("MVP");
        testMenu->RegisterTest<tests::TestCube>("Cube");
        testMenu->RegisterTest<tests::TestBatching>("Batching");
        testMenu->RegisterTest<tests::TestBatchingDynamic>("Batching Dynamic");
        testMenu->RegisterTest<tests::TestModel>("TestModel");

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            // Render here
            renderer.Clear();

            // ImGui : INIT NEW FRAME
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            // ImGui : RENDER
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu){
            delete testMenu;
        }
    }
    // ImGui : DESTROY
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext(); // create a file

    glfwTerminate();
    return 0;
}