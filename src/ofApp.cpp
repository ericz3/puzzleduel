#include "ofApp.h"
#include <math.h>
#include <cmath>
#include <string>
#include <thread>

using std::string;
using std::vector;

const string kTitle1 = "PUZZLE";
const string kTitle2 = "DUEL";
const string kCreateLobbyButtonText = "Create Lobby";
const string kConfirmButtonText = "Confirm";
const string kBackButtonText = "Back";
const string kConnectButtonText = "Connect";
const string kJoinGameButtonText = "Join Lobby";
const string kNameBoxLabel = "Name (10 chars max)";
const string kPortBoxLabel = "Lobby ID (5 digits)";
const string kConnectingText = "Connecting ...";
const string kQuitButtonText = "Quit";
const string kConnectionErrorMessage1 = "CONNECTION FAILED";
const string kConnectionErrorMessage2 = "Press any key";
const string kLobbyP1Label = " Player 1: ";
const string kLobbyP2Label = " Player 2: ";

unsigned const int kMouseSizeDivisor = 7;
unsigned const int kTileSizeDivisor = 6;
unsigned const int kOrbDiameterDivisor = 6;
unsigned const int kRoundFontSizeDivisor = 10;
unsigned const int kStartFontSizeDivisor = 8;
unsigned const int kButtonFontSizeDivisor = 18;
unsigned const int kLabelFontSizeDivisor = 22;
unsigned const int kMessageFontSizedivisor = 28;
unsigned const int kButtonHeightDivisor = 10;
const float kButtonWidthDivisor = 1.5;
unsigned const int kBoxOutlineThicknessDivisor = 100;
unsigned const int kJoinGameBoxYPosDivisor = 6;

const float kAspectRatioMultiplier = 0.6;
const float kDefaultWindowWidth = 1024.0;
const float kDefaultWindowHeight = 1707.0;
const float kSliderLengthMultiplier = 0.7;
const float kRoundSelectorYPosMultiplier = 0.1;
const float kMoveTimeSelectorYPosMultiplier = 0.25;
const float kSliderHeightMultiplier = 0.008;
const float kSecondsPerMillisecond = 0.001;
const float kConfirmButtonYPosMultiplier = 0.6;
const float kBackButtonYPosMultiplier = 0.75;
const float kErrorBoxWidthMultiplier = 0.70;
const float kLobbyPlayerBoxWidthMultiplier = 0.90;
const float kLobbyPlayerBoxHeightMultiplier = 0.1;
const float kLobbyPlayerBoxYPosMultiplier = 0.15;
const float kLobbyIdYPosMultiplier = 0.1;
const float kLobbyQuitButtonYPosMultiplier = 0.85;
const float kLobbyStartButtonYPosMultiplier = 0.7;
const float kLobbySettingsYPosMultiplier = 0.5;

// unsigned const int kDrawCountPointsTimeInterval = 400;
const float kDefaultMoveTime = 15000;
unsigned const int kDefaultNumRounds = 5;
unsigned const int kMinRounds = 3;
unsigned const int kMaxRounds = 20;
const float kMaxMoveTime = 20000;
const float kMinMoveTime = 5000;

unsigned const int kMaxNameLength = 10;
unsigned const int kPortStrLength = 5;

unsigned const int kEraseFadeIncrement = 3;
unsigned const int kMaxAlpha = 255;
unsigned const int kDefaultRGB = 255;

//--------------------------------------------------------------
void PuzzleDuel::setup() {
  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofEnableAntiAliasing();

  window_height = ofGetWindowHeight();
  window_width = ofGetWindowWidth();
  board_width = window_width;
  board_start_height = window_height - window_width;

  ofHideCursor();
  hand_open.load("openhand.png");
  hand_closed.load("closedhand.png");
  cursor = hand_open;

  background.load("background.png");

  board_tiles.load("boardtiles.jpg");
  red_orb.load("redorb.png");
  blue_orb.load("blueorb.png");
  green_orb.load("greenorb.png");
  yellow_orb.load("yelloworb.png");
  white_orb.load("whiteorb.png");
  purple_orb.load("purpleorb.png");
  menu_background.load("startbackground.jpg");

  game_font.load("Xolonium-Regular.ttf", window_width / kRoundFontSizeDivisor);
  game_font_bold.load("Xolonium-Bold.ttf",
                      window_width / kRoundFontSizeDivisor);
  title_font.load("Xolonium-Bold.ttf", window_width / kStartFontSizeDivisor);
  button_font.load("Xolonium-Regular.ttf",
                   window_width / kButtonFontSizeDivisor);
  label_font.load("Xolonium-Regular.ttf", window_width / kLabelFontSizeDivisor);
  message_font.load("Xolonium-Regular.ttf",
                    window_width / kMessageFontSizedivisor);

  ResizeCursor();
  ResizeOrb();
  ResizeBackground();
  ResizeUI();

  ofSetEscapeQuitsApp(false);
  game_board.GenerateBoard();
  round = 1;
  name_box_selected = false;
  dragging_round_slider = false;
  dragging_time_slider = false;
  player_name = "";
  port_s = "";

  end_time = kDefaultMoveTime;
  num_rounds = kDefaultNumRounds;
  erase_fade = kMaxAlpha;

  /*
  count_points.allocate(ofGetWindowWidth(), ofGetWindowHeight());
  count_points.begin();
  ofClear(255, 255, 255);
  count_points.end();*/
}

