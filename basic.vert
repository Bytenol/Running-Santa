#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 normal;
layout (location=3) in vec3 translation;
uniform mat4 mProjection, mView;

out vec2 o_texCoord;
out vec3 o_normal;

void main() {
    o_texCoord = texCoord;
    o_normal = normal;
    gl_Position = mProjection * mView * vec4(translation + position, 1.0);
}