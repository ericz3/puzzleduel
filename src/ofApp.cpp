#include "ofApp.h"
#include <string>

using std::vector;

const std::string kTitle1 = "PUZZLE";
const std::string kTitle2 = "DUEL";
const std::string kCreateLobbyButtonText = "Create Lobby";
const std::string kJoinLobbyButtonText = "Join Lobby";

unsigned const int kMouseSizeDivisor = 7;
unsigned const int kTileSizeDivisor = 6;
unsigned const int kOrbDiameterDivisor = 6;
unsigned const int kEraseFadeIncrement = 5;
unsigned const int kRoundFontSizeDivisor = 10;
unsigned const int kStartFontSizeDivisor = 8;
unsigned const int kButtonFontSizeDivisor = 18;

// unsigned const int kDrawCountPointsTimeInterval = 400;
const float kDefaultMoveTime = 10000;
unsigned const int kDefaultNumRounds = 5;
unsigned const int kMinRounds = 3;
unsigned const int kMaxRounds = 20;
const float kMaxMoveTime = 20000;
const float kMinMoveTime = 5000;

const float kAspectRatioMultiplier = 0.6;
const float kDefaultWindowWidth = 1024.0;
const float kSliderLengthMultiplier = 0.7;
const float kRoundSelectorHeightMultiplier = 0.1;
const float kMoveTimeSelectorHeightMultiplier = 0.25;
const float kSliderHeightMultiplier = 0.008;
const float kSecondsPerMillisecond = 0.001;

unsigned const int kMaxAlpha = 255;
unsigned const int kDefaultRGB = 255;

