#version 330 core

// The input variable from the vertex shader
in vec3 ourColor;

// Declare the output variable of type vec4 that represents
// the color. Note that fs will interpolace this value thus
// we'll get this shading like effect.
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}
