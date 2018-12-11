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
  PLAYER_ERASE_MATCHES,
  PLAYER_ADD_POINTS,
  OPPONENT_TURN,
  OPPONENT_ERASE_MATCHES,
  OPPONENT_ADD_POINTS,
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
  int round_points;

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