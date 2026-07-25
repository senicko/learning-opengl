// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

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

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Double buffering. Rendering commands draw to back buffer, and front
        // buffer is being rendered. When rendering is finished  buffers are
        // swapped
        glfwSwapBuffers(window);
        // Pool events like keyboard or mouse.
        glfwPollEvents();
    }

    // Cleanup

    glfwTerminate();
    return 0;
}
