#version 330 core

in vec2 position;
in vec3 color;

out vec4 ccolor;

void main() {
    gl_Position = vec4(position.xy, 0.5f, 1.0f);
    ccolor = vec4(color.xyz, 1.0f);
}
