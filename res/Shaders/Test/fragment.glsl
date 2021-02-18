#version 330 core

in vec4 position;
in vec4 ccolor;

out vec4 outColor;

void main() {
    outColor = ccolor;
}
