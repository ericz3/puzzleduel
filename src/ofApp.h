#pragma once

#include "board.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "player.h"

enum GameState {
  START,
  CREATE_GAME,
  JOIN_GAME,
  LOBBY,
  MENU,
  PLAYER_TURN,
  PLAYER_MOVE,
  PLAYER_COUNT_POINTS,
  PLAYER_ERASE_MATCHES,
  OPPONENT_TURN,
  OPPONENT_COUNT_POINTS,
  OPPONENT_ERASE_MATCHES,
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
  ofImage start_background;

  ofTrueTypeFont game_font;
  ofTrueTypeFont game_font_bold;
  ofTrueTypeFont title_font;
  ofTrueTypeFont button_font;
  float font_scale;

  GameState game_state;
  Board game_board;
  bool player_win;
  Orb cursor_orb;
  int num_rounds;
  std::string player_name;
   Player player;
   Player opponent;

  int cursor_width;
  int window_width;
  int window_height;
  int board_start_height;
  int board_width;
  int orb_diameter;
  int background_width;
  int orb_tile;
  int round;
  int button_width;
  int button_height;
  int name_box_width;
  int name_box_height;
  int mouse_clicked_x;  // used for button clicking
  int mouse_clicked_y;  // used for button clicking
  int slider_bar_length;
  int slider_bar_height;
  int slider_bar_x;
  int round_slider_bar_y;
  int mt_slider_bar_y;
  int round_slider_x;
  int mt_slider_x;
  int slider_radius;

  void DrawStart();
  void DrawStartButtons();
  void DrawStartTitle();
  void DrawStartButtonsText();

  void DrawCreateGame();
  void DrawSettingsSliders();
  void DrawSettingsSlidersText();
  void DrawCreateGameNameBox();
  void DrawCreateGameButtons();
  void DrawCreateGameButtonsText();
  bool name_box_selected;

  void DrawGameText();
  void DrawCursor();
  void DrawMoveTimeBar();
  void DrawCountPoints();
  void DrawBoard();

  void ResizeCursor();
  void ResizeBackground();
  void ResizeOrb();
  void ResizeUI();

  // checks if mouse is in specified area
  bool MouseInArea(int x_left, int x_right, int y_top, int y_bottom);
  bool dragging_round_slider;
  bool dragging_time_slider;

  float start_time;
  float end_time;

  // ofFbo count_points;

  // int last_count_ind;
  int erase_fade;
};
