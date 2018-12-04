#pragma once

#include <string>

class Player {
 private:
  int score;
  std::string name;
  bool win;

 public:
  Player();
  void SetName(std::string name);
  std::string GetName();
  int GetScore();
  void AddPoints(int points);
  bool IsWinner();
};