//--------------------------------------------------------------
void PuzzleBattle::setup() {
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
  start_background.load("startbackground.jpg");

  game_font.load("Xolonium-Regular.ttf", window_width / kRoundFontSizeDivisor);
  game_font_bold.load("Xolonium-Bold.ttf",
                      window_width / kRoundFontSizeDivisor);
  title_font.load("Xolonium-Bold.ttf", window_width / kStartFontSizeDivisor);
  button_font.load("Xolonium-Regular.ttf",
                   window_width / kButtonFontSizeDivisor);

  ResizeCursor();
  ResizeOrb();
  ResizeBackground();
  ResizeButton();

  ofSetEscapeQuitsApp(false);
  game_board.GenerateBoard();
  game_state = START;
  round = 1;

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
void PuzzleBattle::update() {
  font_scale = (float)window_width / kDefaultWindowWidth;
  if (game_state == PLAYER_ERASE_MATCHES) {
    if (erase_fade == 0) {
      erase_fade = kMaxAlpha;
      game_state = PLAYER_COUNT_POINTS;
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
  }

  if (game_state == PLAYER_MOVE) {
    if (ofGetElapsedTimeMillis() - start_time > end_time) {
      mouseReleased(ofGetMouseX(), ofGetMouseY(), 0);
    }
  }
}

//--------------------------------------------------------------
void PuzzleBattle::draw() {
  if (game_state == START) {
    DrawStart();
  } else if (game_state == CREATE_GAME) {
    DrawCreateGame();
  } else {
    background.draw(0, 0, background_width, background_width);
    DrawGameText();
    DrawBoard();
    if (game_state == PLAYER_COUNT_POINTS) {
      DrawCountPoints();
    }
    if (game_state == PLAYER_MOVE) {
      DrawMoveTimeBar();
    }
  }

  DrawCursor();
}

void PuzzleBattle::DrawStart() {
  start_background.draw(0, 0, window_width,
                        window_width / kAspectRatioMultiplier);
  DrawStartButtons();
  DrawStartTitle();
  DrawStartButtonsText();
}

void PuzzleBattle::DrawStartButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2, window_height / 2,
                    button_width, button_height, button_height / 4);
  ofDrawRectRounded(window_width / 2 - button_width / 2,
                    window_height / 2 + button_height * 1.5, button_width,
                    button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleBattle::DrawStartTitle() {
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

void PuzzleBattle::DrawStartButtonsText() {
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
  int font_width_button2 = button_font.stringWidth(kJoinLobbyButtonText);
  int font_height_button2 = button_font.stringHeight(kJoinLobbyButtonText);
  button_font.drawString(kJoinLobbyButtonText, -font_width_button2 / 2,
                         font_height_button2 * 1.5);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleBattle::DrawCreateGame() {
  start_background.draw(0, 0, window_width,
                        window_width / kAspectRatioMultiplier);
  DrawSettingsSliders();
  DrawSettingsSlidersText();
  DrawCreateGameButtons();
  DrawCreateGameButtonsText();
}

void PuzzleBattle::DrawSettingsSliders() {
  int slider_length = kSliderLengthMultiplier * window_width;
  int slider_height = kSliderHeightMultiplier * window_height;
  int slider_x = window_width / 2 - slider_length / 2;
  int round_slider_y = window_height * kRoundSelectorHeightMultiplier;
  int mt_slider_y = window_height * kMoveTimeSelectorHeightMultiplier;
  ofSetColor(200, 250, 255);
  ofDrawRectangle(slider_x, round_slider_y, slider_length, slider_height);
  ofDrawRectangle(slider_x, mt_slider_y, slider_length, slider_height);

  ofSetColor(250, 230, 40);
  float round_slide_proportion =
      (float)(num_rounds - kMinRounds) / (float)(kMaxRounds - kMinRounds);
  ofDrawCircle(round_slide_proportion * slider_length + slider_x,
               round_slider_y + slider_height / 2, slider_height * 2.0);
  float mt_slide_porportion =
      ((float)(end_time - kMinMoveTime) / (float)(kMaxMoveTime - kMinMoveTime));
  ofDrawCircle(mt_slide_porportion * slider_length + slider_x,
               mt_slider_y + slider_height / 2, slider_height * 2.0);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleBattle::DrawSettingsSlidersText() {
  ofSetColor(250, 220, 65);
  ofPushMatrix();
  ofTranslate(window_width / 2, window_height * kRoundSelectorHeightMultiplier);
  ofScale(font_scale * 0.85, font_scale * 0.85, 1.0);
  std::string rounds_string = "Rounds: " + std::to_string(num_rounds);
  int font_width_rounds = button_font.stringWidth(rounds_string);
  int font_height_rounds = button_font.stringHeight(rounds_string);
  button_font.drawString(rounds_string, -font_width_rounds / 2,
                         font_height_rounds * 3);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(window_width / 2,
              window_height * kMoveTimeSelectorHeightMultiplier);
  ofScale(font_scale * 0.85, font_scale * 0.85, 1.0);
  std::string move_time_string =
      "Move Time: " +
      std::to_string((int)std::round(end_time * kSecondsPerMillisecond)) +
      " Seconds";
  int font_width_mt = button_font.stringWidth(move_time_string);
  int font_height_mt = button_font.stringHeight(move_time_string);
  button_font.drawString(move_time_string, -font_width_mt / 2,
                         font_height_mt * 3);
  ofPopMatrix();
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleBattle::DrawCreateGameButtons() {
  ofSetColor(125, 200, 220);
  ofDrawRectRounded(window_width / 2 - button_width / 2, window_height * 0.6,
                    button_width, button_height, button_height / 4);
  ofDrawRectRounded(window_width / 2 - button_width / 2, window_height * 0.75,
                    button_width, button_height, button_height / 4);
  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
}

void PuzzleBattle::DrawCreateGameButtonsText() {}

void PuzzleBattle::DrawGameText() {
  ofPushMatrix();  // draw round number start
  ofSetColor(250, 220, 65);

  ofTranslate(window_width / 2, board_start_height / 2);
  ofScale(font_scale, font_scale, 1.0);

  std::string round_s =
      "Round " + std::to_string(round) + "/" + std::to_string(num_rounds);
  int font_width = game_font.stringWidth(round_s);
  game_font.drawString(round_s, -font_width / 2, 0);

  ofSetColor(kDefaultRGB, kDefaultRGB, kDefaultRGB);
  ofPopMatrix();  // draw round number end

  ofPushMatrix();  // draw player score start

  ofPopMatrix();  // draw player score end
}

void PuzzleBattle::DrawCursor() {
  if (game_state == PLAYER_MOVE) {
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

void PuzzleBattle::DrawMoveTimeBar() {
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

void PuzzleBattle::DrawCountPoints() {
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

void PuzzleBattle::DrawBoard() {
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

    if (game_state == PLAYER_ERASE_MATCHES &&
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
void PuzzleBattle::keyPressed(int key) {}

//--------------------------------------------------------------
void PuzzleBattle::keyReleased(int key) {}

//--------------------------------------------------------------
void PuzzleBattle::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void PuzzleBattle::mouseDragged(int x, int y, int button) {
  if (game_state == PLAYER_MOVE) {
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
  }
}

//--------------------------------------------------------------
void PuzzleBattle::mousePressed(int x, int y, int button) {
  cursor = hand_closed;
  cursor.resize(cursor_width, cursor_width);
  if (game_state == START) {
    if (x > window_width / 2 - button_width / 2 &&
        x < window_width / 2 + button_width / 2 && y > window_height / 2 &&
        y < window_height / 2 + button_height) {
      mouse_clicked_x = x;
      mouse_clicked_y = y;
    } else if (x > window_width / 2 - button_width / 2 &&
               x < window_width / 2 + button_width / 2 &&
               y > window_height / 2 + button_height * 1.5 &&
               y < window_height / 2 + button_height * 2.5) {
      mouse_clicked_x = x;
      mouse_clicked_y = y;
    }
  } else if (game_state == PLAYER_TURN) {
    start_time = ofGetElapsedTimeMillis();

    int cursor_row;
    int cursor_col;
    int cursor_tile;
    int tile_width = window_width / kTileSizeDivisor;
    if (x > 0 && x < board_width && y < window_height &&
        y > board_start_height) {
      cursor_row = (y - board_start_height) / tile_width;
      cursor_col = x / tile_width;
      cursor_tile = kOrbsInRowAndCol * cursor_row + cursor_col;
      cursor_orb = game_board.GetOrb(cursor_tile);
      game_board.SetOrb(cursor_tile, Orb::EMPTY);
      orb_tile = cursor_tile;
      game_state = PLAYER_MOVE;
    }
  }
}

//--------------------------------------------------------------
void PuzzleBattle::mouseReleased(int x, int y, int button) {
  cursor = hand_open;
  cursor.resize(cursor_width, cursor_width);
  if (game_state == START) {
    if (x > window_width / 2 - button_width / 2 &&
        x < window_width / 2 + button_width / 2 && y > window_height / 2 &&
        y < window_height / 2 + button_height) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height / 2 &&
          mouse_clicked_y < window_height / 2 + button_height) {
        game_state = CREATE_GAME;
      }
    } else if (x > window_width / 2 - button_width / 2 &&
               x < window_width / 2 + button_width / 2 &&
               y > window_height / 2 + button_height * 1.5 &&
               y < window_height / 2 + button_height * 2.5) {
      if (mouse_clicked_x > window_width / 2 - button_width / 2 &&
          mouse_clicked_x < window_width / 2 + button_width / 2 &&
          mouse_clicked_y > window_height / 2 + button_height * 1.5 &&
          mouse_clicked_y < window_height / 2 + button_height * 2.5) {
        game_state = JOIN_GAME;
      }
    }
  }

  else if (game_state == PLAYER_MOVE) {
    game_board.SetOrb(orb_tile, cursor_orb);
    cursor_orb = Orb::EMPTY;
    game_board.CalculatePoints();
    game_state = PLAYER_ERASE_MATCHES;
  }
}

//--------------------------------------------------------------
void PuzzleBattle::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void PuzzleBattle::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void PuzzleBattle::windowResized(int w, int h) {
  window_height = h;
  window_width = window_height * kAspectRatioMultiplier;
  board_start_height = window_height - window_width;
  board_width = window_width;
  ofSetWindowShape(window_width, window_height);
  // count_points.allocate(ofGetWindowWidth(), ofGetWindowHeight());

  ResizeCursor();
  ResizeBackground();
  ResizeOrb();
  ResizeButton();
}

void PuzzleBattle::ResizeCursor() {
  cursor_width = window_width / kMouseSizeDivisor;
}

void PuzzleBattle::ResizeBackground() { background_width = window_width; }

void PuzzleBattle::ResizeOrb() {
  orb_diameter = board_width / kOrbDiameterDivisor;
}

void PuzzleBattle::ResizeButton() {
  button_width = window_width * 2.0 / 3.0;
  button_height = window_height / 10;
}

//--------------------------------------------------------------
void PuzzleBattle::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void PuzzleBattle::dragEvent(ofDragInfo dragInfo) {}