//--------------------------------------------------------------
void PuzzleDuel::update() {
  if (game_manager.game_state == PLAYER_MOVE) {
    if (ofGetElapsedTimeMillis() - start_time > end_time) {
      mouseReleased(ofGetMouseX(), ofGetMouseY(), 0);
    }

  } else if (game_manager.game_state == PLAYER_ERASE_MATCHES) {
    if (erase_fade == 0) {
      erase_fade = kMaxAlpha;
      game_manager.game_state = PLAYER_COUNT_POINTS;
      /*last_count_ind = 0;
      count_points.begin();
      ofClear(255, 255, 255);
      count_points.end();*/

      std::vector<int> &board_points = game_board.GetPointsGrid();
      for (int i = 0; i < kBoardSize; i++) {
        if (board_points.at(i) == kOrbPointValue) {
          game_board.SetOrb(i, Orb::EMPTY);
        }
      }

    } else {
      erase_fade -= kEraseFadeIncrement;
    }

  } else if (game_manager.game_state == LOBBY) {
  }
}

//--------------------------------------------------------------
void PuzzleDuel::draw() {
  if (game_manager.game_state == START) {
    DrawStart();
  } else if (game_manager.game_state == CREATE_GAME) {
    DrawCreateGame();
  } else if (game_manager.game_state == JOIN_GAME) {
    DrawJoinGame();
  } else if (game_manager.game_state == CONNECTING) {
    DrawConnecting();
  } else if (game_manager.game_state == CONNECTION_FAILED) {
    DrawConnectionFailed();
  } else if (game_manager.game_state == LOBBY) {
    DrawLobby();
  } else {
    background.draw(0, 0, background_width, background_width);
    DrawGameText();
    DrawBoard();
    if (game_manager.game_state == PLAYER_COUNT_POINTS) {
      DrawCountPoints();
    }
    if (game_manager.game_state == PLAYER_MOVE) {
      DrawMoveTimeBar();
    }
  }

  DrawCursor();
}

void PuzzleDuel::DrawStart() {
  menu_background.draw(0, 0, background_width,
                       background_width / kAspectRatioMultiplier);
  DrawStartButtons();
  DrawStartTitle();
  DrawStartButtonsText();
}

void PuzzleDuel::DrawStartButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2, window_height / 2,
                    button_width, button_height, button_height / 4);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height / 2 + button_height * 1.5, button_width,
                    button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawStartTitle() {
  ofPushMatrix();
  ofSetColor(250, 200, 10);
  ofTranslate(window_width / 2, window_height / 3);
  ofScale(font_scale, font_scale, 1.0);
  int font_width1 = title_font.stringWidth(kTitle1);
  int font_height1 = title_font.stringHeight(kTitle1);
  title_font.drawString(kTitle1, -font_width1 / 2, 0);
  int font_width2 = title_font.stringWidth(kTitle2);
  title_font.drawString(kTitle2, -font_width2 / 2, font_height1 * 1.25);
  ofPopMatrix();
}

void PuzzleDuel::DrawStartButtonsText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / 2);
  ofScale(font_scale, font_scale, 1.0);
  int font_width_button1 = button_font.stringWidth(kCreateLobbyButtonText);
  int font_height_button1 = button_font.stringHeight(kCreateLobbyButtonText);
  button_font.drawString(kCreateLobbyButtonText, -font_width_button1 / 2,
                         font_height_button1 * 1.5);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / 2 + button_height * 1.5);
  ofScale(font_scale, font_scale, 1.0);
  int font_width_button2 = button_font.stringWidth(kJoinGameButtonText);
  int font_height_button2 = button_font.stringHeight(kJoinGameButtonText);
  button_font.drawString(kJoinGameButtonText, -font_width_button2 / 2,
                         font_height_button2 * 1.5);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawCreateGame() {
  menu_background.draw(0, 0, window_width,
                       window_width / kAspectRatioMultiplier);
  DrawSettingsSliders();
  DrawSettingsSlidersText();
  DrawCreateGameNameBox();
  DrawCreateGameButtons();
  DrawCreateGameButtonsText();
}

