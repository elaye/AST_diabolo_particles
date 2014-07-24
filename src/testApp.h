#pragma once

#include "ofMain.h"
#include "ParticlesSystem.h"
#include "ofxPostProcessing.h"
#include "ofxBloom.h"
#include "ofxBlur.h"
#include "ofxGaussianBlur.h"
#include "ofxGlow.h"
#include "ofxUI.h"
#include "OSCCommunication.h"
#include "ofxFXDensity.h"
#include "trackedObject.h"

class testApp : public ofBaseApp{

	ParticlesSystem particlesSystem;

	ofFbo fbo;

	ofxPostProcessing post;

	ofxGlow bloom;
	ofxBlur blur;
	ofxFXObject FXObject;

	ofxFXDensity density;

	ofxUISuperCanvas *gui;

	ofxUITextInput *textInputSave;
	ofxUITextInput *textInputLoad;
	ofxUISlider * velMultWidget;

	ofPoint diaboloPosition;
	ofPoint leftHandPosition;
	ofPoint rightHandPosition;

	trackedObject diabolo;

	OSCCommunication osc;
	ofxOscMessage message;

    //ofEasyCam cam;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void exit(); 
		void guiEvent(ofxUIEventArgs &e);
		
};
