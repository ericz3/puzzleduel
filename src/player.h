#pragma once

#include <string>

class Player {
 private:
  int score;
  std::string name;
  bool is_host;

 public:
  int client_id;

  Player();
  Player(std::string name, bool is_host);
  Player(std::string name, bool is_host, int client_id);
  void SetName(std::string name);
  std::string GetName();
  int GetScore();
  void AddPoints(int points);
  bool IsHost();
};