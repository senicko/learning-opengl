#include "Shader.h"
#include <cstring>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    // Read raw text from the physical files
    std::string vertexSource = ParseShaderFile(vertexPath);
    std::string fragmentSource = ParseShaderFile(fragmentPath);

    std::cout << "vertex_shader" << std::endl << vertexSource << std::endl;
    std::cout << "fragment_shader" << std::endl << fragmentSource << std::endl;

    // Compile individual shader files
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Create a new program object and get its reference id. Program object is
    // an object to which shader objects can be attached
    m_RendererID = glCreateProgram();

    // Attach compiled shaders to the created program object
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);

    // Link shaders attached to the created program object
    glLinkProgram(m_RendererID);

    int isLinked;

    // Returns GL_TRUE if the last link operation on program
    // was successfull
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE) {
        int maxLength;

        // Returns the number of characters in the information log for program
        // including the null terminator character
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
        char *infoLog = new char[maxLength];
        // Returns the information log for the specified program object.
        // Information log is updated when program object is linked or
        // validated.
        glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, infoLog);
        std::cerr << "Shader Linking Failed: " << infoLog << std::endl;

        delete[] infoLog;
    }

    // Free intermediate shader objects
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    // RAII principle: Destroy the GPU memory when object dies
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const {
    // Installs a program object as part of current rendering state
    glUseProgram(m_RendererID);
}
void Shader::Unbind() const { glUseProgram(0); }

std::string Shader::ParseShaderFile(const std::string &filepath) {
    // NOTE: This syntax runs constructor of std::ifstream and assigns it to
    //       stream variable
    std::ifstream stream(filepath);

    if (!stream.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl
                  << "Error: " << strerror(errno) << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    return buffer.str();
}

GLuint Shader::CompileShader(GLenum type, const std::string &source) {
    // Create an empty shader object and return its identifier by which we can
    // reference it later
    GLuint id = glCreateShader(type);

    const char *src = source.c_str();
    // Replace the source code in shader object
    glShaderSource(id,     // Target shader object
                   1,      // Number of elements in strings and length arrays
                   &src,   // Array of strings (shader source codes)
                   nullptr // Array of string lengths (nullptr means that each
                           // string is null terminated)
    );

    // Compiles source code strings that have been stored in the shader object
    // referenced by id
    glCompileShader(id);

    // TODO: Error handling

    return id;
}

GLint Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    // Uniform variable is a global variable that can be passed to a shader
    // by the user. glGetUniformLocation finds the location of the given uniform
    // variable for the specified program object
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());

    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!"
                  << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &matrix) {
    // Specify the value for the specified uniform variable for the current
    // program object
    glUniformMatrix4fv(
        GetUniformLocation(
            name),    // Location of the uniform variable to be modified
        1,            // This is a single matrix
        GL_FALSE,     // Transpose?
        &matrix[0][0] // Pointer to the matrix (it's first value in memory)
    );
}
