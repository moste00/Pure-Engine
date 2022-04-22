#version 330 core

out vec4 frag_color;

//TODO: Define uniforms for the center and the radius
uniform vec2 center;
uniform float radius;

uniform vec4 inside_color;
uniform vec4 outside_color;

void main(){
    //TODO: Write code that will draw the circle
    if(sqrt(pow((gl_FragCoord.x - center[0]),2)+pow((gl_FragCoord.y - center[1]),2))<= radius){
        frag_color = inside_color;
    } else {
        frag_color = outside_color;
    }
}