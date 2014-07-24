#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;

varying vec4 vColor;

void main()
{
	gl_FragColor = vColor;;
}