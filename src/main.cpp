#include <DemoShaderLoader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <MeshObject.h>   

// Vertex + Color data
GLfloat vertices[] =
{
    // positions    // colors
     0.0f,  0.8f,   1.0f, 0.0f, 0.0f,
     0.8f, -0.8f,   0.0f, 1.0f, 0.0f,
    -0.8f, -0.8f,   0.0f, 0.0f, 1.0f
};

int main()
{
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
    glfwCreateWindow
    (
        640, 480, "RGB Triangle", nullptr, nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    Shader s1;
    s1.b_LoadShaderProgramFromFile
    (
        "resources/Sample.vert",
        "resources/Sample.frag"
    );

    // position + color
    GLuint layout[] = { 2, 3 }; 

    MeshObject triangle
    (
        vertices, 
        sizeof(vertices) / sizeof(GLfloat), 
        layout, 
        sizeof(layout) / sizeof(GLuint)
    );

    // Print OpenGL info
    std::cout << "OpenGL version: "
        << glGetString(GL_VERSION)
        << std::endl;

    std::cout << "GLSL version: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << std::endl;

    std::cout << "Renderer: "
        << glGetString(GL_RENDERER)
        << std::endl;

    std::cout << "Vendor: "
        << glGetString(GL_VENDOR)
        << std::endl;

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        s1.Bind();
        triangle.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    s1.Clear();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
