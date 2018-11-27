#pragma once

#include <iostream>
#include <vector>
#include "ofMain.h"

const int kBoardSize = 36;
const int kBoardWidth = 6;
const int kOrbTypes = 6;
const int kOrbPointValue = 1;

enum class Orb {
  EMPTY = 0,
  RED = 1,
  BLUE = 2,
  GREEN = 3,
  WHITE = 4,
  YELLOW = 5,
  PURPLE = 6
};

class Board {
 public:
  // create a starting board in which no orbs of the same color are touching
  void GenerateBoard();
  // set board_grid to given vector
  void SetBoard(std::vector<Orb> board);
  // calculates number of points earned in a solve
  int CalculatePoints();
  // swap positions of 2 orbs
  void Swap(int pos1, int pos2);
  std::vector<Orb> GetBoardGrid();
  void Update();

 private:
  std::vector<Orb> board_grid;
};

std::ostream& operator<<(std::ostream& os, const Orb& obj);