#include "ofMain.h"
#include "OSCCommunication.h"

void OSCCommunication::setup(){
	//sender.setup("192.168.0.15", 12001);
	receiver.setup(12001);
}

bool OSCCommunication::nextMessage(ofxOscMessage* message){
	if(receiver.hasWaitingMessages()){
		receiver.getNextMessage(message);		
		return true;
	}
	return false;
}
