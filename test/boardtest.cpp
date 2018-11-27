#define CATCH_CONFIG_MAIN
#include "board.h"
#include "catch.hpp"

using std::vector;

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

TEST_CASE("Calculate Points") {
  Board board;
  board.GenerateBoard();

  SECTION("no matches") {
    // no same color orbs touching
    REQUIRE(board.CalculatePoints() == 0);

    /* 2 in a row same color
                B B .
                B
                .
        */
    vector<Orb> test_board = board.GetBoardGrid();
    test_board.at(0) = Orb::BLUE;
    test_board.at(1) = Orb::BLUE;
    test_board.at(6) = Orb::BLUE;
    test_board.at(2) = Orb::RED;
    test_board.at(12) = Orb::RED;
    REQUIRE(board.CalculatePoints() == 0);
  }

  SECTION("3 in row matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    // BBB...
    test_board.at(0) = Orb::BLUE;
    test_board.at(1) = Orb::BLUE;
    test_board.at(2) = Orb::BLUE;
    test_board.at(3) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    // .BBB..
    test_board.at(0) = Orb::RED;
    test_board.at(3) = Orb::BLUE;
    test_board.at(4) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    // ..BBB.
    test_board.at(1) = Orb::RED;
    test_board.at(4) = Orb::BLUE;
    test_board.at(5) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    // ...BBB
    test_board.at(2) = Orb::GREEN;
    test_board.at(5) = Orb::BLUE;
    test_board.at(6) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    // 2 matches in 1 row: RRRBBB
    test_board.at(2) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 6);
  }

  SECTION("4 in a row matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    // BBBB..
    test_board.at(0) = Orb::BLUE;
    test_board.at(1) = Orb::BLUE;
    test_board.at(2) = Orb::BLUE;
    test_board.at(3) = Orb::BLUE;
    test_board.at(4) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);

    // .BBBB.
    board.GenerateBoard();
    test_board = board.GetBoardGrid();
    test_board.at(6) = Orb::RED;
    test_board.at(7) = Orb::BLUE;
    test_board.at(8) = Orb::BLUE;
    test_board.at(9) = Orb::BLUE;
    test_board.at(10) = Orb::BLUE;
    test_board.at(11) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);

    // ..BBBB
    board.GenerateBoard();
    test_board = board.GetBoardGrid();
    test_board.at(6) = Orb::RED;
    test_board.at(7) = Orb::RED;
    test_board.at(8) = Orb::BLUE;
    test_board.at(9) = Orb::BLUE;
    test_board.at(10) = Orb::BLUE;
    test_board.at(11) = Orb::BLUE;
    test_board.at(12) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);
  }

  SECTION("5 in a row matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    // BBBBB.
    test_board.at(30) = Orb::BLUE;
    test_board.at(31) = Orb::BLUE;
    test_board.at(32) = Orb::BLUE;
    test_board.at(33) = Orb::BLUE;
    test_board.at(34) = Orb::BLUE;
    test_board.at(35) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 5);

    // .BBBBB
    test_board.at(30) = Orb::RED;
    test_board.at(31) = Orb::BLUE;
    test_board.at(32) = Orb::BLUE;
    test_board.at(33) = Orb::BLUE;
    test_board.at(34) = Orb::BLUE;
    test_board.at(35) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 5);
  }

  SECTION("3 in a column matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
        B
        B
        B
        .
        .
        .
    */
    test_board.at(0) = Orb::BLUE;
    test_board.at(6) = Orb::BLUE;
    test_board.at(12) = Orb::BLUE;
    test_board.at(18) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    /*
        .
        B
        B
        B
        .
        .
    */
    test_board.at(0) = Orb::RED;
    test_board.at(18) = Orb::BLUE;
    test_board.at(24) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    /*
        .
        .
        B
        B
        B
        .
    */
    test_board.at(6) = Orb::RED;
    test_board.at(24) = Orb::BLUE;
    test_board.at(30) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    /*
        .
        .
        .
        B
        B
        B
    */
    test_board.at(12) = Orb::GREEN;
    test_board.at(30) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 3);

    /*
        R
        R
        R
        B
        B
        B
    */
    test_board.at(12) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 6);
  }

  SECTION("4 in a column matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
        B
        B
        B
        B
        .
        .
    */
    test_board.at(5) = Orb::BLUE;
    test_board.at(11) = Orb::BLUE;
    test_board.at(17) = Orb::BLUE;
    test_board.at(23) = Orb::BLUE;
    test_board.at(29) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);

    /*
        .
        B
        B
        B
        B
        .
    */
    test_board.at(5) = Orb::RED;
    test_board.at(29) = Orb::BLUE;
    test_board.at(35) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);

    /*
        .
        .
        B
        B
        B
        B
    */
    test_board.at(11) = Orb::RED;
    test_board.at(35) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 4);
  }

  SECTION("5 in a column matches") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
        B
        B
        B
        B
        B
        .
    */
    test_board.at(3) = Orb::BLUE;
    test_board.at(9) = Orb::BLUE;
    test_board.at(15) = Orb::BLUE;
    test_board.at(21) = Orb::BLUE;
    test_board.at(27) = Orb::BLUE;
    test_board.at(33) = Orb::RED;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 5);

    /*
        .
        B
        B
        B
        B
        B
    */
    test_board.at(3) = Orb::RED;
    test_board.at(33) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 5);
  }

  SECTION("+  shape match") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
         . . . . . .
         . . . B . .
         . . B B B .
         . . . B . .
         . . . B . .
         . . . . . .
        */
    test_board.at(3) = Orb::RED;
    test_board.at(33) = Orb::RED;
    test_board.at(13) = Orb::RED;
    test_board.at(17) = Orb::RED;
    test_board.at(9) = Orb::BLUE;
    test_board.at(15) = Orb::BLUE;
    test_board.at(21) = Orb::BLUE;
    test_board.at(27) = Orb::BLUE;
    test_board.at(14) = Orb::BLUE;
    test_board.at(16) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 6);
  }

  SECTION("L shape match") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
         . . . . . .
         . B . . . .
         . B . . . .
         . B . . . .
         . B B B . .
         . . . . . .
        */
    test_board.at(1) = Orb::RED;
    test_board.at(31) = Orb::RED;
    test_board.at(24) = Orb::RED;
    test_board.at(28) = Orb::RED;
    test_board.at(7) = Orb::BLUE;
    test_board.at(13) = Orb::BLUE;
    test_board.at(19) = Orb::BLUE;
    test_board.at(25) = Orb::BLUE;
    test_board.at(26) = Orb::BLUE;
    test_board.at(27) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 6);
  }

  SECTION("T shape match") {
    vector<Orb> test_board = board.GetBoardGrid();

    /*
         . B B B B .
         . . . B . .
         . . . B . .
         . . . B . .
         . . . B . .
         . . . . . .
        */
    test_board.at(0) = Orb::RED;
    test_board.at(5) = Orb::RED;
    test_board.at(33) = Orb::RED;
    test_board.at(1) = Orb::BLUE;
    test_board.at(2) = Orb::BLUE;
    test_board.at(3) = Orb::BLUE;
    test_board.at(4) = Orb::BLUE;
    test_board.at(9) = Orb::BLUE;
    test_board.at(15) = Orb::BLUE;
    test_board.at(21) = Orb::BLUE;
    test_board.at(27) = Orb::BLUE;
    board.SetBoard(test_board);
    REQUIRE(board.CalculatePoints() == 8);
  }
}

