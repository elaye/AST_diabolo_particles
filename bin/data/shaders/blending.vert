#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;
uniform mat4 modelViewProjectionMatrix;

varying vec4 vColor;

void main(){
	vColor = gl_Color;
	gl_Position = modelViewProjectionMatrix * gl_Vertex;
}