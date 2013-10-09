//
//  ofxNicofarre.cpp
//  Exmr_MWAM
//
//  Created by maxilla on 2013/08/08.
//
//

#include "ofxNicofarre.h"

void ofxNicofarre::setup(int w,int h){
	camera.setDistance(1000.0);
	camera.setFarClip(10000.0);

	static GLfloat distance[] = { 0.0, 0.0, 1.0 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION,distance);

	sourceBuf.allocate (1920, 1080);
	previewBuf.allocate(w, h);
	source_sample.loadImage("images/source_demo.png");
	VBOSetup();

	useOpenedTexture = false;
}

void ofxNicofarre::setup(int w,int h, ofFbo* buffer){
	camera.setDistance(1000.0);
	camera.setFarClip(10000.0);

	sourceBuf.allocate (1920, 1080);
	previewBuf.allocate(w, h);
	source_sample.loadImage("images/source_demo.png");
	VBOSetup();

	static GLfloat distance[] = { 0.0, 0.0, 1.0 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION,distance);

	openedTexture.allocate(4938, 320, &sourceBuf,buffer);
	
	openedTexture.addRect(ofRectangle(20  ,  20,1520,320),
						  ofRectangle(2400,   0,1520,320),"A");//A
	openedTexture.addRect(ofRectangle(20  , 660, 880,320),
						  ofRectangle(1520,   0, 880,320),"B");//B
	openedTexture.addRect(ofRectangle(20  , 340,1520,320),
						  ofRectangle(0   ,   0,1520,320),"C");//C
	openedTexture.addRect(ofRectangle( 900, 660, 880,320),
						  ofRectangle(3920,   0, 880,320),"D");//D
	openedTexture.addRect(ofRectangle(1540,  20, 200,320),
						  ofRectangle(2467,   0, 200,320),"E");//E
	openedTexture.addRect(ofRectangle(1540, 340, 200,320),
						  ofRectangle(1250,   0, 200,320),"F");//F
	openedTexture.addRect(ofRectangle(1740,  20, 138,210),
						  ofRectangle(4800,   0, 138,210),"TOP");//TOP
	openedTexture.refleshVertexPointer();

	useOpenedTexture = true;
}


void ofxNicofarre::BufUpdate(){

	if (useOpenedTexture){
		
		openedTexture.rects[4].src.x = 2467 + 73;//ofGetMouseX();
		openedTexture.rects[5].src.x = 1250 - 67;// ofGetMouseY();
		openedTexture.refleshVertexPointer();

		sourceBuf.begin();
		ofSetColor(255);
		source_sample.draw(0,0, 1920, 1080);
		openedTexture.draw();
		sourceBuf.end();
		
	}

	previewBuf.begin();
	ofClear(0, 0, 0, 255);

	camera.begin();
	glEnable(GL_DEPTH_TEST);
	ofPushMatrix();
	glScalef(0.3, 0.3, 0.3);

	ofSetColor(255, 255, 255);
	sourceBuf.getTextureReference().bind();

	previewModel.drawElements(GL_TRIANGLES, PANEL_NUM*6);

	glPointSize(4.0);
	topPanelModel.draw(GL_POINTS, 0, 16660);
	glPointSize(1.0);

	sourceBuf.getTextureReference().unbind();

	/*===Stage===*/
	glPushMatrix();
	ofTranslate(0.0,-1975.0,-6495.0);
	glScalef(9450.0, 800.0, 3660.0);
	ofSetColor(128);
	ofDrawBox(0, 0, 0, 1.0);
	glPopMatrix();

	/*===Stage(optional)===*/
	glPushMatrix();
	ofTranslate(0.0,-1975.0,-3750.0);
	glScalef(9450.0, 800.0, 1830.0);
	ofSetColor(80);
	ofDrawBox(0, 0, 0, 1.0);
	glPopMatrix();

	/*===Floor===*/
	glBegin(GL_TRIANGLE_STRIP);
	ofSetColor(30, 30, 30);
	glVertex3f( 4725, -2375,  8325);
	glVertex3f(-4725, -2375,  8325);
	glVertex3f( 4725, -2375, -8325);
	glVertex3f(-4725, -2375, -8325);
	glEnd();

	/*===Wall under===*/
	ofSetColor(50, 50, 50);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-4725, -1575,-8325);
	glVertex3f(-4725, -2375,-8325);
	glVertex3f(-4725, -1575, 8325);
	glVertex3f(-4725, -2375, 8325);
	glVertex3f( 4725, -1575, 8325);
	glVertex3f( 4725, -2375, 8325);
	glVertex3f( 4725, -1575,-8325);
	glVertex3f( 4725, -2375,-8325);
	glEnd();

	/*=== back console ===*/
	ofPushMatrix();
	ofTranslate(-2700, -1525, 7200);
	glScalef(4050, 1700, 2249);
	ofSetColor(20, 20, 20);
	ofDrawBox(0, 0, 0, 1.0);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(3600, -1525, 7200);
	glScalef(2250, 1700, 2249);
	ofSetColor(20, 20, 20);
	ofDrawBox(0, 0, 0, 1.0);
	ofPopMatrix();


	/*部屋原点*/
	ofDrawAxis(400.0);

	/*ステージ原点*/
	ofPushMatrix();
	ofTranslate(0.0,-1575.0, -6495.0);
	ofRotateX(180);
	ofDrawAxis(1500.0);
	ofPopMatrix();
	
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
	camera.end();

	previewBuf.end();
}

