#pragma once

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <glm/glm.hpp>

#include <string>

class Shader {
  public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setVec4(const std::string &name, const glm::vec4 &vec) const;

  private:
    GLuint m_program_id;

    std::string parseShaderFile(const std::string &filepath);
    GLuint compileShader(GLenum type, const std::string &source);
};
