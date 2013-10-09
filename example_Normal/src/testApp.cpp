#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetWindowShape(1280, 720);
	ofSetVerticalSync(true);
	sampleImage.loadImage("sample.png");

	NicoFarre.setup(1280,720);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	NicoFarre.begin();
	/*-*-*-*-*-*-*-*-*-*- Draw something you want *-*-*-*-*-*-*-*-*/

	ofClear(0, 0, 0);
	ofSetColor(255, 255, 255);

	sampleImage.draw(0, 0);

	/*-*-*-*-*-*-*-*-*-*- Draw something you want *-*-*-*-*-*-*-*-*/
	NicoFarre.end();



	
	/*--- Send source buffer to 3D preview---*/
	NicoFarre.BufUpdate();

	/*--- Draw Nicofarre ---*/
	ofSetColor(255);
	NicoFarre.previewDraw(0, 0);

	/*--- Draw source buffer ---*/
	NicoFarre.getSourceBuf()->draw(0, 0, 320, 180);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
