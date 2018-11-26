#include "ofApp.h"

const int kMouseSizeDivisor = 6;
const int kTileSizeDivisor = 6;

//--------------------------------------------------------------
void ofApp::setup() {
  window_height = ofGetWindowHeight();
  window_width = ofGetWindowWidth();
  board_width = window_width;
  ofHideCursor();
  hand_open.load("openhand.png");
  hand_closed.load("closedhand.png");
  cursor = hand_open;
  board_tile.load("brownsquare.jpg");
  ResizeCursor();
  ResizeTile();
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  DrawBoardTiles();
  DrawCursor();
}

void ofApp::DrawCursor() {
  cursor.draw(ofGetMouseX() - hand_closed.getWidth() / 2,
              ofGetMouseY() - hand_closed.getHeight() / 2);
}

void ofApp::DrawBoardTiles() {
  for (int vertical_pos = window_height - board_width;
       vertical_pos < window_height; vertical_pos += tile_width) {
    for (int horizontal_pos = 0; horizontal_pos < window_width;
         horizontal_pos += tile_width) {
      board_tile.draw(horizontal_pos, vertical_pos);
    }
  }
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
void ofApp::windowResized(int w, int h) {
  window_height = h;
  window_width = (window_height * 3) / 5;
  board_width = window_width;
  ofSetWindowShape(window_width, window_height);
  ResizeCursor();
  ResizeTile();
}

void ofApp::ResizeCursor() {
  hand_size = window_width / kMouseSizeDivisor;
  hand_open.resize(hand_size, hand_size);
  hand_closed.resize(hand_size, hand_size);
  cursor.resize(hand_size, hand_size);
}

void ofApp::ResizeTile() {
  tile_width = window_width / kTileSizeDivisor;
  board_tile.resize(tile_width, tile_width);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