void PuzzleDuel::DrawSettingsSliders() {
  ofSetColor(200, 250, 255);
  ofDrawRectangle(slider_bar_x, round_slider_bar_y, slider_bar_length,
                  slider_bar_height);
  ofDrawRectangle(slider_bar_x, mt_slider_bar_y, slider_bar_length,
                  slider_bar_height);

  ofSetColor(250, 230, 40);
  float round_slide_proportion =
      (float)(num_rounds - kMinRounds) / (float)(kMaxRounds - kMinRounds);
  round_slider_x = round_slide_proportion * slider_bar_length + slider_bar_x;
  ofDrawCircle(round_slider_x, round_slider_bar_y + slider_bar_height / 2,
               slider_radius);
  float mt_slide_porportion =
      ((float)(end_time - kMinMoveTime) / (float)(kMaxMoveTime - kMinMoveTime));
  mt_slider_x = mt_slide_porportion * slider_bar_length + slider_bar_x;
  ofDrawCircle(mt_slider_x, mt_slider_bar_y + slider_bar_height / 2,
               slider_radius);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawSettingsSlidersText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kRoundSelectorYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  string rounds_string = "Rounds: " + std::to_string(num_rounds);
  int font_width_rounds = label_font.stringWidth(rounds_string);
  int font_height_rounds = label_font.stringHeight(rounds_string);
  label_font.drawString(rounds_string, -font_width_rounds / 2,
                        font_height_rounds * 3);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2,
              window_height * kMoveTimeSelectorYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  string move_time_string =
      "Move Time: " +
      std::to_string((int)std::round(end_time * kSecondsPerMillisecond)) +
      " Seconds";
  int font_width_mt = label_font.stringWidth(move_time_string);
  int font_height_mt = label_font.stringHeight(move_time_string);
  label_font.drawString(move_time_string, -font_width_mt / 2,
                        font_height_mt * 3);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawCreateGameNameBox() {
  if (name_box_selected) {
    ofSetColor(30, 160, 255);
    ofDrawRectangle(window_width / 2 - outline_box_width / 2,
                    window_height * 0.4 - box_outline_thickness,
                    outline_box_width, outline_box_height);
  }

  ofSetColor(235, 255, 255);
  ofDrawRectangle(window_width / 2 - box_width / 2, window_height * 0.4,
                  box_width, box_height);

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * 0.4);
  ofScale(font_scale, font_scale, 1.0);
  ofSetColor(25, 200, 50);
  int font_height = label_font.getLineHeight();
  int player_name_width = label_font.stringWidth(player_name);
  label_font.drawString(player_name, -player_name_width / 2, font_height);
  ofSetColor(250, 220, 65);
  string name_box_label = kNameBoxLabel;
  int name_box_label_width = label_font.stringWidth(name_box_label);
  label_font.drawString(name_box_label, -name_box_label_width / 2,
                        font_height * 2.75);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawCreateGameButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kBackButtonYPosMultiplier, button_width,
                    button_height, button_height / 4);

  if (player_name.length() <= 0) {
    ofSetColor(180, 205, 215);
  }

  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kConfirmButtonYPosMultiplier, button_width,
                    button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawCreateGameButtonsText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kBackButtonYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  string back_s = kBackButtonText;
  int back_s_width = button_font.stringWidth(back_s);
  int back_s_height = button_font.stringHeight(back_s);
  button_font.drawString(back_s, -back_s_width / 2, back_s_height * 2);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kConfirmButtonYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  if (player_name.length() <= 0) {
    ofSetColor(240, 220, 140);
  }

  string confirm_s = kConfirmButtonText;
  int confirm_s_width = button_font.stringWidth(confirm_s);
  int confirm_s_height = button_font.stringHeight(confirm_s);
  button_font.drawString(confirm_s, -confirm_s_width / 2, confirm_s_height * 2);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawJoinGame() {
  menu_background.draw(0, 0, window_width,
                       window_width / kAspectRatioMultiplier);
  DrawJoinGameInputBoxes();
  DrawJoinGameInputBoxText();
  DrawJoinGameInputBoxLabels();
  DrawJoinGameButtons();
  DrawJoinGameButtonsText();
}

