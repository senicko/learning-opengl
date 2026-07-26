#version 330 core

// position variable passed to the shader from GPU at attribute position 0
layout(location = 0) in vec3 aPos;

uniform float time;

void main() {
    // gl_Position is a predefined vec4 variable. Whatever is set to
    // gl_Position at the end of main will be used as the output of
    // the vertex shader
    gl_Position = vec4(aPos.x + sin(time), aPos.y, aPos.z, 1.0);
}
