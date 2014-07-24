#pragma once

#include "ofMain.h"
#include "ofxFXObject.h"

class ofxFXDensity : public ofxFXObject {

	public:
		
		ofxFXDensity(){
				internalFormat = GL_RGBA32F_ARB;

				c1 = ofFloatColor(0.5,0.0,0.0);
				c2 = ofFloatColor(1.0,0.0,0.0);
				c3 = ofFloatColor(1.0,1.0,0.0);
				
				// In this example the tex0 it's more like a backbuffer 
				load("shaders/emerge120_v2.frag");
				 
		};

		void setColor(float h){

			c1.setBrightness(0.5);
			c2.setBrightness(1.0);
			c3.setBrightness(1.0);
			c1.setSaturation(1.0);
			c2.setSaturation(1.0);
			c3.setSaturation(1.0);
			c1.setHue(h);
			c2.setHue(h);
			c3.setHue(fmod(h + 60.0/360.0, 1.0));

		}

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
					shader.setUniform3f("c1", c1.r, c1.g, c1.b);
					shader.setUniform3f("c2", c2.r, c2.g, c2.b);
					shader.setUniform3f("c3", c3.r, c3.g, c3.b);
					renderFrame();
					shader.end();
					pingPong.dst->end();
					
					//pingPong.swap();
			//}
			
			//pingPong.swap();
			
			ofPopStyle();
		}
	
	protected:
		ofFloatColor c1;
		ofFloatColor c2;
		ofFloatColor c3;
};