void PuzzleDuel::DrawJoinGameInputBoxes() {
  if (name_box_selected) {
    ofSetColor(30, 160, 255);
    ofDrawRectangle(
        window_width / 2 - outline_box_width / 2,
        window_height / kJoinGameBoxYPosDivisor - box_outline_thickness,
        outline_box_width, outline_box_height);
  }

  ofSetColor(235, 255, 255);
  ofDrawRectangle(window_width / 2 - box_width / 2,
                  window_height / kJoinGameBoxYPosDivisor, box_width,
                  box_height);

  if (port_box_selected) {
    ofSetColor(30, 160, 255);
    ofDrawRectangle(
        window_width / 2 - outline_box_width / 2,
        window_height / kJoinGameBoxYPosDivisor * 2 - box_outline_thickness,
        outline_box_width, outline_box_height);
  }

  ofSetColor(235, 255, 255);
  ofDrawRectangle(window_width / 2 - box_width / 2,
                  window_height / kJoinGameBoxYPosDivisor * 2, box_width,
                  box_height);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawJoinGameInputBoxText() {
  ofSetColor(25, 200, 50);
  int font_height = label_font.getLineHeight();
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / kJoinGameBoxYPosDivisor);
  ofScale(font_scale, font_scale, 1.0);
  int player_name_width = label_font.stringWidth(player_name);
  label_font.drawString(player_name, -player_name_width / 2, font_height);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / kJoinGameBoxYPosDivisor * 2);
  ofScale(font_scale, font_scale, 1.0);
  int port_s_width = label_font.stringWidth(port_s);
  label_font.drawString(port_s, -port_s_width / 2, font_height);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawJoinGameInputBoxLabels() {
  int font_height = label_font.getLineHeight();

  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / kJoinGameBoxYPosDivisor);
  ofScale(font_scale, font_scale, 1.0);
  int name_box_label_width = label_font.stringWidth(kNameBoxLabel);
  label_font.drawString(kNameBoxLabel, -name_box_label_width / 2,
                        font_height * 2.75);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / kJoinGameBoxYPosDivisor * 2);
  ofScale(font_scale, font_scale, 1.0);
  int port_box_label_width = label_font.stringWidth(kPortBoxLabel);
  label_font.drawString(kPortBoxLabel, -port_box_label_width / 2,
                        font_height * 2.75);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawJoinGameButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kBackButtonYPosMultiplier, button_width,
                    button_height, button_height / 4);

  if (player_name.length() <= 0 || port_s.length() != kPortStrLength) {
    ofSetColor(180, 205, 215);
  }

  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kConfirmButtonYPosMultiplier, button_width,
                    button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawJoinGameButtonsText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kBackButtonYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  int back_s_width = button_font.stringWidth(kBackButtonText);
  int back_s_height = button_font.stringHeight(kBackButtonText);
  button_font.drawString(kBackButtonText, -back_s_width / 2, back_s_height * 2);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kConfirmButtonYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  if (player_name.length() <= 0 || port_s.length() != kPortStrLength) {
    ofSetColor(240, 220, 140);
  }

  string connect_s = kConnectButtonText;
  int connect_s_width = button_font.stringWidth(connect_s);
  int connect_s_height = button_font.stringHeight(connect_s);
  button_font.drawString(connect_s, -connect_s_width / 2, connect_s_height * 2);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawConnecting() {
  ofSetColor(250, 210, 170);
  menu_background.draw(0, 0, window_width,
                       window_width / kAspectRatioMultiplier);

  ofSetColor(185, 200, 255);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kBackButtonYPosMultiplier, button_width,
                    button_height, button_height / 4);

  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / 3);
  ofScale(font_scale, font_scale, 1.0);
  int connect_string_width = label_font.stringWidth(kConnectingText);
  label_font.drawString(kConnectingText, -connect_string_width / 2, 0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kBackButtonYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  int quit_string_width = button_font.stringWidth(kQuitButtonText);
  int quit_string_height = button_font.stringHeight(kQuitButtonText);
  button_font.drawString(kQuitButtonText, -quit_string_width / 2,
                         quit_string_height * 1.5);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawConnectionFailed() {
  DrawStart();
  ofSetColor(120, 100, 115, 200);
  ofDrawRectangle(0, 0, background_width,
                  background_width / kAspectRatioMultiplier);
  ofSetColor(185, 200, 255, 255);
  int error_box_width = window_width * kErrorBoxWidthMultiplier;
  int error_box_height = error_box_width / 2;
  ofDrawRectRounded(window_width / 2 - error_box_width / 2,
                    window_height / 2 - error_box_height / 2, error_box_width,
                    error_box_height, error_box_height / 8);

  ofSetColor(215, 25, 25, 255);
  int font_height = message_font.getLineHeight();
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height / 2);
  ofScale(font_scale, font_scale, 1);
  int failed_message1_width =
      message_font.stringWidth(kConnectionErrorMessage1);
  message_font.drawString(kConnectionErrorMessage1, -failed_message1_width / 2,
                          -font_height);
  int failed_message2_width =
      message_font.stringWidth(kConnectionErrorMessage2);
  message_font.drawString(kConnectionErrorMessage2, -failed_message2_width / 2,
                          font_height);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawLobby() {
  ofSetColor(240, 200, 140);
  menu_background.draw(0, 0, window_width,
                       window_width / kAspectRatioMultiplier);
  DrawLobbyPlayerBoxes();
  DrawLobbyButtons();
  DrawLobbyPlayerNames();
  DrawLobbySettings();
  DrawLobbyButtonText();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawLobbyPlayerBoxes() {
  ofSetColor(95, 180, 220, 150);
  ofDrawRectRounded(window_width / 2 - player_box_width / 2, player_box_y,
                    player_box_width, player_box_height,
                    player_box_height / 12);
  ofDrawRectRounded(window_width / 2 - player_box_width / 2, player_box_y * 2,
                    player_box_width, player_box_height,
                    player_box_height / 12);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB, kMaxAlpha);
}

void PuzzleDuel::DrawLobbyButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kLobbyStartButtonYPosMultiplier,
                    button_width, button_height, button_height / 4);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height * kLobbyQuitButtonYPosMultiplier,
                    button_width, button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawLobbySettings() {
  ofSetColor(105, 255, 115);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kLobbyIdYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  std::string lobby_id_string = std::to_string(game_manager.port);
  while (lobby_id_string.length() < kPortStrLength) {
    lobby_id_string.insert(0, "0");
  }

  lobby_id_string.insert(0, "Lobby ID: ");
  int lobby_id_string_width = label_font.stringWidth(lobby_id_string);
  label_font.drawString(lobby_id_string, -lobby_id_string_width / 2, 0);
  ofPopMatrix();

  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kLobbySettingsYPosMultiplier);
  ofScale(font_scale, font_scale, 1.0);
  std::string rounds_string = "rounds: " + std::to_string(game_manager.rounds);
  int rounds_string_width = label_font.stringWidth(rounds_string);
  std::string move_time_string =
      "move time: " + std::to_string((int)(game_manager.move_time / 1000)) +
      " seconds";
  int move_time_string_width = label_font.stringWidth(move_time_string);
  label_font.drawString(rounds_string, -rounds_string_width / 2, 0);
  label_font.drawString(move_time_string, -move_time_string_width / 2,
                        label_font.getLineHeight());
  ofPopMatrix();
}

