#include "testApp.h"
#include "ofxCvHaarFinder.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    string host = Spacebrew::SPACEBREW_CLOUD; // "localhost";
    string name = "facetrigger";
    string description = "Super simple ofNoise sender";
    
    spacebrew.addPublish("noiseFast", "range");
    spacebrew.addPublish("noiseSlow", "range");
    spacebrew.connect( host, name, description );
    
    cam.initGrabber(640, 480);
	finder.setup("haarcascade_frontalface_default.xml");
	finder.findHaarObjects(img);
    
    sendnoise = false;

}

//--------------------------------------------------------------
void testApp::update(){
    cam.update();
    img.setFromPixels(cam.getPixels(), 640, 480, OF_IMAGE_COLOR);
    finder.findHaarObjects( img );
    if (( sendnoise = true)){
        float noiseFast = ofNoise(ofGetElapsedTimeMillis() * .1) * 1024.0f;
      //  float noiseSlow = ofNoise(ofGetElapsedTimef() * .1) * 1024.0f;
        spacebrew.sendRange("noiseFast", (noiseFast) );
        //spacebrew.sendRange("noiseSlow", (noiseSlow) );
    
        
    }

}
//--------------------------------------------------------------
void testApp::draw(){

	
    img.draw(0, 0);
    
    ofNoFill();
    
	for(unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
    }
}

//--------------------------------------------------------------
void testApp::faceTrigger(){
    if(finder.findHaarObjects(img)== true) {
        sendnoise = true;
    if(finder.findHaarObjects(img)==false) {
            sendnoise = false;
        }
    }
}