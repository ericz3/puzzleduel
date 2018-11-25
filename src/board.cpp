#include "board.h"
#include <cstdlib>

const int kBoardSize = 36;

void Board::GenerateBoard() {
  for (int i = 0; i < kBoardSize; i++) {
    if (i / 6 == 0) {
      if (i == 0) {
        board_grid.push_back(Orb(rand() % 6 + 1));
      } else {
        Orb temp = Orb(rand() % 6 + 1);
        while (temp == board_grid.at(i - 1)) {
          temp = Orb(rand() % 6 + 1);
        }

        board_grid.push_back(temp);
      }
    } else {
      if (i % 6 == 0) {
        Orb temp = Orb(rand() % 6 + 1);
        while (temp == board_grid.at(i - 6)) {
          temp = Orb(rand() % 6 + 1);
        }

        board_grid.push_back(temp);
      } else {
        Orb temp = Orb(rand() % 6 + 1);
        while (temp == board_grid.at(i - 6) || temp == board_grid.at(i - 1)) {
          temp = Orb(rand() % 6 + 1);
        }

        board_grid.push_back(temp);
      }
    }
  }
}

void Board::Update() {}

int Board::CalculatePoints() { return 0; }

vector<Orb> Board::GetBoardGrid() { return board_grid; }

void Board::DrawBoard() {}

int Board::CountMatches() { return 0; }

std::ostream& operator<<(std::ostream& os, const Orb& obj) {
  os << static_cast<std::underlying_type<Orb>::type>(obj);
  return os;
}
