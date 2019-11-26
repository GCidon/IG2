#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0;

out vec3 vWvertex; // en world space
out vec3 vWnormal;

out vec2 vUv0; // out del vertex shader

uniform mat4 model; // constante de programa
uniform mat4 view;
uniform mat4 proj;
uniform mat4 normalMat;
//uniform mat4 projection;


void main() {
    vUv0 = uv0;
    
    vec3 vWvertex = vec3(model * vertex); // en view space
    vec3 vWnormal = mat3(normalMat) * normal;

    gl_Position = proj * view * vec4(vWvertex, 1.0);
    //gl_Position = modelViewProjMat * vertex; // obligatorio
}