#pragma once

#include <vector>
#include <iostream>
#include "ofMain.h"

using std::vector;

enum class Orb {
  EMPTY = 0,
  RED = 1,
  BLUE = 2,
  GREEN = 3,
  ORANGE = 4,
  YELLOW = 5,
  PURPLE = 6
};

class Board {
 public:
  void GenerateBoard();
  void Update();
  int CalculatePoints();
  vector<Orb> GetBoardGrid();

 private:
  vector<Orb> board_grid;
  void DrawBoard();
  int CountMatches();
};

std::ostream& operator<<(std::ostream& os, const Orb& obj);