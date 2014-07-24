#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxFXBlending : public ofxFXObject {

	public:
		
		ofxFXBlending(){
				internalFormat = GL_RGBA32F_ARB;
				
				// In this example the tex0 it's more like a backbuffer 
				//load("shaders/emerge120_v2.frag");
				shader.load("shaders/blending");
		};

		void update(){

			ofPushStyle();
			
			ofSetColor(255);
			pingPong.src->begin();
			ofClear(0,0);
			textures[0].draw(0,0);
			pingPong.src->end();
			
			//for(int i = 0; i < passes; i++) {
					pingPong.dst->begin();
					ofClear(0,0);
					shader.begin();
					// In this example the tex0 it's more like a backbuffer 
					shader.setUniformTexture("tex0", pingPong.src->getTextureReference(), 0);
					//shader.setUniform1f("fade", fade);
					renderFrame();
					shader.end();
					pingPong.dst->end();
					
					//pingPong.swap();
			//}
			
			//pingPong.swap();
			
			ofPopStyle();
		}
};