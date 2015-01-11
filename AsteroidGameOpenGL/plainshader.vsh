#version 330 core

uniform vec3 colour;
uniform mat4 MVP;

uniform float ZValue;

in vec2 position;

void main(){
    vec4 newPos =MVP * vec4(vec3(position,ZValue),1.0);
    gl_Position =newPos;
}