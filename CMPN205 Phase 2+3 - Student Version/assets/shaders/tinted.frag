#version 330 core

in Varyings {
    vec4 color;
} fs_in;

out vec4 frag_color;




struct Light {
    int type;                     //0 -> Directional , 1 -> POINT, 2 -> SPOT
    vec3 position;
    vec3 ambient;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation; // x*d^2 + y*d + z
    vec2 cone_angles; // x: inner_angle, y: outer_angle
};




uniform vec4 tint;

void main(){
    //TODO: (Req 6) Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color
    frag_color = tint*fs_in.color ;
}