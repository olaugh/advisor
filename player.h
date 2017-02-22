#ifndef PLAYER_H
#define PLAYER_H

#include "card_set.h"
#include "game.h"
#include "strategy.h"

class Game;

class Player {
 public:
  Player();
  void Shuffle(std::mt19937& g);
  void DrawToHand();
  
  void PlayTurn(Game* game, const Strategy* strategy);
  void ActionPhase(Game* game, const Strategy* strategy);
  void BuyPhase(Game* game, const Strategy* strategy);
  void CleanUp(Game* game, const Strategy* strategy);

  void InitializeTurn(Game* game);
  void InflateCardsInHand();
  void PlayAllTreasures(Game* game);
  bool PlayTreasure(Game* game);

  void PlayCardAsTreasure(int i, Game* game);
  
  bool CanBuyWith(const Card& card, int coins, const Game* game) const;

  void ShowHand() const;
  void ShowInPlay() const;
  
  CardSet deck;
  CardSet hand;
  CardSet discard_pile;

  std::vector<Card> cards_in_hand;
  std::vector<Card> cards_in_play;
  
  int actions;
  int buys;
  int coins;
};

#endif
