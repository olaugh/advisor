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
  double best_action_value = -999;
  const Card* chosen_card = nullptr;
  for (const Card& card : player->cards_in_hand) {
    if (card.IsAction()) {
      const double value = ActionPlayValue(card, player, game);
      if (value > best_action_value) {
	cout << "play " << card.display_name << "? value: " << value << endl;
	chosen_card = &card;
	best_action_value = value;
      }
    }
  }
  if (chosen_card != nullptr) {
    cout << "chose " << chosen_card->display_name << endl;
  } else {
    cout << "chose not to play action" << endl;
  }
  return chosen_card;
}

double Strategy::ActionPlayValue(const Card& card,
				 const Player* player,
				 const Game* game) const {
  switch (card.card_name) {
  case SMITHY:
     if (player->actions > 1) return 0.5; else return 0.1;
  case VILLAGE:
    if (player->actions <= 1) return 1.0; else return 0.6;
  default:
    cout << "Unhandled card in ActionPlayValue!!" << endl;
    return -1.0;
  }
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
