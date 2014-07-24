#version 150

uniform sampler2DRect tex0;

in vec2 texCoordVarying;
out vec4 outputColor;

vec3 gu(vec4 a,vec4 b,float f){
    return mix(a.xyz,b.xyz,(f-a.w)*(1.0/(b.w-a.w)));
}

vec3 grad(float f){
    vec4 c01=vec4(0.0,0.0,0.0,0.00);
    vec4 c02=vec4(0.5,0.0,0.0,0.50);
    vec4 c03=vec4(1.0,0.0,0.0,0.55);
    vec4 c04=vec4(1.0,1.0,0.0,0.80);
    vec4 c05=vec4(1.0,1.0,1.0,1.00);
    return (f<c02.w)?gu(c01,c02,f):
    (f<c03.w)?gu(c02,c03,f):
    (f<c04.w)?gu(c03,c04,f):
    gu(c04,c05,f);
}

void main()
{
	float blurAmnt = 1.0;
    vec4 color = vec4(0,0,0,0);
        
    //color = texture(tex0, texCoordVarying);

    int i;
    int j;

    vec4 frag;

    float f;

    //if(texture(tex0, texCoordVarying).x > 0.5){
	    for(i = -1; i<1; i++){
	    	for(j = -1; j<1; j++){
	    		
	    			// frag = texture(tex0, texCoordVarying + vec2(i,j));
		    		// if(frag.x > 0.5){
		    		// 	color += vec4(0.1, 0.005, 0.005, 0.01);
		    		// }
		    		f += texture(tex0, texCoordVarying + vec2(i,j)).x;
		    		color += texture(tex0, texCoordVarying + vec2(i,j));
	    	}
	    }
	    vec3 g = grad(f/4.5);
	    outputColor = vec4(g.x, g.y, g.z, 1.0);
	// }
 //    else{
 //    	outputColor = vec4(0,0,0,0);
 //    }
    
}