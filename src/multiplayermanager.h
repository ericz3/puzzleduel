#pragma once
#include "board.h"
#include "ofApp.h"
#include "ofxNetwork.h"
#include "player.h"

class MultiplayerManager {
 public:
  Player player1;
  Player player2;
  GameState game_state;
  ofxTCPServer server;
  ofxTCPClient client;
  int port;

  MultiplayerManager(PuzzleDuel game);

  void SetUpConnection();

 private:
  void SetupClient();
  void SetupHost();
  void TransferBoard();
  void TransferScore();
};