#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the slope and the intercept
uniform float slope;
uniform float intercept;
uniform vec4 inside_color;
uniform vec4 outside_color;

void main(){
    //TODO: Write code that will draw the square
    if(gl_FragCoord.y <= slope*gl_FragCoord.x + intercept){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}