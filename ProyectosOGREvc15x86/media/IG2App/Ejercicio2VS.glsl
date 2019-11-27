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


void main() {
    
    vWvertex = vec3(model * vertex); // en view space
    vWnormal = mat3(transpose(inverse(model))) * normal;
    vUv0 = uv0;

    gl_Position = proj * view * vec4(vWvertex, 1.0);
    //gl_Position = modelViewProjMat * vertex; // obligatorio
}