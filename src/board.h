#pragma once

#include <iostream>
#include <vector>
#include "ofMain.h"

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
  void SetBoard(std::vector<Orb> board);
  // create a starting board in which no orbs of the same color are touching
  void GenerateBoard();
  void Update();
  // calculates number of points earned in a solve
  int CalculatePoints();
  //swap positions of 2 orbs
  void Swap(int pos1, int pos2); 
  std::vector<Orb> GetBoardGrid();

 private:
  std::vector<Orb> board_grid;
  int CountMatches();
  void Draw();
};

std::ostream& operator<<(std::ostream& os, const Orb& obj);