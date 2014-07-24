#version 150
#extension GL_ARB_texture_rectangle : enable  

uniform sampler2DRect tex0;  

in vec2 texCoordVarying;

out vec4 fragColor;

void main(){ 
  vec4 sum = vec4(0); 
  vec2 st = texCoordVarying.st; 
  int j,i; 
  for( i= -4 ;i < 4; i++){ 
  for (j = -3; j < 3; j++){ 
          sum += texture2DRect(tex0, st + vec2(j, i)*0.004) * 0.25; 
      } 
  } 
   
  if (texture2DRect(tex0, st).r < 0.3){ 
      fragColor = sum * sum * 0.012 + texture2DRect(tex0, st); 
  } else { 
      if (texture2DRect(tex0, st).r < 0.5){ 
          fragColor = sum * sum * 0.009 + texture2DRect(tex0, st); 
      } else { 
          fragColor = sum * sum * 0.0075 + texture2DRect(tex0, st); 
      } 
  } 
}