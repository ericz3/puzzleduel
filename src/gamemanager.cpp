#include "gamemanager.h"
#include <string>
#include <thread>

unsigned const int kMaxPort = 65535;
const string kMsgDelimiter = "\n";
const string kMsgValueDivider = " ";
unsigned const int kConnectionTimeOut = 30000;
unsigned const int kConnectTimeInterval = 3000;
const string kBoardMsgHeader = "Board";
const string kClientStartConfirmation = "Started";

GameManager::GameManager() {
  game_state = START;
  player = Player();
  opponent = Player();
  cursor_orb = Orb::EMPTY;
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
  server.setMessageDelimiter(kMsgDelimiter);
  game_state = LOBBY;
  std::thread send_game_info(&GameManager::SyncSettingsHost, this);
  send_game_info.detach();
}

void GameManager::SendBoard() {
  if (player.IsHost()) {
    HostSendBoard();
  } else {
    ClientSendBoard();
  }
}

void GameManager::SendEndTurn() {
  if (player.IsHost()) {
    server.send(opponent.client_id, kEndTurn);
  } else {
    client.send(kEndTurn);
  }
}

std::string GameManager::ReceiveBoard() {
  if (player.IsHost()) {
    return HostReceiveBoard();
  } else {
    return ClientReceiveBoard();
  }
}

void GameManager::ClientSendBoard() {
  if (client.isConnected()) {
    std::string board_msg;
    board_msg.reserve(kBoardSize + kBoardMsgHeader.length() + 1);
    board_msg.append(kBoardMsgHeader)
        .append(board.AsString())
        .append(std::to_string((int)cursor_orb));
    client.send(board_msg);
    cout << "Send:   " << board_msg << endl;
  }
}

void GameManager::HostSendBoard() {
  if (!opponent.GetName().empty()) {
    std::string board_msg;
    board_msg.reserve(kBoardSize + kBoardMsgHeader.length() + 1);
    board_msg.append(kBoardMsgHeader)
        .append(board.AsString())
        .append(std::to_string((int)cursor_orb));
    server.send(opponent.client_id, board_msg);
    cout << "Send:   " << board_msg << endl;
  }
}

std::string GameManager::ClientReceiveBoard() {
  if (client.isConnected()) {
    std::string receive = client.receive();
    // cout << "receive:   " << receive << endl;
    if (!receive.empty() && receive.length() > kBoardSize) {
      std::string board_msg = receive.substr(kBoardMsgHeader.length());
      return board_msg;
    } else if (!receive.empty() && receive == kEndTurn) {
      return receive;
    } else {
      return "";
    }
  }

  return "";
}

std::string GameManager::HostReceiveBoard() {
  std::string receive = server.receive(opponent.client_id);
  if (!receive.empty() && receive.length() > kBoardSize) {
    std::string board_msg = receive.substr(kBoardMsgHeader.length());
    cout << "1" << endl;
    return board_msg;
  } else if (!receive.empty() && receive == kEndTurn) {
    cout << "2" << endl;
    return receive;
  } else {
    cout << "3" << endl;
    return "";
  }
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
    while (true) {
      server.sendToAll(kStartGameMsg);
      if (server.receive(opponent.client_id) == kClientStartConfirmation) {
        return;
      }
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
    client.setMessageDelimiter(kMsgDelimiter);
  }

  if (client.isConnected()) {
    game_state = LOBBY;
    SyncSettingsClient();
    std::thread client_start(&GameManager::ClientListenStart, this);
    client_start.detach();
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

void GameManager::ClientListenStart() {
  while (client.isConnected()) {
    std::string receive = client.receive();
    if (receive == kStartGameMsg && game_state == LOBBY) {
      game_state = OPPONENT_TURN;
      client.send(kClientStartConfirmation);
      return;
    }
  }
}
