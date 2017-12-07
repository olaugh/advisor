#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>

#include "card.h"
#include "game.h"
#include "player.h"

class Game;
class Player;

class Strategy {
 public:
  const Card* ChooseAction(const Player* player, const Game* game) const;
  std::vector<CardName>
    ChooseBuys(const Player* player, const Game* game, std::mt19937& g) const;
  const Card* BestBuyWith(const Player* player, const Game* game,
			  const vector<Card> cards, int coins,
			  std::mt19937& g) const;
  double BuyValue(const Card& card,
		  const Player* player,
		  const Game* game,
		  std::mt19937& g) const;
  double GainValue(const Card& card,
		   const Player* player,
		   const Game* game,
		   std::mt19937& g) const;
  double ActionPlayValue(const Card& card,
			 const Player* player,
			 const Game* game) const;
};

#endif
