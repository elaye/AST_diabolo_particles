#include "ofMain.h"
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	ofBackground(ofColor::black);

	osc.setup();

	post.init(ofGetWidth(), ofGetHeight());
	post.createPass<BloomPass>();

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
	fbo.begin();
		ofClear(0, 0, 0, 255);
	fbo.end();

	bloom.allocate(ofGetWidth(), ofGetHeight());
	//FXObject.allocate(ofGetWidth(), ofGetHeight());
	blur.allocate(ofGetWidth(), ofGetHeight());
	density.allocate(ofGetWidth(), ofGetHeight());

	blur.setFade(1);

	bloom.setPasses(1);
	//FXObject.load("shaders/emerge120_v2.frag");

	diaboloPosition = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
	leftHandPosition = ofPoint(ofGetWidth()/3, ofGetHeight()/3);
	rightHandPosition = ofPoint(ofGetWidth()*2/3, ofGetHeight()/3);

	gui = new ofxUISuperCanvas("Settings");        //Creates a canvas at (0,0) using the default width

	gui->addSpacer()->toggleColor();
    gui->addFPS(OFX_UI_FONT_SMALL);
    gui->addSpacer()->toggleColor();
	gui->addSlider("Min. Distance",0.0,1000.0,1000.0);
	gui->addSpacer()->toggleColor();
	velMultWidget = gui->addSlider("Velocity Mult.",0.0,1000.0,10.0);
	gui->addSpacer()->toggleColor();
	gui->addSlider("R",0.0,1.0,0.19);
	gui->addSpacer()->toggleColor();
	gui->addSlider("G",0.0,1.0,0.19);
	gui->addSpacer()->toggleColor();
	gui->addSlider("B",0.0,1.0,0.37);
	gui->addSpacer()->toggleColor();
	gui->addSlider("A",0.0,1.0,0.10);
	gui->addSpacer()->toggleColor();
	gui->addLabel("Settings filename :", OFX_UI_FONT_SMALL);
	textInputSave = gui->addTextInput("Filename", "settings");
	textInputSave->setAutoClear(false);
	gui->addLabelButton("Save", false);
	gui->addLabel("Load settings :", OFX_UI_FONT_SMALL);
	textInputLoad = gui->addTextInput("Filename", "settings");
	textInputLoad->setAutoClear(false);
	gui->addLabelButton("Load", false);
    //gui->addSpacer();

	gui->autoSizeToFitWidgets();
	ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
	gui->loadSettings("settings.xml");

}

//--------------------------------------------------------------
void testApp::update(){

	for(int i=0; i<2; i++){
		if(osc.nextMessage(&message)){
			if(message.getAddress() == "/tracking/joint/lefthand"){
				leftHandPosition = ofPoint(message.getArgAsFloat(0)*ofGetWidth(), (1-message.getArgAsFloat(1))*ofGetHeight());
			}
			if(message.getAddress() == "/tracking/joint/righthand"){
				rightHandPosition = ofPoint(message.getArgAsFloat(0)*ofGetWidth(), (1-message.getArgAsFloat(1))*ofGetHeight());
			}
			if(message.getAddress() == "/tracking/coord"){
				//cout << "x : " << message.getArgAsFloat(0) << " y : " << message.getArgAsFloat(1) << endl;
				diaboloPosition = ofPoint(message.getArgAsFloat(0)*ofGetWidth(), (1-message.getArgAsFloat(1))*ofGetHeight());
				diabolo.update(diaboloPosition);
			}
		}
	}

	particlesSystem.updateAttractorPosition(0, leftHandPosition);
	particlesSystem.updateAttractorPosition(1, diaboloPosition);
	particlesSystem.updateAttractorPosition(2, rightHandPosition);

	particlesSystem.update();

	fbo.begin();
		ofEnableAlphaBlending();
			ofFill();
			ofSetColor(0,0,0, 30);
			ofRect(0,0,ofGetWidth(),ofGetHeight());
		ofDisableAlphaBlending();
		ofNoFill();
		ofSetColor(255,255,255,255);
		particlesSystem.draw();
	fbo.end();

	ofPoint * diaboloAcc = diabolo.getAcc();
	//velMultWidget->setValue(diaboloAcc[0].length() * 10);

}

//--------------------------------------------------------------
void testApp::draw(){
	//ofSetColor(255,255,255);

	post.begin();
	 	fbo.draw(0,0);
	post.end();

	ofEnableAlphaBlending();
		if(gui->isVisible()){
			ofFill();
			ofSetColor(100, 100, 255, 100);
			ofRect(0,0,OFX_UI_GLOBAL_CANVAS_WIDTH,ofGetHeight());
		}
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key){
		case 'f':
			ofToggleFullscreen();
			break;
		case 's':
			if(!textInputLoad->isFocused() && !textInputSave->isFocused()){
				gui->toggleVisible();				
			}
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	//particlesSystem.moveAttractor(x, ofGetHeight()-y);
	//particlesSystem.moveAttractor(x, y);
	if(diaboloPosition.distance(ofPoint(x, ofGetHeight() - y)) < 50){
		diaboloPosition.x = x;
		diaboloPosition.y = ofGetHeight() - y;
		particlesSystem.updateAttractorPosition(1, diaboloPosition);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	textInputSave->setFocus(false);
	textInputLoad->setFocus(false);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::exit(){
    //gui->saveSettings("settings.xml");     
    delete gui;
} 
void testApp::guiEvent(ofxUIEventArgs &e){
	string name = e.getName();
    if(name == "Min. Distance"){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setMinDist(slider->getScaledValue());
    }
    if(name == "Velocity Mult."){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setVelMult(slider->getScaledValue());
    }
    if(name == "R"){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setR(slider->getScaledValue());
    }
    if(name == "G"){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setG(slider->getScaledValue());
    }
    if(name == "B"){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setB(slider->getScaledValue());
    }
    if(name == "A"){
        ofxUISlider *slider = e.getSlider();    
        //ofBackground(slider->getScaledValue());
    	particlesSystem.setA(slider->getScaledValue());
    }
    if(name == "Save"){
    	string filename;
    	filename = textInputSave->getTextString() + ".xml";
    	gui->saveSettings(filename);
    	ofLog() << "Settings saved in data/" << filename << endl;
    }
    if(name == "Load"){
    	string filename;
    	filename = textInputLoad->getTextString() + ".xml";
    	gui->loadSettings(filename);
    	ofLog() << "Settings loaded from data/" << filename << endl;
    }
}
