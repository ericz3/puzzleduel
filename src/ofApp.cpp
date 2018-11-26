#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofHideCursor();
  hand_open.loadImage("openhand.png");
  hand_closed.loadImage("closedhand.png");
  hand_open.resize(ofGetWindowWidth() / 7, ofGetWindowWidth() / 7);
  hand_closed.resize(ofGetWindowWidth() / 7, ofGetWindowWidth() / 7);
  cursor = hand_open;
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  cursor.draw(ofGetMouseX() - hand_closed.getWidth() / 2,
              ofGetMouseY() - hand_closed.getHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { cursor = hand_closed; }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) { cursor = hand_open; }

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
