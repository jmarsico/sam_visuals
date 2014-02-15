#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    
    
	ofVideoGrabber cam;
	ofxCv::FlowFarneback flow;
	ofMesh mesh;
	int stepSize, xSteps, ySteps;
    
   
    //bool bShowWire;
    //float distortionStrength;
    
    ofxFloatSlider distortionStrength;
  
    ofxToggle bShowWire;
    ofxToggle bShowCam;
    ofxPanel gui;
    
    

    
};