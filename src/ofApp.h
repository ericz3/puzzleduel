#pragma once

#include "board.h"
#include "gamemanager.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"
#include "player.h"

class PuzzleDuel : public ofBaseApp {
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
  ofTrueTypeFont add_points_font;
  ofTrueTypeFont player_name_font;
  ofTrueTypeFont player_points_font;
  float font_scale;

  GameManager game_manager;

  std::string player_name;

  int cursor_width;
  int window_width;
  int window_height;
  int board_start_height;
  int board_width;
  int orb_diameter;
  int background_width;
  int orb_tile;
  int button_width;
  int button_height;
  int box_width;
  int box_height;
  int mouse_clicked_x;
  int mouse_clicked_y;
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
  int lobby_p1_box_height;
  int lobby_p2_box_height;
  int player_box_width;
  int player_box_height;
  int player_box_y;

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

  void DrawLobby();
  void DrawLobbyPlayerBoxes();
  void DrawLobbyButtons();
  void DrawLobbySettings();
  void DrawLobbyPlayerNames();
  void DrawLobbyButtonText();

  void DrawGame();
  void DrawGameText();
  void DrawCursor();
  void DrawMoveTimeBar();
  void DrawAddPoints();
  void DrawBoard();

  void DrawGameOver();

  void ResizeCursor();
  void ResizeBackground();
  void ResizeOrb();
  void ResizeUI();

  std::string port_s;

  // checks if mouse is in specified area
  bool MouseInArea(int x_left, int x_right, int y_top, int y_bottom);
  bool dragging_round_slider;
  bool dragging_time_slider;

  bool name_box_selected;
  bool port_box_selected;

  float start_time;
  int erase_fade;
  int connection_start_time;
  int connect_time;

  int game_over_fade;

  // ofFbo count_points;

  // int last_count_ind;
};
