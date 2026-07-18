#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const char *vertexShaderSource =
    "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 410 core\n"
    "out vec4 FragColor;"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.4f, 0.4f, 1.0f);\n"
    "}\0";

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Tell glfw which version of OpenGL state machine to initialize.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Requests a forward-compatible context on MacOS (critical)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL",
                                          nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the context of the given window current for the calling thread.
    glfwMakeContextCurrent(window);

    // Handle Retina High DPI Display
    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set initial viewport using the Retina pixel count
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define vertex data and buffers
    // clang-format off
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
  };
    // clang-format on

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

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
