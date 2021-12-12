#version 330 core
in vec2 vUv0;
in vec2 vUv1;
uniform sampler2D texturaLight;
uniform sampler2D texturaAlbedo; 
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorLight = vec3(texture(texturaLight, vUv0));
    vec3 colorAlbedo = vec3(texture(texturaAlbedo, vUv1));
    vec3 color = colorAlbedo * colorLight;
    fFragColor = vec4(color, 1.0);
}