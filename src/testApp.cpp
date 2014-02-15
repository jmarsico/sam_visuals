//toDo: 



#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	cam.initGrabber(640, 480);
	

    //bShowWire = false;
    
    gui.setup("gui");
    gui.add(distortionStrength.setup("distortion", 4.0, 1.0, 10.0));
    gui.add(bShowWire.setup("show Wires", false));
    gui.add(bShowCam.setup("show Camera", true));
    
    gui.setPosition(10,10);
    

    
    
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    stepSize = 8;
	ySteps = cam.getHeight() / stepSize;
	xSteps = cam.getWidth() / stepSize;
	for(int y = 0; y < ySteps; y++) {
		for(int x = 0; x < xSteps; x++) {
			mesh.addVertex(ofVec2f(x * stepSize, y * stepSize));
			mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
		}
	}
	for(int y = 0; y + 1 < ySteps; y++) {
		for(int x = 0; x + 1 < xSteps; x++) {
			int nw = y * xSteps + x;
			int ne = nw + 1;
			int sw = nw + xSteps;
			int se = sw + 1;
			mesh.addIndex(nw);
			mesh.addIndex(ne);
			mesh.addIndex(se);
			mesh.addIndex(nw);
			mesh.addIndex(se);
			mesh.addIndex(sw);
		}
	}
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		flow.setWindowSize(8);
		flow.calcOpticalFlow(cam);
		int i = 0;
        //distortionStrength = 4;
		for(int y = 1; y + 1 < ySteps; y++)
        {
			for(int x = 1; x + 1 < xSteps; x++)
            {
				int i = y * xSteps + x;
				ofVec2f position(x * stepSize, y * stepSize);
				ofRectangle area(position - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
				ofVec2f offset = flow.getAverageFlowInRegion(area);
				mesh.setVertex(i, position + distortionStrength * offset);
				i++;
			}
		}
	}
}

void testApp::draw() {
	ofBackground(0);
    
	ofScale(2, 2);
	cam.getTextureReference().bind();
	if(bShowCam){
        mesh.draw();
    }
	cam.getTextureReference().unbind();
	if(bShowWire) {
        ofSetColor(0,255,0);
		mesh.drawWireframe();
        ofSetColor(255,255,255);
	}
    ofScale(0.5, 0.5);
    gui.draw();
    
}


    //--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key == 'w' ){
        bShowWire = !bShowWire;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}