#version 330 core

uniform mat4 projectionMatrix;

in vec2 position;

void main() {
    gl_Position = projectionMatrix * vec4(position.xy, 0.5f, 1.0f);
}
