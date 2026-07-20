#pragma once

#include <string>

// This avoids importing a whole GLFW header every time we import
// Application.h
struct GLFWwindow;

class Application {
  public:
    Application(const std::string &title, int width, int height);
    ~Application();

    // Starts infinite rendering loop
    void Run();

  private:
    bool InitializeWindow(const std::string &title, int width, int height);
    bool InitializeGraphicsAPI();

    GLFWwindow *m_Window;
    bool m_IsRunning;

    int m_Width;
    int m_Height;
};
