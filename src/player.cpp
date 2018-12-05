#include "player.h"

Player::Player() {
  score = 0;
  win = false;
}

Player::Player(std::string name, bool is_host) {
  this->name = name;
  this->is_host = is_host;
  score = 0;
  win = false;
}

void Player::SetName(std::string name) { this->name = name; }

std::string Player::GetName() { return name; }

int Player::GetScore() { return score; }

void Player::AddPoints(int points) { score += points; }

bool Player::IsWinner() { return win; }
