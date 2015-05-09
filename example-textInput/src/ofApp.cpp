#include "ofApp.h"
ofTrueTypeFont font;
//--------------------------------------------------------------
void ofApp::setup() {
    
	monoLineTextInput.setup();
	monoLineTextInput.text = "hello world";
    monoLineTextInput.bounds.x = 100;
    monoLineTextInput.bounds.y = 100;
	monoLineTextInput.bounds.height = 40;
		monoLineTextInput.bounds.width = 188;
	multilineTextInput.setup();
	
	multilineTextInput.text = "0: #include \"ofApp.h\"\n"
	"1: \n"
	"2: //--------------------------------------------------------------\n"
	"3: void ofApp::setup() {\n"
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
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255*.15);
    
    ofSetColor(255);
    ofRect(monoLineTextInput.bounds);
	ofRect(multilineTextInput.bounds);
    ofNoFill();
	monoLineTextInput.draw();
	multilineTextInput.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
