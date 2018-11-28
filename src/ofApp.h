#pragma once

#include "board.h"
#include "ofMain.h"

enum GameState {
  START,
  MENU,
  PLAYER_TURN,
  PLAYER_MOVE,
  OPPONENT_TURN,
  OPPONENT_MOVE,
  PLAYER_COUNT_POINTS, 
  PLAYER_ERASE_MATCHES,
  OPPONENT_COUNT_POINTS,
  OPPONENT_ERASE_MATCHES,
  SWITCH_PLAYER,
  GAME_OVER
};

class PuzzleBattle : public ofBaseApp {
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
  ofImage board_tiles;
  ofImage background;
  ofImage red_orb;
  ofImage blue_orb;
  ofImage green_orb;
  ofImage yellow_orb;
  ofImage white_orb;
  ofImage purple_orb;

  GameState game_state;
  Board game_board;
  bool player_win;
  Orb cursor_orb;

  int cursor_width;
  int window_width;
  int window_height;
  int board_start_height;
  int board_width;
  int orb_diameter;
  int background_width;
  int orb_tile;

  void DrawCursor();
  void DrawCalculatePoints();
  void DrawBoard();

  void ResizeCursor();
  void ResizeBackground();
  void ResizeOrb();

  int erase_fade;
};
