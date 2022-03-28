#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the side-length
uniform vec2 center;
uniform float side_length;


uniform vec4 inside_color;
uniform vec4 outside_color;

//uniforms are the same across the entire frame draw.

void main(){
    //TODO: Write code that will draw the square

    //x coor must not exceed horizontal borders of the square, y coor must not exceed the vertical borders of the square
    if(abs(gl_FragCoord.x - center[0]) <= side_length/2 && abs(gl_FragCoord.y - center[1]) <= side_length/2){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}