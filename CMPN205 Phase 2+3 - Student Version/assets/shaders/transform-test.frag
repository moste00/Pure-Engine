#version 330 core


struct DirectionalLight{
    vec3 Direction;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Ambient;
}


in Varyings {
    vec3 position;
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
} fs_in;

out vec4 frag_color;

void main(){
    frag_color = vec4(0.5 * fs_in.normal + 0.5, 1.0);
}