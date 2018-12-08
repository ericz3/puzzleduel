#include "gamemanager.h"
#include <thread>

unsigned const int kMaxPort = 65535;
const string kMessageDelimiter = "\n";
unsigned const int kConnectionTimeOut = 30000;
unsigned const int kConnectTimeInterval = 3000;

GameManager::GameManager() {
  connected = false;
  game_state = START;
  player = Player();
  opponent = Player();
}

void GameManager::SetupClient(std::string player_name, int port) {
  this->port = port;
  player = Player(player_name, false);
  std::thread connect(&GameManager::ConnectClient, this);
  connect.detach();
}

void GameManager::SetupServer(std::string player_name) {
  player = Player(player_name, true);
  std::thread connect(&GameManager::CreateServer, this);
  connect.detach();
}

bool GameManager::IsConnected() { return connected; }

void GameManager::ConnectClient() {
  int connection_start_time = ofGetElapsedTimeMillis();
  int connect_time = 0;
  ofxTCPSettings settings(port);
  while (!client.isConnected() &&
         ofGetElapsedTimeMillis() - connection_start_time <=
             kConnectionTimeOut) {
    if (game_state != CONNECTING) {
      return;
    }

    client.setup(settings);
    client.setMessageDelimiter(kMessageDelimiter);
    connect_time = ofGetElapsedTimeMillis();
  }

  if (client.isConnected()) {
    game_state = LOBBY;
  } else {
    game_state = CONNECTION_FAILED;
  }
}

void GameManager::CreateServer() {
  port = rand() % kMaxPort + 1;
  ofxTCPSettings settings(port);
  server.setup(settings);
  server.setMessageDelimiter(kMessageDelimiter);
}
