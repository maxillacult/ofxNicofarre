//
//  texSelector.h
//  Exmr_MWAM
//
//  Created by Ovis aries on 2013/08/09.
//
//

#ifndef __Exmr_MWAM__texSelector__
#define __Exmr_MWAM__texSelector__

#include "ofMain.h"

class textureRect {
public:
	string rectName;
	ofRectangle src;
	ofRectangle dst;
	ofFloatColor col[4];
};

class texSelector{
public:
	void allocate(int w,int h,ofFbo* target,ofFbo *srcBuf);
	void addRect(ofRectangle target,ofRectangle source, string name);
	void refleshVertexPointer();

	void setRectColor(string name,float r,float g,float b,float a);
	void setRectColor(string name,ofFloatColor color);

	void begin(){buffer->begin();}
	void end(){buffer->end();}

	void draw();

//protected:
	textureRect* getRectangle(string name);

	vector<ofVec3f> vertices;
	vector<ofVec2f> texCoords;
	vector<ofFloatColor> colors;
	vector<textureRect> rects;

	ofRectangle interArea;
	ofFbo* targetBuffer;
	ofFbo* buffer;

	/*--- not implemented ---*/
	void setInteractArea(ofRectangle area);

	void mouseMoved(ofMouseEventArgs &arg);
	void mousePressed(ofMouseEventArgs &arg);
	void mouseDragged(ofMouseEventArgs &arg);
	void mouseReleased(ofMouseEventArgs &arg);
};

#endif /* defined(__Exmr_MWAM__texSelector__) */