void PuzzleDuel::DrawLobbyPlayerNames() {
  std::string player1_name;
  std::string player2_name;
  if (game_manager.player.IsHost()) {
    player1_name = game_manager.player.GetName();
    player2_name = game_manager.opponent.GetName();
  } else if (game_manager.opponent.IsHost()) {
    player2_name = game_manager.player.GetName();
    player1_name = game_manager.opponent.GetName();
  }

  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2 - player_box_width / 2, player_box_y);
  ofScale(font_scale, font_scale, 1.0);
  button_font.drawString(kLobbyP1Label, 0, button_font.getLineHeight() * 1.25);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2 - player_box_width / 2, player_box_y * 2);
  ofScale(font_scale, font_scale, 1.0);
  button_font.drawString(kLobbyP2Label, 0, button_font.getLineHeight() * 1.25);
  ofPopMatrix();

  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
  ofPushMatrix();
  int p1_label_width = button_font.stringWidth(kLobbyP1Label);
  ofTranslate(window_width / 2 - player_box_width / 2, player_box_y);
  ofScale(font_scale, font_scale, 1.0);
  button_font.drawString(player1_name, p1_label_width,
                         button_font.getLineHeight() * 1.25);
  ofPopMatrix();

  ofPushMatrix();
  int p2_label_width = button_font.stringWidth(kLobbyP2Label);
  ofTranslate(window_width / 2 - player_box_width / 2, player_box_y * 2);
  ofScale(font_scale, font_scale, 1.0);
  button_font.drawString(player2_name, p2_label_width,
                         button_font.getLineHeight() * 1.25);
  ofPopMatrix();
}

void PuzzleDuel::DrawLobbyButtonText() {

}

void PuzzleDuel::DrawGameText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();  // draw round number start
  ofTranslate(window_width / 2, board_start_height / 2);
  ofScale(font_scale, font_scale, 1.0);
  string round_s =
      "Round " + std::to_string(round) + "/" + std::to_string(num_rounds);
  int font_width = game_font.stringWidth(round_s);
  game_font.drawString(round_s, -font_width / 2, 0);
  ofPopMatrix();  // draw round number end

  ofPushMatrix();  // draw player score start

  ofPopMatrix();  // draw player score end
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleDuel::DrawCursor() {
  if (game_manager.game_state == PLAYER_MOVE) {
    ofImage cursor_orb_image;
    if (cursor_orb == Orb::RED) {
      cursor_orb_image = red_orb;
    } else if (cursor_orb == Orb::BLUE) {
      cursor_orb_image = blue_orb;
    } else if (cursor_orb == Orb::GREEN) {
      cursor_orb_image = green_orb;
    } else if (cursor_orb == Orb::YELLOW) {
      cursor_orb_image = yellow_orb;
    } else if (cursor_orb == Orb::WHITE) {
      cursor_orb_image = white_orb;
    } else if (cursor_orb == Orb::PURPLE) {
      cursor_orb_image = purple_orb;
    }

    cursor_orb_image.draw(ofGetMouseX() - orb_diameter / 2,
                          ofGetMouseY() - orb_diameter / 2, orb_diameter,
                          orb_diameter);
  }

  cursor.draw(ofGetMouseX() - cursor_width / 2,
              ofGetMouseY() - cursor_width / 2, cursor_width, cursor_width);
}

void PuzzleDuel::DrawMoveTimeBar() {
  float current_time = ofGetElapsedTimeMillis() - start_time;
  if (current_time <= end_time) {
    float timer_bar = 1.0 - current_time / end_time;

    // color shift from green -> yellow -> red as time runs out
    if (timer_bar >= 0.6) {
      ofSetColor((1.0 - timer_bar) * 250 + 150, 255, 0);
    } else {
      ofSetColor(255, (timer_bar - 0.2) * 640, 0);
    }

    ofDrawRectRounded(ofGetMouseX() - cursor_width / 2,
                      ofGetMouseY() - cursor_width * 3.0 / 4.0,
                      cursor_width * timer_bar, cursor_width / 6, cursor_width);

    ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
  }
}

