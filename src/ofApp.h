#pragma once

#include "board.h"
#include "ofMain.h"

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
  ofImage background;
  ofImage red_orb;
  ofImage blue_orb;
  ofImage green_orb;
  ofImage orange_orb;
  ofImage yellow_orb;
  ofImage purple_orb;

  Board game_board;

  int hand_size;
  int window_width;
  int window_height;
  int tile_width;
  int board_width;

  void DrawCursor();
  void DrawTiles();
  void DrawOrb(Orb orb);
  void DrawBoard();

  void ResizeTile();
  void ResizeCursor();
  void ResizeBackground();
};
