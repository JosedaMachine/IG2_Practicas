#version 330 core
in vec2 vUv0;
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
    if(gl_FrontFacing){ 
         color =  colorMetalFront;
    }else{
        color =  colorRiverBack;
    }

    fFragColor = vec4(color, 1.0);  
    
}