void PuzzleDuel::DrawCountPoints() {
  /*std::vector<int> &board_points = game_board.GetPointsGrid();
  int current_time = ofGetElapsedTimeMillis();
  if (current_time - start_time >= kDrawCountPointsTimeInterval) {
    start_time = current_time;
    int tile_row;
    int tile_col;
    int tile_x_pos;
    int tile_y_pos;
    int tile_width = window_width / kTileSizeDivisor;
    for (int i = last_count_ind + 1; i < kBoardSize; i++) {
      if (board_points.at(i) == kOrbPointValue) {
        tile_row = i / kOrbsInRowAndCol;
        tile_col = i % kOrbsInRowAndCol;
        tile_x_pos = tile_col * tile_width;
        tile_y_pos = board_start_height + tile_row * tile_width;

        last_count_ind = i;

        count_points.begin();
        ofCircle(tile_x_pos, tile_y_pos, 30);
        count_points.end();

        break;
      }
      if (i == kBoardSize - 1) {
        game_state == PLAYER_TURN;
      }
    }
  }

  count_points.draw(0, 0);*/
}

void PuzzleDuel::DrawBoard() {
  ofSetColor(175, 250, 250);
  board_tiles.draw(0, board_start_height, board_width, board_width);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);

  std::vector<Orb> &board = game_board.GetBoardGrid();
  std::vector<int> &board_points = game_board.GetPointsGrid();
  ofImage orb_image;
  int orb_row;
  int orb_col;
  int orb_x_pos;
  int orb_y_pos;
  int tile_width = window_width / kTileSizeDivisor;
  for (int i = 0; i < kBoardSize; i++) {
    orb_image.clear();
    Orb current_orb = board.at(i);

    if (game_manager.game_state == PLAYER_ERASE_MATCHES &&
        board_points.at(i) == kOrbPointValue) {
      ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB, erase_fade);
    }

    if (current_orb == Orb::RED) {
      orb_image = red_orb;
    } else if (current_orb == Orb::BLUE) {
      orb_image = blue_orb;
    } else if (current_orb == Orb::GREEN) {
      orb_image = green_orb;
    } else if (current_orb == Orb::YELLOW) {
      orb_image = yellow_orb;
    } else if (current_orb == Orb::WHITE) {
      orb_image = white_orb;
    } else if (current_orb == Orb::PURPLE) {
      orb_image = purple_orb;
    }

    orb_row = i / kOrbsInRowAndCol;
    orb_col = i % kOrbsInRowAndCol;
    orb_x_pos = orb_col * tile_width;
    orb_y_pos = board_start_height + orb_row * tile_width;

    orb_image.draw(orb_x_pos, orb_y_pos, orb_diameter, orb_diameter);

    ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB, kDefaultRGB);
  }
}

//--------------------------------------------------------------
void PuzzleDuel::keyPressed(int key) {
  if (game_manager.game_state == CREATE_GAME) {
    if (name_box_selected) {
      if (key == OF_KEY_BACKSPACE && player_name.length() > 0) {
        player_name.pop_back();
      } else if (key == OF_KEY_DEL) {
        player_name.clear();
      } else if (key >= 33 && key <= 126 &&
                 player_name.length() < kMaxNameLength) {
        player_name.push_back(key);
      }
    }
  } else if (game_manager.game_state == JOIN_GAME) {
    if (name_box_selected) {
      if (key == OF_KEY_BACKSPACE && player_name.length() > 0) {
        player_name.pop_back();
      } else if (key == OF_KEY_DEL) {
        player_name.clear();
      } else if (key >= 33 && key <= 126 &&
                 player_name.length() < kMaxNameLength) {
        player_name.push_back(key);
      }
    } else if (port_box_selected) {
      if (key == OF_KEY_BACKSPACE && port_s.length() > 0) {
        port_s.pop_back();
      } else if (key == OF_KEY_DEL) {
        port_s.clear();
      } else if (key >= 48 && key <= 57 && port_s.length() < kPortStrLength) {
        port_s.push_back(key);
      }
    }
  } else if (game_manager.game_state == CONNECTION_FAILED) {
    if (true) {
      player_name.clear();
      port_s.clear();
      game_manager.game_state = START;
    }
  }
}

//--------------------------------------------------------------
void PuzzleDuel::keyReleased(int key) {}

