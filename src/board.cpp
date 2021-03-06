#include "board.h"
#include <cstdlib>

using std::vector;

void Board::GenerateBoard() {
  board_grid.clear();
  board_points = vector<int>(kBoardSize, 0);

  for (int i = 0; i < kBoardSize; i++) {
    int col = i % kOrbsInRowAndCol;
    int row = i / kOrbsInRowAndCol;

    if (row == 0) {
      if (col == 0) {
        board_grid.push_back(Orb(rand() % kOrbTypes + 1));
      } else {
        Orb temp = Orb(rand() % kOrbTypes + 1);
        while (temp == board_grid.at(i - 1)) {
          temp = Orb(rand() % kOrbTypes + 1);
        }

        board_grid.push_back(temp);
      }
    } else {
      if (col == 0) {
        Orb temp = Orb(rand() % kOrbTypes + 1);
        while (temp == board_grid.at(i - kOrbsInRowAndCol)) {
          temp = Orb(rand() % kOrbTypes + 1);
        }

        board_grid.push_back(temp);
      } else {
        Orb temp = Orb(rand() % kOrbTypes + 1);
        while (temp == board_grid.at(i - kOrbsInRowAndCol) ||
               temp == board_grid.at(i - 1)) {
          temp = Orb(rand() % kOrbTypes + 1);
        }

        board_grid.push_back(temp);
      }
    }
  }
}

void Board::SetBoard(std::vector<Orb> board) { board_grid = board; }

int Board::CalculatePoints() {
  board_points = vector<int>(kBoardSize, 0);
  int points_sum = 0;

  for (int pos = 0; pos < kBoardSize; pos++) {
    Orb current = board_grid.at(pos);
    int row = pos / kOrbsInRowAndCol;
    int col = pos % kOrbsInRowAndCol;
    if (row < 4) {
      if (col < 4) {
        if (current == board_grid.at(pos + 1) &&
            current == board_grid.at(pos + 2)) {
          board_points.at(pos) = kOrbPointValue;
          board_points.at(pos + 1) = kOrbPointValue;
          board_points.at(pos + 2) = kOrbPointValue;
        }
      }

      if (current == board_grid.at(pos + kOrbsInRowAndCol) &&
          current == board_grid.at(pos + kOrbsInRowAndCol + kOrbsInRowAndCol)) {
        board_points.at(pos) = kOrbPointValue;
        board_points.at(pos + kOrbsInRowAndCol) = kOrbPointValue;
        board_points.at(pos + kOrbsInRowAndCol + kOrbsInRowAndCol) =
            kOrbPointValue;
      }
    } else {
      if (col < 4) {
        if (current == board_grid.at(pos + 1) &&
            current == board_grid.at(pos + 2)) {
          board_points.at(pos) = kOrbPointValue;
          board_points.at(pos + 1) = kOrbPointValue;
          board_points.at(pos + 2) = kOrbPointValue;
        }
      }
    }
  }

  for (int point : board_points) {
    points_sum += point;
  }

  return points_sum;
}

void Board::Swap(int pos1, int pos2) {
  Orb temp = board_grid.at(pos1);
  board_grid.at(pos1) = board_grid.at(pos2);
  board_grid.at(pos2) = temp;
}

Orb Board::GetOrb(int pos) { return board_grid.at(pos); }

void Board::SetOrb(int pos, Orb orb) { board_grid.at(pos) = orb; }

vector<Orb> Board::GetBoardGrid() { return board_grid; }

vector<int> Board::GetPointsGrid() { return board_points; }

std::string Board::ToString() {
  std::string board_string;
  board_string.reserve(kBoardSize);
  for (int i = 0; i < kBoardSize; i++) {
    int orb_val = (int)board_grid.at(i);
    board_string.append(std::to_string(orb_val));
  }

  return board_string;
}

std::ostream& operator<<(std::ostream& os, const Orb& obj) {
  os << static_cast<std::underlying_type<Orb>::type>(obj);
  return os;
}
