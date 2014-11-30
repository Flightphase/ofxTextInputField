//
//  textInput.h
//  textInput
//
//  Created by Elliot Woods on 09/12/2011.
//  modified by James George 12/2/2011
//  modified by Momo the Monster 7/10/2012
//  swappable fonts added by James George 9/11/2012
//	refactoring and modifications by Elliot Woods on 30/11/2014
//
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

// jg : TODO: text wrapping

#pragma once

#include "ofMain.h"

//For lack of a type abstraction, this lets you #define a font renderer so
//(like ofxFTGL or ofxFont)
//to use ofxFTGL use somethinglike this:
//#define OFX_TEXTFIELD_FONT_RENDERER ofxFTGLFont
//#define OFX_TEXTFIELD_FONT_INCLUDE "ofxFTGLFont.h"

#ifndef OFX_TEXTFIELD_FONT_RENDERER
#define OFX_TEXTFIELD_FONT_RENDERER ofTrueTypeFont
#endif 

#ifdef OFX_TEXTFIELD_FONT_INCLUDE
#include OFX_TEXTFIELD_FONT_INCLUDE
#endif

#define TEXTFIELD_IS_ACTIVE "textfieldIsActive"
#define TEXTFIELD_IS_INACTIVE "textfieldIsInactive"

#include "ofxTextInputFieldFontRenderer.h"

class ofxTextInputField {
  public:
	ofxTextInputField();
	virtual ~ofxTextInputField();

	/// Always call this first
    void setup();

	/// Change the font used to draw the text
	void setFont(OFX_TEXTFIELD_FONT_RENDERER& font);

	void enable();
	void disable();
    bool isEnabled() const;
	
	void beginEditing();
	void endEditing();
	bool isEditing() const;

    //can be set manually or otherwise is controlled by enable/disable
    bool drawCursor;
    
    ofRectangle bounds;
	
    void draw();
	void clear();
	
	string text;
	int cursorPosition;
	
	int selectionBegin;
	int selectionEnd;
	bool selecting;
	
	ofEvent<string> textChanged;
	void keyPressed(ofKeyEventArgs &a);
    void keyReleased(ofKeyEventArgs &a);
	void mousePressed(ofMouseEventArgs& args);
	void mouseDragged(ofMouseEventArgs& args);
	void mouseReleased(ofMouseEventArgs& args);

	bool autoClear;
	bool autoTab;
	
	bool multiline;
    
	#ifdef USE_GLFW_CLIPBOARD
    void setClipboard(string clippy);
    string getClipboard();
	#endif
	
  protected:
	float lastTimeCursorMoved;
	
	float verticalPadding;
	float horizontalPadding;

	ofxTextInput::FontRenderer* fontRef;
	
    bool enabled;
	bool editing;
	bool mouseDownInRect;
	
	void getCursorCoords(int pos, int &cursorX, int &cursorY);
	int getCursorPositionFromMouse(int x, int y);
    
    bool shiftHeld, commandHeld;
    map<int, char> shiftMap;
};
