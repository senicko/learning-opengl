#version 330 core

layout(location = 0) in vec3 aPos;

void main() {
    // gl_Position is a predefined vec4 variable. Whatever is set to
    // gl_Position at the end of main will be used as the output of
    // the vertex shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
