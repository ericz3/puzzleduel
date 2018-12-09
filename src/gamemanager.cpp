#include "gamemanager.h"
#include <string>
#include <thread>

unsigned const int kMaxPort = 65535;
const string kMessageDelimiter = "\n";
const string kMessageValueDivider = " ";
unsigned const int kConnectionTimeOut = 30000;
unsigned const int kConnectTimeInterval = 3000;

GameManager::GameManager() {
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

void GameManager::SetupServer(std::string player_name, float move_time,
                              int rounds) {
  player = Player(player_name, true);
  this->move_time = move_time;
  this->rounds = rounds;
  port = rand() % kMaxPort + 1;
  ofxTCPSettings settings(port);
  server.setup(settings);
  server.setMessageDelimiter(kMessageDelimiter);
  game_state = LOBBY;
  std::thread send_game_info(&GameManager::SyncSettingsHost, this);
  send_game_info.detach();
}

void GameManager::SyncSettingsHost() {
  while (game_state == LOBBY) {
    for (int client_id = 0; client_id < server.getLastID(); client_id++) {
      if (server.isClientConnected(client_id)) {
        server.send(client_id, std::to_string(move_time) + " " +
                                   std::to_string(rounds) + " " +
                                   player.GetName());
        /* std::string message;
         std::string messages;*/
        if (opponent.GetName().empty()) {
          std::string opponent_name = server.receive(client_id);
          opponent = Player(opponent_name, false);
        }
      }
    }
  }
}

void GameManager::SyncSettingsClient() {
  std::string game_info = "";
  if (client.isConnected()) {
    while (game_info.length() == 0) {
      game_info = client.receive();
    }
    client.send(player.GetName());

    int divider1_pos = game_info.find(" ") + 1;
    move_time = float(std::stoi(game_info.substr(0, divider1_pos)));
    game_info.erase(0, divider1_pos);
    int divider2_pos = game_info.find(" ") + 1;
    rounds = int(std::stoi(game_info.substr(0, divider2_pos)));
    game_info.erase(0, divider2_pos);
    opponent = Player(game_info, true);
  }
}

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
    SyncSettingsClient();
  } else {
    game_state = CONNECTION_FAILED;
  }
}
