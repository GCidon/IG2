#version 330 core

uniform sampler2D textura0; // tipo sampler2D para texturas 2D
uniform sampler2D textura1;
uniform vec4 InColor;
uniform vec4 OutColor;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader
in vec3 vWvertex;
in vec3 vWnormal;

uniform vec3 viewPos;

uniform vec3 lightPosition; // en world space
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 materialDiffuse; // datos del material
uniform vec3 materialSpecular;
uniform float materialShininess;


void main() {
    vec3 color0 = vec3(texture(textura0, vUv0)); // acceso a texel
    vec3 color1 = vec3(texture(textura1, vUv0)); // configuración
   
    if(color1.x > 0.6){
        discard;
    }
    // ambient
    vec3 ambient = lightAmbient * materialDiffuse;
    // diffuse
    vec3 norm = normalize(vWnormal);

    if(!gl_FrontFacing)
        norm = -norm;

    vec3 lightDir = lightPosition;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightDiffuse * materialDiffuse;
    // specular
    vec3 viewDir = normalize(viewPos - vWvertex);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular= spec * lightSpecular * materialSpecular;

    if(gl_FrontFacing){
        vec3 result= (diffuse) * (vec3(OutColor) * color0);
        fFragColor = vec4(result, 1.0);
    } else {
        vec3 result= (diffuse) * vec3(InColor);
        fFragColor = vec4(result, 1.0);
    }
}