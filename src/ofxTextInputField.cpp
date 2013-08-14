//
//  textInput.cpp
//
//  Created by Elliot Woods on 09/12/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 12/2/2011
//  modified by Momo the Monster 7/10/2012
//  swappable fonts added by James George 9/11/2012
//
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

#include "ofxTextInputField.h"


ofxTextInputField::ofxTextInputField() {
	text = "";
	cursorPosition = 0;
	fontRef = NULL;
    isEnabled = false;
	isEditing = false;
    bounds = ofRectangle(0,0,100,22);
    drawCursor = false;
	autoClear = false;
	mouseDownInRect = false;
	OFX_TEXTFIELD_FONT_RENDERER *r = new OFX_TEXTFIELD_FONT_RENDERER();
	setFont(*r);
    //isSetup = false;
	
	VERTICAL_PADDING = 3;
	HORIZONTAL_PADDING = 3;
	lastTimeCursorMoved = ofGetElapsedTimef();
}

ofxTextInputField::~ofxTextInputField(){
	if(isEnabled){
        disable();
    }

}

void ofxTextInputField::setup(){
	enable();
}


void ofxTextInputField::enable(){
	if(!isEnabled){
		ofAddListener(ofEvents().mousePressed, this, &ofxTextInputField::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);
		isEnabled = true;
	}
}

void ofxTextInputField::disable(){
	if(isEditing){
		endEditing();
	}
	if(isEnabled){
        ofRemoveListener(ofEvents().mousePressed, this, &ofxTextInputField::mousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);
		isEnabled = false;
    }
	
}
void ofxTextInputField::beginEditing() {
    if(!isEditing){
        ofAddListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_ACTIVE);
        isEditing = true;
        drawCursor = true;
		if(autoClear){
			clear();
		}
		else{


		}
    }
}

void ofxTextInputField::endEditing() {
    if(isEditing){
        ofRemoveListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_INACTIVE);
        ofNotifyEvent(textChanged, text, this);
        isEditing = false;
        drawCursor = false;
    }
}

void ofxTextInputField::setFont(OFX_TEXTFIELD_FONT_RENDERER& font){
	fontRef = &font;
}

bool ofxTextInputField::getIsEditing(){
    return isEditing;
}

bool ofxTextInputField::getIsEnabled(){
	return isEnabled;
}

void ofxTextInputField::draw() {
    
	ofPushMatrix();
	ofTranslate(bounds.x, bounds.y);

	
	fontRef->drawString(text, HORIZONTAL_PADDING, fontRef->getLineHeight()+VERTICAL_PADDING);
	

	//draw cursor line
    if(drawCursor) {
        ofPushStyle();
		// cursor should only blink when its been idle, and animation
		// should be a clipped sine wave
        float timeFrac = 0.5 * ofClamp(cos(6.0f * (ofGetElapsedTimef()-lastTimeCursorMoved))*4, -1, 1) + 0.5;
        
        ofColor col = ofGetStyle().color;
		ofSetColor(col.r * timeFrac, col.g * timeFrac, col.b * timeFrac);
		
		
		// argh, splitting all the time.
		vector<string> lines = ofSplitString(text, "\n");
		
		
		// calculate this every loop.
		int cursorX, cursorY;
        getCursorCoords(cursorX, cursorY);
	//	printf("Pos: %d    X: %d   Y: %d\n", cursorPosition, cursorX, cursorY);
		int cursorPos = HORIZONTAL_PADDING + fontRef->stringWidth(lines[cursorY].substr(0,cursorX));
        
		
        
		int cursorTop = VERTICAL_PADDING + fontRef->getLineHeight()*cursorY;
		int cursorBottom = cursorTop + fontRef->getLineHeight();
		
		
		
		
		ofSetLineWidth(1.0f);
		//TODO: multiline with fontRef
        ofLine(cursorPos, cursorTop,
			   cursorPos, cursorBottom);
        ofPopStyle();
    }
	
	ofPopMatrix();
}

