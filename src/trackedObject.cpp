#include "trackedObject.h"

void trackedObject::setup(){
	t[0]=0;
	t[1]=0;

	p[0] = ofPoint(0, 0);
	p[1] = ofPoint(0, 0);
	v[0] = ofPoint(0, 0);
	v[1] = ofPoint(0, 0);
	a[0] = ofPoint(0, 0);
	a[1] = ofPoint(0, 0);
}

void trackedObject::update(ofPoint new_p){
	t[1] = t[0];
	t[0] = ofGetElapsedTimeMillis() / 1000;
	p[1] = p[0];
	p[0] = ofPoint(new_p.x, new_p.y);
	v[1] = v[0];
	v[0] = (p[1] - p[0]) / (t[1] - t[0]);
	a[1] = a[0];
	a[0] = (v[1] - v[0]) / (t[1] - t[0]);
}

void trackedObject::setPos(ofPoint new_p){
	p[0] = new_p;
}