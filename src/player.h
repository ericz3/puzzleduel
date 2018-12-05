#pragma once

#include <string>

class Player {
 private:
  int score;
  std::string name;
  bool win;
  bool is_host;

 public:
  Player();
  Player(std::string name, bool is_host);
  void SetName(std::string name);
  std::string GetName();
  int GetScore();
  void AddPoints(int points);
  bool IsWinner();
};