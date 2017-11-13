#include <iostream>
#include <vector>

#include "card.h"
#include "game.h"
#include "player.h"

using std::cout;
using std::endl;
using std::vector;

namespace {
  const Card* MostExpensiveBuyWith(const Player* player,
				   const Game* game,
				   const vector<Card> cards,
				   int coins) {
    const Card* most_expensive_card = nullptr;
    int most_expensive_cost = -1;
    for (const Card& card : cards) {
      int cost = card.Cost();
      if (cost > most_expensive_cost &&
	  player->CanBuyWith(card, coins, game)) {
	most_expensive_cost = cost;
	most_expensive_card = &card;
      }
    }
    return most_expensive_card;
  }
}  // namespace

const Card* Strategy::ChooseAction(const Player* player,
				   const Game* game) const {
  for (const Card& card : player->cards_in_hand) {
    if (card.IsAction()) {
      return &card;
    }
  }
  return nullptr;
}

vector<CardName> Strategy::ChooseBuys(const Player* player,
				      const Game* game) const {
  // Default dumbest strategy, always buys most expensive card it can,
  // if it costs at least 2 coins.

  vector<CardName> buys;
  if (player->buys == 0) return buys;

  int coins = player->coins;

  cout << "Player has " << coins << " coins." << endl;
  const vector<Card> cards = game->CardsAtopPiles();
  for (const Card& card : cards) {
    cout << "Card: " << card.display_name << ", cost: "
	 << card.Cost() << endl;
  }
  
  for (int i = 0; i < player->buys; ++i) {
    const Card* card = MostExpensiveBuyWith(player, game, cards, coins);
    if (card == nullptr) {
      break;
    }
    if (card->Cost() < 2) {
      // Don't buy
      break;
    }
    buys.push_back(card->card_name);
    coins -= card->Cost();
  }

  return buys;
}