TEST_CASE("Swap orbs") {
  Board board;
  board.GenerateBoard();

  SECTION("Vertical swwap") {
    int pos1 = 7;
    int pos2 = 13;
    Orb orb1 = board.GetBoardGrid().at(pos1);
    Orb orb2 = board.GetBoardGrid().at(pos2);
    board.Swap(pos1, pos2);
    REQUIRE(board.GetBoardGrid().at(pos1) == orb2);
    REQUIRE(board.GetBoardGrid().at(pos2) == orb1);
  }

  SECTION("Horizontal swap") {
    int pos1 = 22;
    int pos2 = 16;
    Orb orb1 = board.GetBoardGrid().at(pos1);
    Orb orb2 = board.GetBoardGrid().at(pos2);
    board.Swap(pos1, pos2);
    REQUIRE(board.GetBoardGrid().at(pos1) == orb2);
    REQUIRE(board.GetBoardGrid().at(pos2) == orb1);
  }

  SECTION("Diagonal swap") {
    int pos1 = 19;
    int pos2 = 26;
    Orb orb1 = board.GetBoardGrid().at(pos1);
    Orb orb2 = board.GetBoardGrid().at(pos2);
    board.Swap(pos1, pos2);
    REQUIRE(board.GetBoardGrid().at(pos1) == orb2);
    REQUIRE(board.GetBoardGrid().at(pos2) == orb1);
  }
}