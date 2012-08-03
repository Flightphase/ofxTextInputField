//
//  textInput.h
//  textInput
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 2/12/2011
//  modified by Momo the Monster 7/10/2012
//
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//
#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#define TEXTFIELD_IS_ACTIVE "textfieldIsActive"
#define TEXTFIELD_IS_INACTIVE "textfieldIsInactive"

class ofxTextInputField {
  public:
	
	ofxTextInputField();
	
	void enable();
	void disable();
    bool isEnabled;
    
    ofRectangle bounds;
	
    void draw();
	void draw(int x, int y);
		
	void clear();
	
	string text;
	int cursorPosition;
	
	ofEvent<string> evtEnter;
	void	keyPressed(ofKeyEventArgs &a);
	
protected:
    void    mouseReleased(ofMouseEventArgs& args);
	int		cursorx, cursory;
};
