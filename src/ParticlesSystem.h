#pragma once

#include "ofMain.h"

// #define NUM_PARTICLES 500*500
#define NUM_PARTICLES 100*1000

class Particle {
	float m;
	ofPoint p;
	ofPoint v;
	ofPoint a;
	float velSpread;

	int size;

	int attractorNum;

	public:
		Particle();
		void update();
		void draw();
		int getAttractorNum();
		void attractTo(ofPoint attractPoint, int minDist, float velMult);
		ofPoint getPosition();

};

class ParticlesSystem {

	float minDist;
	float maxVel;
	float velMult;
	float rot;
	float forceMult;

	ofFloatColor color;

	Particle particles[NUM_PARTICLES];
	ofPoint attractors[3];

	ofVbo vboA;
	ofVbo vboB;

	ofMesh mesh;
	ofVbo vbo;

	ofTexture pTex;

	public:
		ParticlesSystem();
		void update();
		void draw();
		void drawAttractor(ofPoint p, int h);
		void moveAttractor(int x, int y);
		void setMinDist(int dist);
		void setVelMult(float m);
		void updateAttractorPosition(int i, ofPoint p);
		void setR(float r);
		void setG(float g);
		void setB(float b);
		void setA(float a);
};
