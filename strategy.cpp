#include <iostream>
#include <vector>

#include "card.h"
#include "game.h"
#include "player.h"

using std::cout;
using std::endl;
using std::vector;

const Strategy* Strategy::DeeperClone() const {
  Strategy* strategy = new Strategy;
  strategy->depth = depth + 1;
  return strategy;
}

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

double Strategy::BuyValue(const Card& card,
			  const Player* player,
			  const Game* game,
			  std::mt19937& g) const {
  return GainValue(card, player, game, g);
}

double Strategy::GainValue(const Card& card,
			   const Player* player,
			   const Game* game,
			   std::mt19937& g) const {
  const double hacky_estimate = 0.25 * pow(card.base_cost, 1.5) - 1;
  std::normal_distribution<> dist{0, 0.4};
  const double noise = dist(g);
  return hacky_estimate + noise;
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

const Card* Strategy::BestBuyWith(const Player* player,
				  const Game* game,
				  const vector<Card> cards,
				  int coins,
				  std::mt19937& g) const {
  const Card* best_to_buy = nullptr;
  double best_value = 0.0;
  for (const Card& card : cards) {
    if (player->CanBuyWith(card, coins, game)) {
      double value = BuyValue(card, player, game, g);
      cout << "buy " << card.display_name << "? value: " << value << endl;
      if (value > best_value) {
	best_value = value;
	best_to_buy = &card;
      }
    }
  }
  return best_to_buy;
}

void Strategy::SimAllBuys(const Player* player,
			  const Game* game,
			  std::mt19937& g) const {
  const vector<Card> cards = game->CardsAtopPiles();
  std::unique_ptr<const Strategy> sim_strategy(DeeperClone());
  std::uniform_int_distribution<> dist(0, 1 << 24);  
  long seed = dist(g);
  for (const Card& card : cards) {
    if (player->CanBuyWith(card, player->coins, game)) {
      cout << "sim buying " << card.display_name << endl;
      for (int i = 0; i < 8; ++i) {
	std::cout << "sim iteration: " << i << std::endl;
	std::mt19937 sim_g(seed << 32 | i);
	Game game_copy = *game;
	Player player_copy = *player;
	player_copy.BuyCleanUpAndDraw(&game_copy, sim_strategy.get(),
				      {card}, sim_g);
	game_copy.FinishTurn({sim_strategy.get(), sim_strategy.get()}, sim_g);
	// This is wrong because it assumes perfect information of the opponent's
	// current hand, our deck, and their deck and discard piles. No varation
        // will occur until shuffles. Instead, all unknowns should be randomized.
	game_copy.FinishGame({sim_strategy.get(), sim_strategy.get()}, sim_g);
      }
    }
  }
}

vector<CardName> Strategy::ChooseBuys(const Player* player,
				      const Game* game,
				      std::mt19937& g) const {
  // Default dumbest strategy, always greedily buys best card it can according
  // to BuyValue, if it has positive value.
  vector<CardName> buys;
  if (player->buys == 0) return buys;

  int coins = player->coins;

  cout << "Player has " << coins << " coins." << endl;
  const vector<Card> cards = game->CardsAtopPiles();
  for (const Card& card : cards) {
    cout << "Card: " << card.display_name << ", cost: "
	 << card.Cost() << endl;
  }

  if (depth == 0) {
    SimAllBuys(player, game, g);
  }
  
  // What happens if you buy the last card in a pile?
  // Obviously this can't handle multiple buys correctly yet.
  // What if there are on-buy or on-gain effects that change the values?
  for (int i = 0; i < player->buys; ++i) {
    const Card* card = BestBuyWith(player, game, cards, coins, g);
    if (card == nullptr) {
      break;
    }
    buys.push_back(card->card_name);
    coins -= card->Cost();
  }

  return buys;
}
