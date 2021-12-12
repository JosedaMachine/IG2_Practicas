#version 330 core

uniform sampler2D texturaL;  // tipo sampler2D para texturas 2D
uniform sampler2D texturaM;  // ‐> unidades de textura (int)
uniform sampler2D texturaK;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
    // vec3 color = mix(colorL, colorM, BF) * intLuzAmb;
    // vec3 color = colorL * colorM * colorK;
    // mix ‐> (1‐BF).colorL + BF.colorM 
    if(colorL == vec3(1, 1, 1) ) {
        vec3 colorM = vec3(texture(texturaM, vUv0)); // configuración!
        fFragColor = vec4(colorM, 1.0); // out
    } else {
        vec3 colorK = vec3(texture(texturaK, vUv0));
        fFragColor = vec4(colorK, 1.0); // out
    }
}