#include "ParticlesSystem.h"

Particle::Particle(){
	m = 1;
	//p = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	p.x = ofRandom(0, ofGetWidth());
	p.y = ofRandom(0, ofGetHeight());
	v = ofPoint(0);
	a = ofPoint(0);
	velSpread = ofRandom(1.0,3.0);
	attractorNum = (int) ofRandom(0,2.9);

}

void Particle::update(){

}

ofPoint Particle::getPosition(){
	return p;
}

int Particle::getAttractorNum(){
	return attractorNum;
}

void Particle::attractTo(ofPoint attractPoint, int minDist, float velMult){
	ofVec3f dist = attractPoint - p;
	float sqDist = attractPoint.squareDistance(p);
	if(sqDist < minDist){
		// Random attractor between the 3 attractors
		//attractorNum = (attractorNum + (int) ofRandom(1, 2.9)) % 3;
		if(attractorNum == 0){
			attractorNum = 1;
		}
		else if(attractorNum == 2){
			attractorNum = 1;
		}
		else{
			attractorNum += ofSign(ofRandom(-1, 1));
		}
		// a = ofPoint(0);
		// v = ofPoint(0);
		//p = ofPoint(ofGetWidth()/2,ofGetHeight()/2);
		//cout << attractorNum << endl; 
	}else{
		//cout << min(1000 * 5 / sqDist, (float) maxVel) << endl;
		// ofPoint F = dist * 1/sqDist * forceMult;
		// a = F / m;
		// v += a;
		// p += v;
		p += dist * 1/sqDist * velMult * velSpread;
		p.x += ofRandom(-1,1);
		p.y += ofRandom(-1,1);
	}
	
}

// void Particle::attractTo(ofPoint attractPoint, int minDist, int rotDist, float maxVel, float velMult, float rot){
// 	ofVec3f dist = attractPoint - p;
// 	float sqDist = attractPoint.squareDistance(p);
// 	if(sqDist < minDist){
// 		// Random attractor between the 3 attractors
// 		//attractorNum = (attractorNum + (int) ofRandom(1, 2.9)) % 3;
// 		if(attractorNum == 0){
// 			attractorNum = 1;
// 		}
// 		else if(attractorNum == 2){
// 			attractorNum = 1;
// 		}
// 		else{
// 			attractorNum += ofSign(ofRandom(-1, 1));
// 		}

// 		//cout << attractorNum << endl; 
// 	}else{
// 		//cout << min(1000 * 5 / sqDist, (float) maxVel) << endl;
// 		p += dist * min(velMult / sqDist, maxVel);
// 		p += ofPoint(-dist.y, dist.x) * min(rot / sqDist, 1000.0f);
// 		p.x += ofRandom(-1,1);
// 		p.y += ofRandom(-1,1);
// 	}
	
// }



ParticlesSystem::ParticlesSystem(){
	
	// minDist = 500;
	// maxVel = 1;
	// velMult = 1;
	// rot = 10;
	color = ofFloatColor(0.19, 0.19, 0.37, 0.10);

	vbo.enableVAOs();
	//ofFloatColor c[NUM_PARTICLES];
	mesh.enableColors();
	for(int i=0; i<NUM_PARTICLES; i++){
		particles[i] = Particle();
		mesh.addVertex(particles[i].getPosition());
		mesh.addColor(ofFloatColor(0.5,0.1,0.1,0.3));
		mesh.addIndex(i);
	}
	vbo.setMesh(mesh, GL_DYNAMIC_DRAW);
	//vboA.setVertexData( particles[0].getPosition(), NUM_PARTICLES, GL_DYNAMIC_DRAW );
    //vboA.setColorData( &c[0], NUM_PARTICLES, GL_DYNAMIC_DRAW );

    //glEnable(GL_DEPTH_TEST);

	attractors[0] = ofPoint(ofGetWidth() / 3, ofGetHeight() / 3);
	attractors[1] = ofPoint(ofGetWidth() / 2, 2 * ofGetHeight() / 3);
	attractors[2] = ofPoint(2 * ofGetWidth() / 3, ofGetHeight() / 3);
}

void ParticlesSystem::update(){
	for(int i=0; i<NUM_PARTICLES; i++){
		//particles[i].update();
		int attractorNum = particles[i].getAttractorNum();
		particles[i].attractTo(attractors[attractorNum], minDist, velMult);
		mesh.setVertex(i, particles[i].getPosition());
		mesh.setColor(i, color);
	}
	vbo.updateMesh(mesh);
}

void ParticlesSystem::draw(){
	for(int i=0; i<3; i++){
		if(i==1) drawAttractor(attractors[i], 255);
		else drawAttractor(attractors[i], 125);
	}
	ofEnableBlendMode(OF_BLENDMODE_ADD);
		vbo.draw(GL_POINTS, 0, NUM_PARTICLES);
	ofDisableBlendMode();
}

void ParticlesSystem::drawAttractor(ofPoint p, int h){

	int r = 20;
	ofColor c = ofColor::fromHsb(h,100,100);

	ofPushStyle();
		ofEnableAlphaBlending();
		ofFill();
		for(int i = 0; i<30; i++){
			c.setSaturation(255 * r / (i * i + 1));
			c.a = 255 * i*i / r + 20;
			ofSetColor(c);
			ofCircle(p, r / (i + 1));
		}
	ofPopStyle();
}

void ParticlesSystem::moveAttractor(int x, int y){
	attractors[1] = ofPoint(x, ofGetHeight()-y);
}

void ParticlesSystem::updateAttractorPosition(int i, ofPoint p){
	attractors[i] = p;
}

void ParticlesSystem::setMinDist(int dist){
	minDist = dist;
}

void ParticlesSystem::setVelMult(float m){
	velMult = m;
}

void ParticlesSystem::setR(float r){
	color.r = r;
}

void ParticlesSystem::setG(float g){
	color.g = g;
}

void ParticlesSystem::setB(float b){
	color.b = b;
}

void ParticlesSystem::setA(float a){
	color.a = a;
}

