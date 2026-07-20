#define GLFW_INCLUDE_NONE

#include "Application.h"
#include "Shader.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

Application::Application(const std::string &title, int width, int height)
    : m_Window(nullptr), m_IsRunning(false), m_Width(width), m_Height(height) {
    if (InitializeWindow(title, width, height) && InitializeGraphicsAPI()) {
        m_IsRunning = true;
    }
}

Application::~Application() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }

    glfwTerminate();
}

bool Application::InitializeWindow(const std::string &title, int width,
                                   int height) {
    if (!glfwInit()) {
        std::cerr << "Critical Error: Failed to initialize GLFW framework."
                  << std::endl;
    }

    // Configure OpenGL 4.1 profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_Window) {
        std::cerr << "Critical Error: Failed to create OS window." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    int frameBufferWidth, frameBufferHeight;

    glfwGetFramebufferSize(m_Window, &frameBufferWidth, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(
        m_Window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

    return true;
}

bool Application::InitializeGraphicsAPI() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr
            << "Critical Error: Failed to initialize GLAD extension wrangled."
            << std::endl;
        return false;
    }

    // Specify lower left corner of the viewport and its width and height
    glViewport(0, 0, m_Width, m_Height);

    // Enable GL_DEPTH_TEST server-side GL capability which causes GL to do
    // depth comparisons and update the depth buffer
    glEnable(GL_DEPTH_TEST);

    return true;
}

void Application::Run() {
    const std::string vertexPath = "assets/shaders/triangle_vs.glsl";
    const std::string fragmentPath = "assets/shaders/triangle_fs.glsl";

    Shader triangleShader(vertexPath, fragmentPath);

    // Define vertices
    float vertices[] = {
        // clang-format off
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        // clang-format on
    };

    // VBO (Vertex Buffer Object) Stores raw arrays of geometric data in GPU,
    // like vertex positions, colors or UV coordinates. memory.
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // VAO (Vertex Array Object) defines how to interpret and access that raw
    // VBO data. It remembers layout, data types and buffer bindings.
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO buffer

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(vertices), vertices,
        GL_STATIC_DRAW); // Create a datastore for the currently bound buffer

    GLuint attrib_location = 0; // Index of the generic vertex attribute
    glVertexAttribPointer(
        attrib_location,
        3, // Number of components per generic vertex attribute (1, 2, 3, 4)
        GL_FLOAT, // Type for each component in the array
        GL_FALSE, // Specifies whether fixed-point types should be normalized
        3 * sizeof(float), // Specifies the byte offset between consecutive
                           // generic vertex attributes
        (void *)0 // Offset of the first component of the first generic vertex
                  // attribute
    );
    glEnableVertexAttribArray(attrib_location);

    while (m_IsRunning && !glfwWindowShouldClose(m_Window)) {
        // Poll and process events
        glfwPollEvents();

        // Specify RGBA values used when color buffers are cleared
        glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
        // Clear buffers, in that case COLOR_BUFFER and DEPTH_BUFFER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangleShader.Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(m_Window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
