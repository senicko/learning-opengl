#version 330 core

// Declare the output variable of type vec4
// that represents the color
out vec4 FragColor;

// The input variable from the vertex shader
uniform vec4 ourColor;

void main() {
    FragColor = ourColor;
}
