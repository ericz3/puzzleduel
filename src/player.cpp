#include "player.h"

Player::Player(std::string name) {
  this->name = name;
  score = 0;
  win = false;
}

std::string Player::GetName() { return name; }

int Player::GetScore() { return score; }

void Player::AddPoints(int points) { score += points; }

bool Player::IsWinner() { return win; }
