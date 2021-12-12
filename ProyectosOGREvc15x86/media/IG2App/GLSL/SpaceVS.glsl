#version 330 core

in vec4 vertex;  // atributos de los vértices a procesar
in vec2 uv0;     // coordenadas de textura

uniform mat4 modelViewProjMat; // constante de programa
uniform float st;

out vec2 vUv0;  // out del vertex shader
out vec2 vUv1;  // out del vertex shader


//Pilla todos vertices
void main() {
    vUv0 = uv0;
    vUv1 = uv0;

    //Factores de escala
    float a = 0.3; //Range scale, too much or too little
    float b = -1.0; //Range between -1 , 1
    float ZF = st* a + b; 
    //Se escala
    float scaleAnchor = 0.5; //Scale point from where to scale
    
    vUv1.s = ((vUv0.s -  scaleAnchor) * ZF) + scaleAnchor;
	vUv1.t = ((vUv0.t - scaleAnchor) * ZF) + scaleAnchor;

    gl_Position = modelViewProjMat * vertex; //obligatorio
}