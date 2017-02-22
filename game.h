#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "player.h"
#include "pile.h"
#include "card.h"
#include "card_set.h"

class Game {
 public:
  Game(int num_players);
  void PlayGame(const vector<const Strategy*>& strategies);
  void PlayTurn(const vector<const Strategy*>& strategies);
  bool IsOver();
  void MakePiles(const std::vector<CardName>& kingdom, int num_players);
  void ShowPiles() const;
  const Pile* FindPile(CardName card_name) const;
  int NumEmptyPiles() const;
  void HandleGameOver();
  std::vector<Card> CardsAtopPiles() const;
  
  std::vector<Player> players;
  int player_on_turn;
  std::vector<Pile> piles;
  CardSet trash;
};

#endif
