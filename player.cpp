#include <iostream>

#include "deck.h"
#include "game.h"
#include "player.h"
#include "strategy.h"

using std::cout;
using std::endl;

Player::Player() {
  InitialBaseDeck base_deck;
  deck = base_deck;
}

void Player::Shuffle(std::mt19937& g) {
  deck.Shuffle(g);
}

void Player::DrawToHand() {
  deck.Draw(5, &hand);

  vector<Card*> hand_cards;
  for (const CardName card_name : hand.cards) {
    hand_cards.push_back(Card::MakeCard(card_name));
  }

  for (const Card* card : hand_cards) {
    cout << card->display_name << endl;
  }
}

void Player::PlayTurn(Game* game, const Strategy* strategy) {
  cout << "Playing turn..." << endl;
  InitializeTurn(game);
  InflateCardsInHand();
  ActionPhase(game, strategy);
  BuyPhase(game, strategy);
  CleanUp(game, strategy);
}

void Player::InitializeTurn(Game* game) {
  actions = 1;
  coins = 0;
  buys = 1;
}

void Player::ActionPhase(Game* game, const Strategy* strategy) {
  
}

void Player::BuyPhase(Game* game, const Strategy* strategy) {
  PlayAllTreasures(game);
  ShowHand();
  ShowInPlay();
  vector<CardName> buys = strategy->ChooseBuys(this, game);
}

void Player::CleanUp(Game* game, const Strategy* strategy) {

}

void Player::InflateCardsInHand() {
  for (CardName card_name : hand.cards) {
    Card* card = Card::MakeCard(card_name);
    cards_in_hand.push_back(*card);
  }
}

void Player::PlayAllTreasures(Game* game) {
  while (PlayTreasure(game)); 
}

bool Player::PlayTreasure(Game* game) {
  for (int i = 0; i < cards_in_hand.size(); ++i) {
    const Card& card = cards_in_hand[i];
    if (card.IsTreasure()) {
      PlayCardAsTreasure(i, game);
      return true;
    }
  }
  return false;
}

void Player::PlayCardAsTreasure(int i, Game* game) {
  const Card& card = cards_in_hand[i];
  coins += card.treasure_plus_coin;
  cards_in_play.push_back(card);
  cards_in_hand.erase(cards_in_hand.begin() + i);
}

bool Player::CanBuyWith(const Card& card, int coins, const Game* game) const {
  const int cost = card.Cost();
  return coins >= cost;
}

void Player::ShowHand() const {
  cout << "Hand..." << endl;
  for (const Card& card : cards_in_hand) {
    cout << "  " << card.display_name << endl;
  }
}

void Player::ShowInPlay() const {
  cout << "In play..." << endl;
  for (const Card& card : cards_in_play) {
    cout << "  " << card.display_name << endl;
  }
}
