#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetWindowShape(1280, 720);
	ofSetVerticalSync(true);
	sampleImage.loadImage("sample.png");

	buffer.allocate(4938, 320);

	NicoFarre.setup(1280,720,&buffer);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	buffer.begin();
	/*-*-*-*-*-*-*-*-*-*- Draw something you want *-*-*-*-*-*-*-*-*/

	ofClear(0, 0, 0);
	ofSetColor(255, 255, 255);

	sampleImage.draw(0, 0);

	/*-*-*-*-*-*-*-*-*-*- Draw something you want *-*-*-*-*-*-*-*-*/
	buffer.end();


	/*--- Send source buffer to 3D preview---*/
	NicoFarre.BufUpdate();

	/*--- Draw Nicofarre ---*/
	ofSetColor(255);
	NicoFarre.previewDraw(0, 0);

	/*--- Draw opened buffer ---*/
	buffer.draw(0, 20, 1234.5, 80);
	ofDrawBitmapString("Opened buffer (you should draw on it.)", 0,18);

	/*--- Draw source buffer ---*/
	NicoFarre.getSourceBuf()->draw(0, 120, 320, 180);
	ofDrawBitmapString("Source buffer (Nicofarre original format)", 0,118);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key == '1') NicoFarre.setBrightness(FARRE_PANEL_A, 0.0);
	if (key == '2') NicoFarre.setBrightness(FARRE_PANEL_B, 0.0);
	if (key == '3') NicoFarre.setBrightness(FARRE_PANEL_C, 0.0);
	if (key == '4') NicoFarre.setBrightness(FARRE_PANEL_D, 0.0);
	if (key == '5') NicoFarre.setBrightness(FARRE_PANEL_E, 0.0);
	if (key == '6') NicoFarre.setBrightness(FARRE_PANEL_F, 0.0);
	if (key == '7') NicoFarre.setBrightness(FARRE_PANEL_TOP, 0.0);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if (key == '1') NicoFarre.setBrightness(FARRE_PANEL_A, 1.0);
	if (key == '2') NicoFarre.setBrightness(FARRE_PANEL_B, 1.0);
	if (key == '3') NicoFarre.setBrightness(FARRE_PANEL_C, 1.0);
	if (key == '4') NicoFarre.setBrightness(FARRE_PANEL_D, 1.0);
	if (key == '5') NicoFarre.setBrightness(FARRE_PANEL_E, 1.0);
	if (key == '6') NicoFarre.setBrightness(FARRE_PANEL_F, 1.0);
	if (key == '7') NicoFarre.setBrightness(FARRE_PANEL_TOP, 1.0);

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
