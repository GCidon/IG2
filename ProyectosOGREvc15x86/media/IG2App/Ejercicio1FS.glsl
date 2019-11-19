#version 330 core

uniform sampler2D textura0; // tipo sampler2D para texturas 2D
uniform sampler2D textura1;
uniform float FB; // blending factor
uniform float intLuzAmb; // luz ambiente
in vec2 vUv0; // out del vertex shader
in vec2 vUv1;
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 color0 = vec3(texture(textura0, vUv0)); // acceso a texel
    vec3 color1 = vec3(texture(textura1, vUv0)); // configuración
    //vec3 color1 = vec3(texture(textura1, vUv1)); // configuración
    vec3 color = mix(color0, color1, FB);// * intLuzAmb;
    fFragColor = vec4(color, 1.0);
}