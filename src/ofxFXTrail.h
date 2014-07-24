#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxFXTrail : public ofxFXObject {

	public:
		
		ofxFXTrail(){
				internalFormat = GL_RGBA32F_ARB;
				
				// In this example the tex0 it's more like a backbuffer 
				load("shaders/identity.frag");
				//shader.load("shaders/identity");
		};

		void update(){

			ofPushStyle();
			
			ofSetColor(255);
			pingPong.dst->begin();
			//ofClear(0,0);
			//textures[0].draw(0,0);
			shader.begin();
				shader.setUniformTexture("tex0", pingPong.src->getTextureReference(), 0);
				renderFrame();
			shader.end();

			pingPong.dst->end();
			
			//for(int i = 0; i < passes; i++) {
					// pingPong.dst->begin();
					// ofClear(0,0);
					// shader.begin();
					// // In this example the tex0 it's more like a backbuffer 
					// shader.setUniformTexture("tex0", pingPong.src->getTextureReference(), 0);
					// //shader.setUniform1f("fade", fade);
					// renderFrame();
					// shader.end();
					// pingPong.dst->end();
					
					//pingPong.swap();
			//}
			
			// pingPong.swap();
			
			ofPopStyle();
		}
};