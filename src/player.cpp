#include "player.h"

Player::Player() {
  score = 0;
  name = "";
  client_id = 10000;
}

Player::Player(std::string name, bool is_host) {
  this->name = name;
  score = 0;
  this->is_host = is_host;
  client_id = 10000;
}

Player::Player(std::string name, bool is_host, int client_id) {
  this->name = name;
  score = 0;
  this->is_host = is_host;
  this->client_id = client_id;
}

void Player::SetName(std::string name) { this->name = name; }

std::string Player::GetName() { return name; }

int Player::GetScore() { return score; }

void Player::AddPoints(int points) { score += points; }

bool Player::IsHost() { return is_host; }
