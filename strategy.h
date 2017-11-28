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
    ChooseBuys(const Player* player, const Game* game) const;
  double ActionPlayValue(const Card& card,
			 const Player* player,
			 const Game* game) const;
};

#endif
