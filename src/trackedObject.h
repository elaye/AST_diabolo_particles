#pragma once

#include "ofMain.h"
#include "boost/signal.hpp"
#include "boost/bind.hpp"

class trackedObject {

	float t[2];

	ofPoint p[2];
	ofPoint v[2];
	ofPoint a[2];

	string type; //leftHand, rightHand, diabolo

	public:

		void setup();
		void update(ofPoint new_p);

		ofPoint* getPos() {return p;}
		ofPoint* getVel() {return v;}
		ofPoint* getAcc() {return a;}

		void setPos(ofPoint new_p);
};