#include "shader.hpp"
#include <glm/glm.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char **argv) {
    // Initialize glfw

    if (!glfwInit()) {
        std::cerr << "critical: failed to initialize glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window

    GLFWwindow *window =
        glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "critical: failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling ANY OpenGL functions

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "critical: failed to initialize glad" << std::endl;
        return -1;
    }

    // Setup viewport

    glViewport(0, 0, // This is the location of LOWER LEFT corner
               800, 600);

    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

    // Rendering

    Shader triangle_shader(std::string(ASSET_PATH) + "shaders/triangle_vs.glsl",
                           std::string(ASSET_PATH) +
                               "shaders/triangle_fs.glsl");

    Shader shape_shader(std::string(ASSET_PATH) + "shaders/shape_vs.glsl",
                        std::string(ASSET_PATH) + "shaders/shape_fs.glsl");

    float triangle_vertices[] = {
        // clang-format off
        // points           // colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
        // clang-format on
    };

    GLuint TriangleVBO;
    glGenBuffers(1, &TriangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);

    GLuint TriangleVAO;
    glGenVertexArrays(1, &TriangleVAO);
    glBindVertexArray(TriangleVAO);
    glBufferData(GL_ARRAY_BUFFER,           // type of the buffer
                 sizeof(triangle_vertices), // size of data in bytes
                 triangle_vertices,         // data
                 GL_STATIC_DRAW             // set once, use many times
    );

    glVertexAttribPointer(0,        // which vertex attribute (location = 0)
                          3,        // size of the vertex attribute
                          GL_FLOAT, // type of the data (vec* in GLSL is float)
                          GL_FALSE, // normalized?
                          6 * sizeof(float), // stride = 12
                          (void *)0          // offset = 0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float rect_vertices[] = {
        // clang-format off
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left
        // clang-format on
    };

    GLuint RectangleVBO;
    glGenBuffers(1, &RectangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, RectangleVBO);

    GLuint RectangleVAO;
    glGenVertexArrays(1, &RectangleVAO);
    glBindVertexArray(RectangleVAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0,        // which vertex attribute (location = 0)
                          3,        // size of the vertex attribute
                          GL_FLOAT, // type of the data (vec* in GLSL is float)
                          GL_FALSE, // normalized?
                          3 * sizeof(float), // stride = 12
                          (void *)0          // offset = 0
    );
    glEnableVertexAttribArray(0);

    unsigned int rect_indices[] = {
        // clang-format off
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
        // clang-format on
    };

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();

        triangle_shader.bind();
        triangle_shader.setFloat("time", time);
        glBindVertexArray(TriangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shape_shader.bind();
        shape_shader.setFloat("time", time);
        glBindVertexArray(RectangleVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
