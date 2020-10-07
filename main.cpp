
#include "main.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};


static ShaderProgramSource ParseShader(const string& filepath){
    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos){
            if (line.find("vertex") != string::npos){
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else if ((int)type != -1)
        {
            ss[(int)type] << line << "\n";
        }        
    }
    return {ss[0].str(), ss[1].str()};

}

static unsigned int CompileShader(unsigned int type, const string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

// verterShader & fragmentShader = actual source code
static unsigned int CreateShader(const string& verterShader, const string& fragmentShader){
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, verterShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        /* buffer for data */
        
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        /* layout : "explain" what the data is, in the buffer */
        GLCall(glEnableVertexAttribArray(0));
            /* link buffer with vao (GLFW_OPENGL_CORE_PROFILE) */
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        /* index buffer object */
        IndexBuffer ib(indices, 6);
        
        ShaderProgramSource source = ParseShader("shaders/Basic.shader");
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        GLCall(glUseProgram(shader));

        int location = glGetUniformLocation(shader, "u_Color");
        assert((location != -1));
        GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

        // unbind
        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));





        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float incrementR = 0.05f;
        float incrementG = 0.02f;
        float incrementB = 0.08f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            GLCall(glUseProgram(shader));
            updateColor(r, g, b, incrementR, incrementG, incrementB);
            GLCall(glUniform4f(location, r, g, b, 1.0f));

            GLCall(glBindVertexArray(vao));
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}
