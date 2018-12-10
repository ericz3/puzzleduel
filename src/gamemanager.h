#pragma once

#include <vector>
#include "board.h"
#include "ofxNetwork.h"
#include "player.h"

enum GameState {
  START,
  CREATE_GAME,
  JOIN_GAME,
  CONNECTING,
  CONNECTION_FAILED,
  LOBBY,
  PLAYER_TURN,
  PLAYER_MOVE,
  PLAYER_COUNT_POINTS,
  PLAYER_ERASE_MATCHES,
  OPPONENT_TURN,
  OPPONENT_COUNT_POINTS,
  OPPONENT_ERASE_MATCHES,
  GAME_OVER
};

class GameManager {
 public:
  Player player;
  Player opponent;
  GameState game_state;
  ofxTCPServer server;
  ofxTCPClient client;
  int port;
  float move_time;
  int rounds;

  GameManager();
  void SetupClient(std::string player_name, int port);
  void SetupServer(std::string player_name, float move_time, int rounds);
  void SendBoard();
  Board ReceiveBoard();
  void SendScore();
  int RecieveScore();
  void DisconnectLobby();

 private:
  void ConnectClient();
  void SyncSettingsHost();
  void SyncSettingsClient();
};