#include "ofApp.h"

using std::vector;

unsigned const int kMouseSizeDivisor = 7;
unsigned const int kTileSizeDivisor = 6;
unsigned const int kOrbDiameterDivisor = 6;
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

  ofSetEscapeQuitsApp(false);
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
  cursor.draw(ofGetMouseX() - cursor_width / 2,
              ofGetMouseY() - cursor_width / 2, cursor_width, cursor_width);
}

void PuzzleBattle::DrawBoard() {
  board_tiles.draw(0, board_start_height, board_width, board_width);

  std::vector<Orb> &board = game_board.GetBoardGrid();
  ofImage orb_image;
  int orb_row;
  int orb_col;
  int orb_x_pos;
  int orb_y_pos;
  int tile_width = window_width / kTileSizeDivisor;
  for (int i = 0; i < kBoardSize; i++) {
    orb_image.clear();
    Orb current_orb = board.at(i);
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
  /*
    cursor_row = (y - board_start_height) / tile_width;
    cursor_col = x / tile_width;
  */
  cursor_tile = kOrbsInRowAndCol * cursor_row + cursor_col;
  game_board.Swap(cursor_tile, orb_tile);
  orb_tile = cursor_tile;
}

//--------------------------------------------------------------
void PuzzleBattle::mousePressed(int x, int y, int button) {
  cursor = hand_closed;
  cursor.resize(cursor_width, cursor_width);

  // if not player turn then return;

  int cursor_row;
  int cursor_col;
  int cursor_tile;
  int tile_width = window_width / kTileSizeDivisor;
  // if cursor not on board then return;
  if (x > 0 && x < board_width && y < window_height &&
      y > board_start_height) {
    cursor_row = (y - board_start_height) / tile_width;
    cursor_col = x / tile_width;
    cursor_tile = kOrbsInRowAndCol * cursor_row + cursor_col;
    cursor_orb = game_board.GetOrb(cursor_tile);
    game_board.SetOrb(cursor_tile, Orb::EMPTY);
    orb_tile = cursor_tile;
  }
}

//--------------------------------------------------------------
void PuzzleBattle::mouseReleased(int x, int y, int button) {
  cursor = hand_open;
  game_board.SetOrb(orb_tile, cursor_orb);
  cursor_orb = Orb::EMPTY;

  game_board.CalculatePoints();
  vector<int> &points_board = game_board.GetPointsGrid();
  for (int i = 0; i < kBoardSize; i++) {
    int points = points_board.at(i);
    if (points == kOrbPointValue) {
      game_board.SetOrb(i, Orb::EMPTY);
	}
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
