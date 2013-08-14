#include "testApp.h"
ofTrueTypeFont font;
//--------------------------------------------------------------
void testApp::setup() {
    
	monoLineTextInput.setup();
	monoLineTextInput.text = "hello world";
    monoLineTextInput.bounds.x = 100;
    monoLineTextInput.bounds.y = 100;
	monoLineTextInput.bounds.height = 40;
		monoLineTextInput.bounds.width = 188;
	multilineTextInput.setup();
	
	multilineTextInput.text = "0: #include \"testApp.h\"\n"
	"1: \n"
	"2: //--------------------------------------------------------------\n"
	"3: void testApp::setup() {\n"
	"4: \n"
	"5:     monoLineTextInput.setup();\n"
	"6:     monoLineTextInput.text = \"hello world\";\n"
	"7:     monoLineTextInput.bounds.x = 100;\n"
	"8:     monoLineTextInput.bounds.y = 100;\n"
	"9:\n"
	"10:    multilineTextInput.setup();\n"
	"11: \n"
	"12: 	monoLineTextInput.text = \"hello world\";\n"
	"13:	monoLineTextInput.bounds.x = 100;\n"
	"14:	monoLineTextInput.bounds.y = 100;\n"
	"15:\n"
	"16:\n"
	"17: }\n";
    multilineTextInput.bounds.x = 300;
    multilineTextInput.bounds.y = 100;
	multilineTextInput.bounds.width = 400;
	multilineTextInput.bounds.height = 500;
	multilineTextInput.multiline = true;
	font.loadFont(OF_TTF_SERIF, 18);
	monoLineTextInput.setFont(font);
	
	
}

//--------------------------------------------------------------
void testApp::update() {
	
}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(255*.15);
    
    ofSetColor(255);
    ofRect(monoLineTextInput.bounds);
	ofRect(multilineTextInput.bounds);
    ofNoFill();
	monoLineTextInput.draw();
	multilineTextInput.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) { 

}
