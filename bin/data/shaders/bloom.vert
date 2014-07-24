#version 150

in vec4 position;
in vec2 texcoord;

uniform mat4 modelViewProjectionMatrix;

void main(){
	gl_Position = modelViewProjectionMatrix * position;
}