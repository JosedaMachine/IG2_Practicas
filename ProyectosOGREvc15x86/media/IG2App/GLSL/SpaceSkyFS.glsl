#version 330 core

uniform sampler2D texturaAlbedo;  // tipo sampler2D para texturas 2D
uniform sampler2D texturaLight;  // ‐> unidades de textura (int)
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorAlbedo = vec3(texture(texturaAlbedo, vUv0));
    vec3 colorLight = vec3(texture(texturaLight, vUv0));
    vec3 color = colorAlbedo * colorLight;
    fFragColor = vec4(color, 1.0);
}