#pragma once

// clang-format off
#include <glad/glad.h>
// clang-format on

#include <string>

class Shader {
  public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

  private:
    GLuint m_program_id;

    std::string parseShaderFile(const std::string &filepath);
    GLuint compileShader(GLenum type, const std::string &source);
};
