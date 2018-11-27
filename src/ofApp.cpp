#include "ofApp.h"

using std::vector;

const int kMouseSizeDivisor = 7;
const int kTileSizeDivisor = 6;
const int kOrbDiameterDivisor = 7;
const double kAspectRatioMultiplier = 0.6;

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

  ResizeCursor();
  ResizeOrb();
  ResizeBackground();

  game_board.GenerateBoard();
}

//--------------------------------------------------------------
void PuzzleBattle::update() {}

//--------------------------------------------------------------
void PuzzleBattle::draw() {
  background.draw(0, 0, background_width, background_width);
  DrawBoard();
  DrawCursor();
}

void PuzzleBattle::DrawCursor() {
  cursor.draw(ofGetMouseX() - cursor_width / 2, ofGetMouseY() - cursor_width / 2,
              cursor_width, cursor_width);
}

void PuzzleBattle::DrawBoard() {
  board_tiles.draw(0, board_start_height, board_width, board_width);

  std::vector<Orb> board = game_board.GetBoardGrid();
  ofImage orb_image;
  int orb_row;
  int orb_col;
  int orb_x_pos;
  int orb_y_pos;
  int tile_width = window_width / kTileSizeDivisor;
  for (int i = 0; i < kBoardSize; i++) {
    if (board.at(i) == Orb::RED) {
      orb_image = red_orb;
    } else if (board.at(i) == Orb::BLUE) {
      orb_image = blue_orb;
    } else if (board.at(i) == Orb::GREEN) {
      orb_image = green_orb;
    } else if (board.at(i) == Orb::YELLOW) {
      orb_image = yellow_orb;
    } else if (board.at(i) == Orb::WHITE) {
      orb_image = white_orb;
    } else if (board.at(i) == Orb::PURPLE) {
      orb_image = purple_orb;
    }

    orb_row = i / kOrbsInRowAndCol;
    orb_col = i % kOrbsInRowAndCol;
    orb_x_pos = orb_col * tile_width + (tile_width - orb_diameter) / 2;
    orb_y_pos = board_start_height + orb_row * tile_width +
                (tile_width - orb_diameter) / 2;

    orb_image.draw(orb_x_pos, orb_y_pos, orb_diameter, orb_diameter);
  }
}

//--------------------------------------------------------------
void PuzzleBattle::keyPressed(int key) {}

//--------------------------------------------------------------
void PuzzleBattle::keyReleased(int key) {}

//--------------------------------------------------------------
void PuzzleBattle::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void PuzzleBattle::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void PuzzleBattle::mousePressed(int x, int y, int button) {
  cursor = hand_closed;
  cursor.resize(cursor_width, cursor_width);
}

//--------------------------------------------------------------
void PuzzleBattle::mouseReleased(int x, int y, int button) {
  cursor = hand_open;
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

  ResizeCursor();
  ResizeBackground();
  ResizeOrb();
}

void PuzzleBattle::ResizeCursor() {
  cursor_width = window_width / kMouseSizeDivisor;
}

void PuzzleBattle::ResizeBackground() { background_width = window_width; }

void PuzzleBattle::ResizeOrb() {
  orb_diameter = board_width / kOrbDiameterDivisor;
}

//--------------------------------------------------------------
void PuzzleBattle::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void PuzzleBattle::dragEvent(ofDragInfo dragInfo) {}