//--------------------------------------------------------------
void PuzzleDuel::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void PuzzleDuel::mouseDragged(int x, int y, int button) {
  if (game_manager.game_state == PLAYER_MOVE) {
    int cursor_row;
    int cursor_col;
    int cursor_tile;
    int tile_width = window_width / kTileSizeDivisor;

    if (x <= 0) {
      cursor_col = 0;
    } else if (x >= window_width - orb_diameter) {
      cursor_col = kOrbsInRowAndCol - 1;
    } else {
      cursor_col = x / tile_width;
    }

    if (y <= board_start_height) {
      cursor_row = 0;
    } else if (y >= window_height - orb_diameter) {
      cursor_row = kOrbsInRowAndCol - 1;
    } else {
      cursor_row = (y - board_start_height) / tile_width;
    }

    cursor_tile = kOrbsInRowAndCol * cursor_row + cursor_col;
    game_board.Swap(cursor_tile, orb_tile);
    orb_tile = cursor_tile;
  } else if (game_manager.game_state == CREATE_GAME) {
    float bar_proportion;
    if (x < slider_bar_x) {
      bar_proportion = 0.0;
    } else if (x > slider_bar_x + slider_bar_length) {
      bar_proportion = 1.0;
    } else {
      bar_proportion = (float)(x - slider_bar_x) / (float)slider_bar_length;
    }

    if (dragging_round_slider == true) {
      float rounds_range = (float)(kMaxRounds - kMinRounds);
      num_rounds = std::round(bar_proportion * rounds_range + kMinRounds);
    } else if (dragging_time_slider == true) {
      float move_time_range = (float)(kMaxMoveTime - kMinMoveTime);
      end_time = std::round(bar_proportion * move_time_range + kMinMoveTime);
    }
  }
}

//--------------------------------------------------------------
void PuzzleDuel::mousePressed(int x, int y, int button) {
  cursor = hand_closed;
  cursor.resize(cursor_width, cursor_width);

  if (game_manager.game_state == START) {
    mouse_clicked_x = x;
    mouse_clicked_y = y;
  } else if (game_manager.game_state == CREATE_GAME) {
    mouse_clicked_x = x;
    mouse_clicked_y = y;
    if (MouseInArea(window_width / 2 - box_width / 2,
                    window_width / 2 + box_width / 2, window_height * 0.4,
                    window_height * 0.4 + box_height)) {
      name_box_selected = true;
    } else {
      name_box_selected = false;
    }

    if (MouseInArea(
            round_slider_x - slider_radius, round_slider_x + slider_radius,
            round_slider_bar_y + slider_bar_height / 2 - slider_radius,
            round_slider_bar_y + slider_bar_height / 2 + slider_radius)) {
      dragging_round_slider = true;
    } else {
      dragging_round_slider = false;
    }

    if (MouseInArea(mt_slider_x - slider_radius, mt_slider_x + slider_radius,
                    mt_slider_bar_y + slider_bar_height / 2 - slider_radius,
                    mt_slider_bar_y + slider_bar_height / 2 + slider_radius)) {
      dragging_time_slider = true;
    } else {
      dragging_time_slider = false;
    }
  } else if (game_manager.game_state == JOIN_GAME) {
    mouse_clicked_x = x;
    mouse_clicked_y = y;
    if (MouseInArea(window_width / 2 - box_width / 2,
                    window_width / 2 + box_width / 2,
                    window_height / kJoinGameBoxYPosDivisor,
                    window_height / kJoinGameBoxYPosDivisor + box_height)) {
      name_box_selected = true;
    } else {
      name_box_selected = false;
    }

    if (MouseInArea(
            window_width / 2 - box_width / 2, window_width / 2 + box_width / 2,
            (window_height / kJoinGameBoxYPosDivisor) * 2,
            (window_height / kJoinGameBoxYPosDivisor) * 2 + box_height)) {
      port_box_selected = true;
    } else {
      port_box_selected = false;
    }
  } else if (game_manager.game_state == CONNECTING) {
    mouse_clicked_x = x;
    mouse_clicked_y = y;
  } else if (game_manager.game_state == PLAYER_TURN) {
    start_time = ofGetElapsedTimeMillis();

    int cursor_row;
    int cursor_col;
    int cursor_tile;
    int tile_width = window_width / kTileSizeDivisor;
    if (MouseInArea(0, board_width, board_start_height, window_height)) {
      cursor_row = (y - board_start_height) / tile_width;
      cursor_col = x / tile_width;
      cursor_tile = kOrbsInRowAndCol * cursor_row + cursor_col;
      cursor_orb = game_board.GetOrb(cursor_tile);
      game_board.SetOrb(cursor_tile, Orb::EMPTY);
      orb_tile = cursor_tile;
      game_manager.game_state = PLAYER_MOVE;
    }
  }
}

