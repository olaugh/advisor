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
  std::vector<CardName>
    ChooseBuys(const Player* player, const Game* game) const;
};

#endif
