//
//  textInput.h
//  textInput
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 2/12/2011
//
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

#include "ofMain.h"
#include "ofEvents.h"

class ofxTextInputField {
  public:
	
	ofxTextInputField();
	
	void enable();
	void disable();
	
	void draw(int x, int y);
		
	void clear();
	
	string text;
	int cursorPosition;
	
	ofEvent<string> evtEnter;
	
protected:
	void	keyPressed(ofKeyEventArgs &a);
	int		cursorx, cursory;
};
