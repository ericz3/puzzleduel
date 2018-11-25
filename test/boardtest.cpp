#define CATCH_CONFIG_MAIN
#include "board.h"
#include "catch.hpp"

const int kBoardSize = 36;

TEST_CASE("generate board") {
  Board board;
  board.GenerateBoard();
  vector<Orb> board_grid = board.GetBoardGrid();
  for (int i = 0; i < kBoardSize; i++) {
    if (i / 6 == 0) {
      if (i != 0) {
        REQUIRE(board_grid.at(i) != board_grid.at(i - 1));
      }
    } else {
      if (i % 6 == 0) {
        REQUIRE(board_grid.at(i) != board_grid.at(i - 6));
      } else {
        REQUIRE(board_grid.at(i) != board_grid.at(i - 6));
        REQUIRE(board_grid.at(i) != board_grid.at(i - 1));
      }
    }
  }
}