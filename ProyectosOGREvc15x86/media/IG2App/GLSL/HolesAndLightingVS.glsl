#version 330 core

in vec4 vertex;  // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0;     // coordenadas de textura 0

uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 normalMat;        // matriz inversa (normales)

out vec2 vUv0;  // out del vertex shader
out vec3 Normal;

//Pilla todos verticesQ
void main() {
    vUv0 = uv0; // se pasan las coordenadas de textura
    Normal = mat3(normalMat)*normal;
    gl_Position = modelViewProjMat * vertex; //obligatorio
}