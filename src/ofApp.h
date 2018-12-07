#pragma once

#include "board.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"
#include "player.h"

enum GameState {
  START,
  CREATE_GAME,
  JOIN_GAME,
  CONNECTING,
  CONNECTION_FAILED,
  LOBBY,
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
  ofImage menu_background;

  ofTrueTypeFont game_font;
  ofTrueTypeFont game_font_bold;
  ofTrueTypeFont title_font;
  ofTrueTypeFont button_font;
  ofTrueTypeFont label_font;
  ofTrueTypeFont message_font;
  float font_scale;

  GameState game_state;
  Board game_board;
  unsigned int num_rounds;
  bool player_win;
  Orb cursor_orb;

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
  int box_width;
  int box_height;
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
  int box_outline_thickness;
  int outline_box_height;
  int outline_box_width;

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

  void DrawJoinGame();
  void DrawJoinGameInputBoxes();
  void DrawJoinGameInputBoxText();
  void DrawJoinGameInputBoxLabels();
  void DrawJoinGameButtons();
  void DrawJoinGameButtonsText();

  void DrawConnecting();

  void DrawConnectionFailed();

  bool name_box_selected;
  bool port_box_selected;

  void DrawGameText();
  void DrawCursor();
  void DrawMoveTimeBar();
  void DrawCountPoints();
  void DrawBoard();

  void ResizeCursor();
  void ResizeBackground();
  void ResizeOrb();
  void ResizeUI();

  ofxTCPServer server;
  ofxTCPClient client;
  std::string port_s;
  int port;
  bool client_connected;

  void SetUpServer();
  void SetUpClient();

  // checks if mouse is in specified area
  bool MouseInArea(int x_left, int x_right, int y_top, int y_bottom);
  bool dragging_round_slider;
  bool dragging_time_slider;

  float start_time;
  float end_time;
  int erase_fade;
  int connection_start_time;
  int connect_time;

  // ofFbo count_points;

  // int last_count_ind;
};
