#version 330 core


uniform mat4 transform;       // = MVP
uniform vec3 eye;
uniform mat4 VP;
uniform mat4 M;
uniform mat4 M_IT;


layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

out Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 position;
    vec3 normal;
    vec3 view;
    vec3 world;
} vs_out;




void main(){
    vec3 world = (M * vec4(position, 1.0)).xyz;
//    gl_Position = VP * M * vec4(position, 1.0);            

    gl_Position = VP * vec4(world, 1.0);      //this is not getting the same result as MVP
   
//    gl_Position = transform * vec4(position, 1.0); 
    
//    gl_Position = P * vec4((V * vec4((M * vec4(position, 1.0)).xyz, 1.0)).xyz, 1.0);         //transform is MVP ready for direct use
    vs_out.position = position;
    vs_out.color = color;
    vs_out.tex_coord = tex_coord;
    vs_out.normal = normalize((M_IT * vec4(normal, 0.0)).xyz);
    vs_out.view = eye - world;
    vs_out.world = world;
}



