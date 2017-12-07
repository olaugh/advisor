#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "card_set.h"
#include "game.h"
#include "strategy.h"

class Game;

class Player {
 public:
  Player();
  void Shuffle(std::mt19937& g);
  void DrawToHand(std::mt19937& g);
  void DrawFromDeck(int n, CardSet* dest, std::mt19937& g);
  void PutDiscardPileInDeckAndShuffle(std::mt19937& g);
  
  void PlayTurn(Game* game, const Strategy* strategy, std::mt19937& g);
  
  void ActionPhase(Game* game, const Strategy* strategy, std::mt19937& g);
  bool PlayAction(Game* game, const Strategy* strategy,
		  std::mt19937& g);
  void PlayAction(Game* game, const Strategy* strategy, const Card* card,
		  std::mt19937& g);
  int FindCardIndexInHand(CardName card_name) const;
  
  void BuyPhase(Game* game, const Strategy* strategy, std::mt19937& g);
  void PlayAllTreasures(Game* game);
  bool PlayTreasure(Game* game);
  void PlayCardAsTreasure(int i, Game* game);
  void BuyCard(Game* game, const Strategy* strategy, CardName);
  bool CanBuyWith(const Card& card, int coins, const Game* game) const;

  
  void CleanUp(Game* game, const Strategy* strategy);
  void CleanUpCardFromPlay(Game* game, const Strategy* strategy, int i);
  bool ShouldDiscardFromPlay(Game* game, const Strategy* strategy,
			     const Card& card);
  void CleanUpCardFromHand(Game* game, const Strategy* strategy, int i);
  bool ShouldDiscardFromHand(Game* game, const Strategy* strategy,
			     const Card& card);
  
  void InitializeTurn(Game* game);
  void InflateCardsInHand();
  void ReinflateCardsInHand();
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
