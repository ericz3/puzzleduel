#include "gamemanager.h"
#include <string>
#include <thread>

unsigned const int kMaxPort = 65535;
const string kMessageDelimiter = "\n";
const string kMessageValueDivider = " ";
unsigned const int kConnectionTimeOut = 30000;
unsigned const int kConnectTimeInterval = 3000;
const char kBoardMessageHeader = 'B';

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

void GameManager::SetupServer(std::string player_name) {
  player = Player(player_name, true);
  port = rand() % kMaxPort + 1;
  ofxTCPSettings settings(port);
  server.setup(settings);
  server.setMessageDelimiter(kMessageDelimiter);
  game_state = LOBBY;
  std::thread send_game_info(&GameManager::SyncSettingsHost, this);
  send_game_info.detach();
}

void GameManager::DisconnectLobby() {
  if (player.IsHost()) {
    std::thread dc_host(&GameManager::DisconnectHost, this);
    dc_host.detach();
  } else {
    std::thread dc_client(&GameManager::DisconnectClient, this);
    dc_client.detach();
  }
}

void GameManager::StartGame() {
  std::thread start_attempt(&GameManager::TryStartGame, this);
  start_attempt.detach();
}

void GameManager::TryStartGame() {
  if (!opponent.GetName().empty() && game_state == LOBBY) {
    game_state = PLAYER_TURN;
    int start = ofGetElapsedTimeMillis();
    while (ofGetElapsedTimeMillis() - start < 500) {
      server.sendToAll(kStartGameMessage);
    }
  }
}

void GameManager::ConnectClient() {
  int connection_start_time = ofGetElapsedTimeMillis();
  ofxTCPSettings settings(port);
  while (!client.isConnected() &&
         ofGetElapsedTimeMillis() - connection_start_time <=
             kConnectionTimeOut) {
    if (game_state != CONNECTING) {
      return;
    }

    client.setup(settings);
    client.setMessageDelimiter(kMessageDelimiter);
  }

  if (client.isConnected()) {
    game_state = LOBBY;
    SyncSettingsClient();
    std::thread listen(&GameManager::ClientCommunicate, this);
    listen.detach();
  } else {
    game_state = CONNECTION_FAILED;
  }
}

void GameManager::SyncSettingsHost() {
  while (game_state == LOBBY) {
    for (int client_id = 0; client_id < server.getLastID(); client_id++) {
      if (server.isClientConnected(client_id) &&
          opponent.client_id != client_id) {
        server.send(client_id, std::to_string(move_time) + " " +
                                   std::to_string(rounds) + " " +
                                   player.GetName());
        std::string opponent_name = server.receive(client_id);
        while (opponent_name.empty()) {
          opponent_name = server.receive(client_id);
        }
        opponent = Player(opponent_name, false, client_id);
      } else if (!server.isClientConnected(client_id) &&
                 opponent.client_id == client_id) {
        opponent = Player();
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
    move_time = std::stof(game_info.substr(0, divider1_pos));
    game_info.erase(0, divider1_pos);
    int divider2_pos = game_info.find(" ") + 1;
    rounds = std::stoi(game_info.substr(0, divider2_pos));
    game_info.erase(0, divider2_pos);
    opponent = Player(game_info, true);
  }
}

void GameManager::DisconnectHost() {
  server.close();
  game_state = START;
  player = Player();
  opponent = Player();
}

void GameManager::DisconnectClient() {
  client.close();
  game_state = START;
  player = Player();
  opponent = Player();
}

void GameManager::ClientCommunicate() {
  while (client.isConnected()) {
    std::string receive = client.receive();
    if (receive == kStartGameMessage && game_state == LOBBY) {
      cout << receive << endl;
      game_state = OPPONENT_TURN;
      return;
    } /*else if (!receive.empty() && receive.front() == kBoardMessageHeader) {
      for (int i = 0; i < kBoardSize; i++) {
      
	  }
    }*/
  }
}
