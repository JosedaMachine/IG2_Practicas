#version 330 core
in vec2 vUv0;
in vec3 normalDirection;

uniform vec3 colorFront;
uniform vec3 colorBack;

uniform vec4 lightPos;      // direccion de la luz (considerada como vector)
uniform vec4 intLuz;        // intensidad de luz

uniform sampler2D texturaCorrosion;
uniform sampler2D texturaRiverBack; 
uniform sampler2D texturaMetalFront;

out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorCorrosion = vec3(texture(texturaCorrosion, vUv0));
    vec3 colorRiverBack = vec3(texture(texturaRiverBack, vUv0));
    vec3 colorMetalFront = vec3(texture(texturaMetalFront, vUv0));

    if(colorCorrosion.x > 0.6) discard;

    vec3 color;
    vec3 lightDir = normalize(vec3(lightPos));
    
    if(gl_FrontFacing){ 
        vec3 norm = normalize(normalDirection); //Normal del vertice en coordenadas mundiales glsl

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(intLuz) * diff;

        color =  colorFront * colorMetalFront* diffuse;
    }else{
        vec3 norm = -normalize(normalDirection); // invertimos las normales, ya que deberan ir hacia dentro
        
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(intLuz) * diff;

        color =  colorBack * colorRiverBack * diffuse;
    }

    fFragColor = vec4(color, 1.0);  
}