void ofxNicofarre::VBOSetup(){

	/*===== B Panel =====*/
	vertex[0].set(-4725, 1575, -8325);
	vertex[1].set( 4725, 1575, -8325);
	vertex[2].set(-4725, -1575, -8325);
	vertex[3].set( 4725, -1575, -8325);
	texCoords[0].set(40		, 680);
	texCoords[1].set(880	, 680);
	texCoords[2].set(40		, 960);
	texCoords[3].set(880	, 960);

	/*===== A Panel =====*/
	vertex[4].set( 4725,  1575, -8325);
	vertex[5].set( 4725, -1575, -8325);
	vertex[6].set( 4725,  1575,  8325);
	vertex[7].set( 4725, -1575,  8325);
	texCoords[4].set(40		, 40);
	texCoords[5].set(40 	, 320);
	texCoords[6].set(1520	, 40);
	texCoords[7].set(1520	, 320);

	/*===== C Panel =====*/
	vertex[8 ].set(-4725,  1575, -8325);
	vertex[9 ].set(-4725, -1575, -8325);
	vertex[10].set(-4725,  1575,  8325);
	vertex[11].set(-4725, -1575,  8325);
	texCoords[8] .set(1520		, 360);
	texCoords[9] .set(1520		, 640);
	texCoords[10].set(40		, 360);
	texCoords[11].set(40		, 640);

	/*===== D Panel =====*/
	vertex[12].set(-4725,  1575,  8325);
	vertex[13].set( 4725,  1575,  8325);
	vertex[14].set(-4725, -1575,  8325);
	vertex[15].set( 4725, -1575,  8325);
	texCoords[12].set(1760		, 680);
	texCoords[13].set(920		, 680);
	texCoords[14].set(1760		, 960);
	texCoords[15].set(920		, 960);

	/*===== E Panel =====*/
	vertex[16].set( 2925, -1575,  -4965);
	vertex[17].set( 2925,  1575,  -4965);
	vertex[18].set( 4725, -1575,  -4965);
	vertex[19].set( 4725,  1575,  -4965);
	texCoords[16].set(1560		, 320);
	texCoords[17].set(1560		, 40);
	texCoords[18].set(1720		, 320);
	texCoords[19].set(1720		, 40);

	/*===== F Panel =====*/
	vertex[20].set(-2925, -1575,  -4965);
	vertex[21].set(-2925,  1575,  -4965);
	vertex[22].set(-4725, -1575,  -4965);
	vertex[23].set(-4725,  1575,  -4965);
	texCoords[20].set(1720		, 640);
	texCoords[21].set(1720		, 360);
	texCoords[22].set(1560		, 640);
	texCoords[23].set(1560		, 360);

	/*===== D Panel Console wall =====*/
	vertex[24].set(-4725,  -675, 6075);
	vertex[25].set(-4725, -1575, 6075);
	vertex[26].set(- 675,  -675, 6075);
	vertex[27].set(- 675, -1575, 6075);

	vertex[28].set( 2475, -675, 6075);
	vertex[29].set( 2475,-1575, 6075);
	vertex[30].set( 4725, -675, 6075);
	vertex[31].set( 4725,-1575, 6075);

	//920,880
	texCoords[24].set(1760		, 880);
	texCoords[25].set(1760		, 960);
	texCoords[26].set(1400		, 880);
	texCoords[27].set(1400		, 960);

	texCoords[28].set(1120		, 880);
	texCoords[29].set(1120		, 960);
	texCoords[30].set(920		, 880);
	texCoords[31].set(920		, 960);


	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 1;
	index[4] = 2;
	index[5] = 3;

	index[6 ] = 4;
	index[7 ] = 5;
	index[8 ] = 6;
	index[9 ] = 5;
	index[10] = 6;
	index[11] = 7;

	index[12] = 8;
	index[13] = 9;
	index[14] = 10;
	index[15] = 9;
	index[16] = 10;
	index[17] = 11;

	index[18] = 12;
	index[19] = 13;
	index[20] = 14;
	index[21] = 13;
	index[22] = 14;
	index[23] = 15;

	index[24] = 16;
	index[25] = 17;
	index[26] = 18;
	index[27] = 17;
	index[28] = 18;
	index[29] = 19;

	index[30] = 20;
	index[31] = 21;
	index[32] = 22;
	index[33] = 21;
	index[34] = 22;
	index[35] = 23;

	index[36] = 24;
	index[37] = 25;
	index[38] = 26;
	index[39] = 25;
	index[40] = 26;
	index[41] = 27;

	index[42] = 28;
	index[43] = 29;
	index[44] = 30;
	index[45] = 29;
	index[46] = 30;
	index[47] = 31;

	for (int i = 0;i < PANEL_NUM*4;i++){
		colors[i].set(1.0, 1.0, 1.0, 1.0);
	}
	previewModel.setColorData(colors, PANEL_NUM*4, GL_DYNAMIC_DRAW);
	previewModel.setVertexData(vertex, PANEL_NUM*4, GL_STATIC_DRAW);
	previewModel.setIndexData(index, PANEL_NUM*6, GL_STATIC_DRAW);
	previewModel.setTexCoordData(texCoords, PANEL_NUM*4, GL_STATIC_DRAW);

	for (int j = 1;j < 170;j++){
		for (int i = 1;i < 98;i++){
			topVertex[j*98+i].set((i-1)*98 - 4725, 1575,j*98 - 8325);
			topTexCoords[j*98+i].set(1760 + i,210 - j);
		}
	}

	topPanelModel.setVertexData(topVertex, 16660, GL_STATIC_DRAW);
	topPanelModel.setTexCoordData(topTexCoords, 16660, GL_STATIC_DRAW);
}

void ofxNicofarre::setBrightness(ofxNicofarrePanel panel, float brightness){
	if (!useOpenedTexture){
		ofLog(OF_LOG_WARNING, "You can use this method at only openTexture mode.");
		return;
	}
	ofFloatColor tar = ofFloatColor(brightness,brightness,brightness,1.0);
	switch (panel) {
		case FARRE_PANEL_A:
			openedTexture.setRectColor("A", tar);
			break;
		case FARRE_PANEL_B:
			openedTexture.setRectColor("B", tar);
			break;
		case FARRE_PANEL_C:
			openedTexture.setRectColor("C", tar);
			break;
		case FARRE_PANEL_D:
			openedTexture.setRectColor("D", tar);
			break;
		case FARRE_PANEL_E:
			openedTexture.setRectColor("E", tar);
			break;
		case FARRE_PANEL_F:
			openedTexture.setRectColor("F", tar);
			break;
		case FARRE_PANEL_TOP:
			openedTexture.setRectColor("TOP", tar);
			break;
		default:
			break;
	}
}