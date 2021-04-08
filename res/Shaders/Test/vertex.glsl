#version 330 core

uniform vec4 bbbb;

in vec2 position;

void main() {
    gl_Position = bbbb + vec4(position.xy, 0.5f, 1.0f);
}
