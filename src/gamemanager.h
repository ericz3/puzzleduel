#pragma once

#include <string>
#include <vector>
#include "board.h"
#include "ofxNetwork.h"
#include "player.h"

const string kStartGameMessage = "start";

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
  Board board;
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
  void SetupServer(std::string player_name);
  void SendBoard();
  Board ReceiveBoard();
  void SendScore();
  int RecieveScore();
  void DisconnectLobby();
  void StartGame();

 private:
  void TryStartGame();
  void ConnectClient();
  void SyncSettingsHost();
  void SyncSettingsClient();
  void DisconnectHost();
  void DisconnectClient();
  void HostCommunicate();
  void ClientCommunicate();
};