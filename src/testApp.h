#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

#import "ofxSpacebrew.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
  
    
    void faceTrigger();
    
    
    ofImage img;
    ofVideoGrabber cam;
    ofxCvHaarFinder finder;
    bool    sendnoise;
    
    // create your spacebrew object
    Spacebrew::Connection spacebrew;
};
