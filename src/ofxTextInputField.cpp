//
//  ofxTextInputField.cpp
//  ofxTextInputField
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 2/12/2011

//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//
//

#include "ofxTextInputField.h"


ofxTextInputField::ofxTextInputField() {
	text="";
	cursorPosition=0;
	cursorx=0;
	cursory=0;
    isEnabled = false;
    bounds = ofRectangle(0,0,100,18);
    drawCursor = false;
}

void ofxTextInputField::setup(){
    ofAddListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);    
}

void ofxTextInputField::enable() {
    if(!isEnabled){
        ofAddListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_ACTIVE);
        isEnabled = true;
        drawCursor = true;
    }
}

void ofxTextInputField::disable() {
    if(isEnabled){
        ofRemoveListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_INACTIVE);
        isEnabled = false;
        drawCursor = false;
    }
}

bool ofxTextInputField::getIsEnabled(){
    return isEnabled;
}

void ofxTextInputField::draw() {
    
	ofPushMatrix();
	ofTranslate(bounds.x, bounds.y);
	
	//draw text
	ofDrawBitmapString(text, 10,12);
	
	//draw cursor line
    if(drawCursor) {
        ofPushStyle();
        float timeFrac = 0.5 * sin(3.0f * ofGetElapsedTimef()) + 0.5;
        
        ofColor col = ofGetStyle().color;
        
        ofSetColor(col.r * timeFrac, col.g * timeFrac, col.b * timeFrac);
        ofSetLineWidth(3.0f);
        ofLine(cursorx*8 + 10, 13.7*cursory+2, cursorx*8 + 10, 13.7*cursory+12);
        ofPopStyle();
    }
	
	ofPopMatrix();
}

void ofxTextInputField::mouseReleased(ofMouseEventArgs& args){
    if (bounds.inside(args.x, args.y)) {
        enable();
        clear();
    }
}

void ofxTextInputField::keyPressed(ofKeyEventArgs& args) {	
	//add charachter (non unicode sorry!)

	int key = args.key;
	if (key == OF_KEY_RETURN) {
//		return;
		ofNotifyEvent(evtEnter, text, this);
        disable();
//		if (evtEnter.empty()) {
//			text.insert(text.begin()+cursorPosition, '\n');
//			cursorPosition++;
//		}
	}
	
	if (key >=32 && key <=126) {
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
	
	//for multiline:
	cursorx = cursory = 0;
	for (int i=0; i<cursorPosition; ++i) {
		if (*(text.begin()+i) == '\n') {
			++cursory;
			cursorx = 0;
		} else {
			cursorx++;
		}
	}
}

void ofxTextInputField::clear() {
	text.clear();
	cursorPosition=0;
}
