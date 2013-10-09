//
//  texSelector.cpp
//  Exmr_MWAM
//
//  Created by Ovis aries on 2013/08/09.
//
//

#include "texSelector.h"

void texSelector::allocate(int w, int h, ofFbo *target,ofFbo *srcBuf){
	ofAddListener(ofEvents().mouseMoved, this, &texSelector::mouseMoved);
	ofAddListener(ofEvents().mousePressed, this, &texSelector::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &texSelector::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &texSelector::mouseReleased);

	buffer = srcBuf;
	buffer->allocate(w, h);
	targetBuffer = target;
}

void texSelector::addRect(ofRectangle target, ofRectangle source, string name){
	textureRect newRec;
	newRec.rectName = name;
	newRec.src = source;
	newRec.dst = target;
	newRec.col[0].set(1.0, 1.0, 1.0, 1.0);
	newRec.col[1].set(1.0, 1.0, 1.0, 1.0);
	newRec.col[2].set(1.0, 1.0, 1.0, 1.0);
	newRec.col[3].set(1.0, 1.0, 1.0, 1.0);
	rects.push_back(newRec);
}

void texSelector::draw(){
	ofSetColor(255);
	buffer->getTextureReference().bind();
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, &colors[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	buffer->getTextureReference().unbind();
}

void texSelector::refleshVertexPointer(){
	vertices.clear();
	texCoords.clear();
	colors.clear();

	for (int i = 0;i < rects.size();i++){
		vertices.push_back(ofPoint(rects[i].dst.position));

		vertices.push_back(ofPoint(rects[i].dst.position) +
						   ofPoint(rects[i].dst.width,0.0));

		vertices.push_back(ofPoint(rects[i].dst.position) +
						   ofPoint(0.0,rects[i].dst.height));

		vertices.push_back(ofPoint(rects[i].dst.position) +
						   ofPoint(rects[i].dst.width,0.0));

		vertices.push_back(ofPoint(rects[i].dst.position) +
						   ofPoint(0.0,rects[i].dst.height));

		vertices.push_back(ofPoint(rects[i].dst.position) +
						   ofPoint(rects[i].dst.width,rects[i].dst.height));

		texCoords.push_back(ofPoint(rects[i].src.position));

		texCoords.push_back(ofPoint(rects[i].src.position) +
							ofPoint(rects[i].src.width,0.0));

		texCoords.push_back(ofPoint(rects[i].src.position) +
							ofPoint(0.0,rects[i].src.height));

		texCoords.push_back(ofPoint(rects[i].src.position) +
							ofPoint(rects[i].src.width,0.0));

		texCoords.push_back(ofPoint(rects[i].src.position) +
							ofPoint(0.0,rects[i].src.height));

		texCoords.push_back(ofPoint(rects[i].src.position) +
							ofPoint(rects[i].src.width,rects[i].src.height));

		colors.push_back(ofFloatColor(rects[i].col[0]));
		colors.push_back(ofFloatColor(rects[i].col[1]));
		colors.push_back(ofFloatColor(rects[i].col[2]));
		colors.push_back(ofFloatColor(rects[i].col[1]));
		colors.push_back(ofFloatColor(rects[i].col[2]));
		colors.push_back(ofFloatColor(rects[i].col[3]));
	}
}

void texSelector::setRectColor(string name, float r, float g, float b,float a){
	setRectColor(name, ofFloatColor(r,g,b,a));
}

void texSelector::setRectColor(string name, ofFloatColor color){
	textureRect* target = getRectangle(name);
	target->col[0].set(color);
	target->col[1].set(color);
	target->col[2].set(color);
	target->col[3].set(color);
	refleshVertexPointer();
}

textureRect* texSelector::getRectangle(string name){
	for (int i = 0;i < rects.size();i++){
		if (rects[i].rectName == name){
			return &rects[i];
		}
	}

	return NULL;
}

void texSelector::setInteractArea(ofRectangle area){
	interArea = area;
}

void texSelector::mouseMoved(ofMouseEventArgs &arg){
	arg.x -= interArea.x;
	arg.y -= interArea.y;
	
}

void texSelector::mousePressed(ofMouseEventArgs &arg){
	arg.x -= interArea.x;
	arg.y -= interArea.y;

}

void texSelector::mouseDragged(ofMouseEventArgs &arg){
	arg.x -= interArea.x;
	arg.y -= interArea.y;

}

void texSelector::mouseReleased(ofMouseEventArgs &arg){
	arg.x -= interArea.x;
	arg.y -= interArea.y;

}
