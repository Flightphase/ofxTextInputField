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
	text="";
	cursorPosition=0;
	cursorx=0;
	cursory=0;
	fontRef = NULL;
    isEnabled = false;
    bounds = ofRectangle(0,0,100,18);
    drawCursor = false;
    isSetup = false;
}

ofxTextInputField::~ofxTextInputField(){
    if(isEnabled){
        disable();
    }

	if(isSetup){
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);    
    }
}

void ofxTextInputField::setup(){
    if(!isSetup){
        isSetup = true;
	    ofAddListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);    
    }
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
        ofNotifyEvent(textChanged, text, this);
        isEnabled = false;
        drawCursor = false;
    }
}

void ofxTextInputField::setFont(OFX_TEXTFIELD_FONT_RENDERER& font){
	fontRef = &font;
}

bool ofxTextInputField::getIsEnabled(){
    return isEnabled;
}

void ofxTextInputField::draw() {
    
	ofPushMatrix();
	ofTranslate(bounds.x, bounds.y);
	
	//draw text
	if(fontRef == NULL){
		//boo don't use this
		ofDrawBitmapString(text, 10,12);
	}
	else{
		fontRef->drawString(text, 10, 12);
	}
	
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
        if(!isEnabled){
	        enable();
    	    clear();
        }
    }
    else{
        if(isEnabled){
	        disable();
        }
    }
}

void ofxTextInputField::keyPressed(ofKeyEventArgs& args) {	
	//ew: add charachter (non unicode sorry!)
	//jg: made a step closer to this with swappable renderers and ofxFTGL -- but need unicode text input...
	
	int key = args.key;
	if (key == OF_KEY_RETURN) {
        disable();
        return;
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
