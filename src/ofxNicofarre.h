//
//  ofxNicofarre.h
//  Exmr_MWAM
//
//  Created by maxilla on 2013/08/08.
//
//

#ifndef __Exmr_MWAM__ofxNicofarre__
#define __Exmr_MWAM__ofxNicofarre__

#include "ofMain.h"
#include "texSelector.h"

#define PANEL_NUM 8

enum ofxNicofarrePanel{
	FARRE_PANEL_A,
	FARRE_PANEL_B,
	FARRE_PANEL_C,
	FARRE_PANEL_D,
	FARRE_PANEL_E,
	FARRE_PANEL_F,
	FARRE_PANEL_TOP
};

class ofxNicofarre{
public:
	void setup(int w,int h);
	void setup(int w,int h, ofFbo* buffer);
	void BufUpdate();

	ofFbo* getPreviewBuf(){return &previewBuf;}
	ofFbo* getSourceBuf(){return &sourceBuf;}

	void setBrightness(ofxNicofarrePanel panel,float brightness);

	void begin(){
		sourceBuf.begin();
	}

	void end(){
		sourceBuf.end();
	}

	void previewDraw(int x,int y){
		previewDraw(x, y, previewBuf.getWidth(), previewBuf.getHeight());
	}

	void previewDraw(int x,int y,int w,int h){
		previewBuf.draw(x, y, w, h);
	}

protected:

	void VBOSetup();

	texSelector openedTexture;

	ofFbo		openedBuf;	/* opened buffer */
	ofFbo		sourceBuf;	/* Farre flendly buffer */
	ofFbo		previewBuf;	/* 3D Preview Buffer */

	ofEasyCam	camera;

	ofImage		source_sample;

	ofVbo		previewModel;
	ofVbo		topPanelModel;

	ofFloatColor	colors		[PANEL_NUM*4];
	ofVec3f			vertex		[PANEL_NUM*4];
	ofVec2f			texCoords	[PANEL_NUM*4];
	ofIndexType		index		[PANEL_NUM*6];

	ofVec3f		topVertex	[16660];
	ofVec2f		topTexCoords[16660];

	bool enableOptionalStage;
	bool useOpenedTexture;
};

#endif /* defined(__Exmr_MWAM__ofxNicofarre__) */
