#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class OSCCommunication {
    // Osc
    ofxOscReceiver receiver;

	public:
		void setup();
		bool nextMessage(ofxOscMessage* message);
};