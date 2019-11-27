#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0;
in vec3 normal;

out vec2 vUv0; // out del vertex shader

out vec3 vWvertex; // en world space
out vec3 vWnormal;

uniform mat4 model; // constante de programa
uniform mat4 view;
uniform mat4 proj;
uniform mat4 normalMat;


void main() {
    vUv0 = uv0;
    
    vec3 vWvertex = vec3(model * vertex); // en view space
    vec3 vWnormal = mat3(normalMat) * normal;

    gl_Position = proj * view * vec4(vWvertex, 1.0);
    //gl_Position = modelViewProjMat * vertex; // obligatorio
}