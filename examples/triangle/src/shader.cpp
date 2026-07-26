#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexSource = parseShaderFile(vertexPath);
    std::string fragmentSource = parseShaderFile(fragmentPath);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vs);
    glAttachShader(m_program_id, fs);
    glLinkProgram(m_program_id);

    int isLinked;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE) {
        int maxLength;
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &maxLength);

        char *infoLog = new char[maxLength];
        glGetProgramInfoLog(m_program_id, maxLength, &maxLength, infoLog);

        std::cerr << "ERROR::SHADER::LINKING_FAILED" << infoLog << std::endl;
        delete[] infoLog;
    }

    // We no longer need shader objects after linking them
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() { glDeleteProgram(m_program_id); }

void Shader::bind() const { glUseProgram(m_program_id); }

void Shader::unbind() const { glUseProgram(0); }

GLuint Shader::compileShader(GLenum type, const std::string &source) {
    const char *src = source.c_str();

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int isCompiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE) {
        int maxLength;
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &maxLength);

        char *infoLog = new char[maxLength];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);

        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl
                  << infoLog;

        delete[] infoLog;
    }

    return id;
}

std::string Shader::parseShaderFile(const std::string &filePath) {
    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ " << filePath
                  << std::endl
                  << "error: " << strerror(errno) << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    return buffer.str();
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const {
    glUniform3f(glGetUniformLocation(m_program_id, name.c_str()), vec.x, vec.y,
                vec.z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &vec) const {
    glUniform4f(glGetUniformLocation(m_program_id, name.c_str()), vec.x, vec.y,
                vec.z, vec.w);
}
