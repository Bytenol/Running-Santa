#version 330 core

precision highp float;
in vec2 o_texCoord;
in vec3 o_normal;

uniform sampler2D u_texture;
out vec4 FragColor;

vec3 getDirectionalLight(vec3 normal) {
    vec3 dir = vec3(-0.4, 0.6, 1);
    float alpha = max(dot(dir, normalize(normal)), 0.5);
    return vec3(1, 1, 1) * alpha;
}

void main() {
    vec3 ambientLight = vec3(1, 1, 1) * 0.5;
    vec3 directionalLight = getDirectionalLight(o_normal);

    FragColor = texture(u_texture, o_texCoord);
    FragColor.rgb *= (ambientLight + directionalLight);
}