#version 330 core

// position variable passed to the shader from GPU at attribute position 0
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

// time
uniform float time;

// output the color
out vec3 ourColor;

void main() {
    // gl_Position is a predefined vec4 variable. Whatever is set to
    // gl_Position at the end of main will be used as the output of
    // the vertex shader
    gl_Position = vec4(aPos.x + sin(time), aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}
