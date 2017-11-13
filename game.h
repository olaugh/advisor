#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "card.h"
#include "card_set.h"
#include "pile.h"
#include "player.h"

class Game {
 public:
  Game(int num_players);
  void PlayGame(const vector<const Strategy*>& strategies);
  void PlayGame(const vector<const Strategy*>& strategies, std::mt19937& g);
  bool PlayTurn(const vector<const Strategy*>& strategies, std::mt19937& g);
  bool IsOver();
  void MakePiles(const std::vector<CardName>& kingdom, int num_players);
  void ShowPiles() const;
  Pile* FindPile(CardName card_name);
  int NumEmptyPiles() const;
  void HandleGameOver();
  std::vector<Card> CardsAtopPiles() const;
  
  std::vector<Player> players;
  int turn_number;
  int player_on_turn;
  std::vector<Pile> piles;
  CardSet trash;
};

#endif
