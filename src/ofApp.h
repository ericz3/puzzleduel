#pragma once

#include "ofMain.h"
#include "board.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

 private:
  ofImage hand_open;
  ofImage hand_closed;
  ofImage cursor;
  ofImage board_tile;

  int hand_size;
  int window_width;
  int window_height;
  int tile_width;
  int board_width;

  void DrawCursor();
  void DrawBoardTiles();
  void ResizeTile();
  void ResizeCursor();
};