//--------------------------------------------------------------
void PuzzleDuel::mouseReleased(int x, int y, int button) {
  cursor = hand_open;
  cursor.resize(cursor_width, cursor_width);
  if (game_manager.game_state == START) {
    if (MouseInArea(window_width / 2 - button_width / 2,
                    window_width / 2 + button_width / 2, window_height / 2,
                    window_height / 2 + button_height)) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height / 2 &&
          mouse_clicked_y < window_height / 2 + button_height) {
        game_manager.game_state = CREATE_GAME;
      }
    } else if (MouseInArea(window_width / 2 - button_width / 2,
                           window_width / 2 + button_width / 2,
                           window_height / 2 + button_height * 1.5,
                           window_height / 2 + button_height * 2.5)) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height / 2 + button_height * 1.5 &&
          mouse_clicked_y < window_height / 2 + button_height * 2.5) {
        game_manager.game_state = JOIN_GAME;
      }
    }
  } else if (game_manager.game_state == CREATE_GAME ||
             game_manager.game_state == JOIN_GAME) {
    dragging_round_slider = false;
    dragging_time_slider = false;
    if (MouseInArea(
            window_width / 2 - button_width / 2,
            window_width / 2 + button_width / 2,
            window_height * kConfirmButtonYPosMultiplier,
            window_height * kConfirmButtonYPosMultiplier + button_height) &&
        player_name.length() > 0) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height * kConfirmButtonYPosMultiplier &&
          mouse_clicked_y <
              window_height * kConfirmButtonYPosMultiplier + button_height) {
        if (game_manager.game_state == CREATE_GAME) {
          game_manager.SetupServer(player_name, end_time, num_rounds);
        } else if (game_manager.game_state == JOIN_GAME &&
                   port_s.length() == kPortStrLength) {
          int port = std::stoi(port_s);
          game_manager.game_state = CONNECTING;
          game_manager.SetupClient(player_name, port);
        }
      }
    } else if (MouseInArea(
                   window_width / 2 - button_width / 2,
                   window_width / 2 + button_width / 2,
                   window_height * kBackButtonYPosMultiplier,
                   window_height * kBackButtonYPosMultiplier + button_height)) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height * kBackButtonYPosMultiplier &&
          mouse_clicked_y <
              window_height * kBackButtonYPosMultiplier + button_height) {
        player_name.clear();
        port_s.clear();
        game_manager.game_state = START;
      }
    }
  } else if (game_manager.game_state == CONNECTING) {
    if (MouseInArea(
            window_width / 2 - button_width / 2,
            window_width / 2 + button_width / 2,
            window_height * kBackButtonYPosMultiplier,
            window_height * kBackButtonYPosMultiplier + button_height)) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height * kBackButtonYPosMultiplier &&
          mouse_clicked_y <
              window_height * kBackButtonYPosMultiplier + button_height) {
        player_name.clear();
        port_s.clear();
        game_manager.game_state = START;
      }
    }
  } else if (game_manager.game_state == PLAYER_MOVE) {
    game_board.SetOrb(orb_tile, cursor_orb);
    cursor_orb = Orb::EMPTY;
    game_board.CalculatePoints();
    game_manager.game_state = PLAYER_ERASE_MATCHES;
  }
}

bool PuzzleDuel::MouseInArea(int x_left, int x_right, int y_top, int y_bottom) {
  int mouse_x = ofGetMouseX();
  int mouse_y = ofGetMouseY();
  if (mouse_x > x_left && mouse_x < x_right && mouse_y > y_top &&
      mouse_y < y_bottom) {
    return true;
  } else {
    return false;
  }
}

//--------------------------------------------------------------
void PuzzleDuel::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void PuzzleDuel::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void PuzzleDuel::windowResized(int w, int h) {
  window_height = h;
  window_width = window_height * kAspectRatioMultiplier;
  board_start_height = window_height - window_width;
  board_width = window_width;
  ofSetWindowShape(window_width, window_height);
  // count_points.allocate(ofGetWindowWidth(), ofGetWindowHeight());

  ResizeCursor();
  ResizeBackground();
  ResizeOrb();
  ResizeUI();
}

void PuzzleDuel::ResizeCursor() {
  cursor_width = window_width / kMouseSizeDivisor;
}

void PuzzleDuel::ResizeBackground() { background_width = window_width; }

void PuzzleDuel::ResizeOrb() {
  orb_diameter = board_width / kOrbDiameterDivisor;
}

void PuzzleDuel::ResizeUI() {
  font_scale = (float)window_width / kDefaultWindowWidth;
  button_width = (float)window_width / kButtonWidthDivisor;
  button_height = window_height / kButtonHeightDivisor;
  box_height = 1.25 * button_height / 2;
  box_width = 0.75 * button_width;
  box_outline_thickness = window_width / kBoxOutlineThicknessDivisor;
  outline_box_height = box_height + 2 * box_outline_thickness;
  outline_box_width = box_width + 2 * box_outline_thickness;
  slider_bar_length = kSliderLengthMultiplier * window_width;
  slider_bar_height = kSliderHeightMultiplier * window_height;
  slider_bar_x = window_width / 2 - slider_bar_length / 2;
  round_slider_bar_y = window_height * kRoundSelectorYPosMultiplier;
  mt_slider_bar_y = window_height * kMoveTimeSelectorYPosMultiplier;
  slider_radius = 2 * slider_bar_height;
  player_box_width = window_width * kLobbyPlayerBoxWidthMultiplier;
  player_box_y = window_height * kLobbyPlayerBoxYPosMultiplier;
  player_box_height = window_height * kLobbyPlayerBoxHeightMultiplier;
}

//--------------------------------------------------------------
void PuzzleDuel::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void PuzzleDuel::dragEvent(ofDragInfo dragInfo) {}
