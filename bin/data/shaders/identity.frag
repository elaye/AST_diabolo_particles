#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex0;

void main()
{
	gl_FragColor = texture2DRect(tex0, gl_TexCoord[0].st);
    //gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}