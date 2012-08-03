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

#define TEXTFIELD_IS_ACTIVE "textfieldIsActive"
#define TEXTFIELD_IS_INACTIVE "textfieldIsInactive"

class ofxTextInputField {
  public:
	ofxTextInputField();
	
    void setup();
    
	void enable();
	void disable();
    bool getIsEnabled();
    //can be set manually or otherwise is controlled by enable/disable
    bool drawCursor;
    
    ofRectangle bounds;
	
    void draw();
		
	void clear();
	
	string text;
	int cursorPosition;
	
	ofEvent<string> evtEnter;
	void	keyPressed(ofKeyEventArgs &a);

  protected:
    bool 	isEnabled;
    void    mouseReleased(ofMouseEventArgs& args);
	int		cursorx, cursory;
};
