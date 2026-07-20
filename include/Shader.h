#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
  public:
    // The constructor takes the file paths to the GLSL source code
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    // The destructor ensures the shader program is deleted from the GPU
    ~Shader();

    // NOTE: Declaring function as const (at the end) means that it can't modify
    //       class members.

    // Activates this specific shader program for the upcoming draw calls
    void Bind() const;

    // Deactivates the shader program
    void Unbind() const;

    // Utility functions to securely send data from the CPU to the GPU uniforms
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    GLuint m_RendererID;

    // An internal cache to prevent querying the GPU for uniform locations every
    // frame
    std::unordered_map<std::string, GLint> m_UniformLocationCache;

    // Interlan helper functions
    std::string ParseShaderFile(const std::string &filepath);
    GLuint CompileShader(GLenum type, const std::string &source);
    GLint GetUniformLocation(const std::string &name);
};