void ofxTextInputField::getCursorCoords(int &cursorX, int &cursorY) {
	vector<string> lines = ofSplitString(text, "\n");
	
	
	int c = 0;
	
	
	for(int i = 0; i < lines.size(); i++) {
		if(cursorPosition<=c+lines[i].size()) {
			cursorY = i;
			cursorX = cursorPosition - c;
			return;
		}
		c += lines[i].size() + 1;
	}

}

/*
void ofxTextInputField::setCursorPositionFromXY() {
	cursorPosition = cursorx;
	vector<string> parts = ofSplitString(text, "\n");
	for(int i = 0 ; i < cursory; i++) {
		cursorPosition += parts[i].size() + i; // for carriage returns
	}
}

*/
int ofxTextInputField::getCursorPositionFromMouse(int x, int y) {
	int cursorX = 0;
	int cursorY = 0;
	float pos = y - bounds.y - VERTICAL_PADDING;
	pos /= fontRef->getLineHeight();
	int line = pos;
	cursorY = line;
	
	vector<string> lines = ofSplitString(text, "\n");
	if(cursorY>=lines.size()-1) cursorY = lines.size()-1;
	if(lines.size()>0) {
		cursorX = fontRef->getPosition(lines[cursorY], x - HORIZONTAL_PADDING - bounds.x);
	}
	int c = 0;
	for(int i = 0; i < cursorY; i++) {
		c += lines[i].size() + 1;
	}
	c += cursorX;
	return c;
}


void ofxTextInputField::mousePressed(ofMouseEventArgs& args){
	mouseDownInRect = bounds.inside(args.x, args.y);
	if(mouseDownInRect) {
		cursorPosition = getCursorPositionFromMouse(args.x, args.y);
		lastTimeCursorMoved = ofGetElapsedTimef();
	}
}

void ofxTextInputField::mouseReleased(ofMouseEventArgs& args){

    if(bounds.inside(args.x, args.y)) {
        if(!isEditing && mouseDownInRect){
	        beginEditing();
        }
    }
    else if(isEditing){
		endEditing();
	}
}
/*
void ofxTextInputField::setCursorXYFromPosition() {
	vector<string> lines = ofSplitString(text, "\n");
	
	
	int c = 0;
	
	
	for(int i = 0; i < lines.size(); i++) {
		if(cursorPosition<=c+lines[i].size()) {
			cursory = i;
			cursorx = cursorPosition - c;
			break;
		}
		c += lines[i].size() + 1;
	}
}

int ofxTextInputField::getLineForPosition(int pos) {
	vector<string> lines = ofSplitString(text, "\n");
	int c = 0;
	for(int i = 0; i < lines.size(); i++) {
		if(pos<c+lines[i].size()+1) {
			return i;
		}
		c += lines[i].size() + 1;
	}
}
*/
void ofxTextInputField::keyPressed(ofKeyEventArgs& args) {
	//ew: add charachter (non unicode sorry!)
	//jg: made a step closer to this with swappable renderers and ofxFTGL -- but need unicode text input...
	lastTimeCursorMoved = ofGetElapsedTimef();
	int key = args.key;
	if (key == OF_KEY_RETURN) {
				text.insert(text.begin()+cursorPosition, '\n');
		cursorPosition++;
//        endEditing();
        return;
	}
	
	if ((key >=32 && key <=126) || key=='\t') {
		text.insert(text.begin()+cursorPosition, key);
		cursorPosition++;
	}
	
	
	if (key==OF_KEY_BACKSPACE) {
		if (cursorPosition>0) {
			text.erase(text.begin()+cursorPosition-1);
			--cursorPosition;
		}
	}
	
	if (key==OF_KEY_DEL) {
		if (text.size() > cursorPosition) {
			text.erase(text.begin()+cursorPosition);
		}
	}
	
	if (key==OF_KEY_LEFT){
		if (cursorPosition>0){
			--cursorPosition;
		}
	}
	
	if (key==OF_KEY_RIGHT){
		if (cursorPosition<text.size()){
			++cursorPosition;
		}
	}
	
	
}

void ofxTextInputField::clear() {
	text.clear();
	cursorPosition = 0;
}
