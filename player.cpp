#include <cassert>
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
  cout << "Shuffle(...)" << endl;
  deck.Shuffle(g);
}

void Player::DrawToHand(std::mt19937& g) {
  DrawFromDeck(5, &hand, g);
}

void Player::DrawFromDeck(int n, CardSet* dest, std::mt19937& g) {
  cout << "DrawFromDeck(" << n << ", ...)" << endl;
  for (int i = 0; i < n; ++i) {
    if (deck.IsEmpty()) {
      cout << "deck is empty" << endl;
      if (discard_pile.IsEmpty()) {
	cout << "discard pile is empty too" << endl;
	return;
      }
      PutDiscardPileInDeckAndShuffle(g);
    }
    deck.Draw(1, dest);
  }
}

void Player::PutDiscardPileInDeckAndShuffle(std::mt19937& g) {
  cout << "PutDiscardPileInDeckAndShuffle(...)" << endl;
  for (CardName card_name : discard_pile.cards) {
    deck.AddCard(card_name);
  }
  discard_pile.Clear();
  Shuffle(g);
}

void Player::PlayTurn(Game* game, const Strategy* strategy, std::mt19937& g) {
  cout << "Playing turn..." << endl;
  InitializeTurn(game);
  InflateCardsInHand();
  ActionPhase(game, strategy, g);
  BuyPhase(game, strategy, g);
  CleanUp(game, strategy);
  DrawToHand(g);
}

void Player::BuyCleanUpAndDraw(Game* game, const Strategy* strategy,
			       const vector<Card>& cards_to_buy,
			       std::mt19937& g) {
  std::cout << "BuyCleanUpAndDraw(...)" << endl;;
  // Treasures have already been played.
  //PlayAllTreasures(game);
  ShowHand();
  ShowInPlay();
  for (const Card& card : cards_to_buy) {
    BuyCard(game, strategy, card.card_name);
  }
  CleanUp(game, strategy);
  DrawToHand(g);
}

// Eventually needs to handle overpayment.
void Player::BuyCard(Game* game, const Strategy* strategy,
		     CardName card_name) {
  std::unique_ptr<Card> card(Card::MakeCard(card_name));
  cout << "Buying a " << card->display_name << endl;
    
  Pile* pile = game->FindPile(card_name);
  assert(pile != nullptr);
  pile->TakeCard(&discard_pile);
}

void Player::InitializeTurn(Game* game) {
  actions = 1;
  coins = 0;
  buys = 1;
  cards_in_hand.clear();
  cards_in_play.clear();
}

void Player::ActionPhase(Game* game, const Strategy* strategy, std::mt19937& g) {
  cout << "ActionPhase(...)" << endl;
  ShowHand();
  while(PlayAction(game, strategy, g));
}

bool Player::PlayAction(Game* game, const Strategy* strategy, std::mt19937& g) {
  cout << "Actions: " << actions << endl;;
  if (actions == 0) return false;
  const Card* card = strategy->ChooseAction(this, game);
  if (card != nullptr) {
    PlayAction(game, strategy, card, g);
    actions--;
    return true;
  }
  return false;
}

void Player::PlayAction(Game* game, const Strategy* strategy,
			const Card* card, std::mt19937& g) {
  const int i = FindCardIndexInHand(card->card_name);
  assert(i >= 0);
  cards_in_play.push_back(cards_in_hand[i]);
  hand.RemoveAt(i);
  cout << "Playing a " << card->display_name << endl;
  if (card->action_plus_actions > 0) {
    cout << "Plus " << card->action_plus_actions << " actions" << endl;
    actions += card->action_plus_actions;
  }
  if (card->action_plus_cards > 0) {
    cout << "Drawing " << card->action_plus_cards << " cards" << endl;
    for (int j = 0; j < card->action_plus_cards; ++j) {
      DrawFromDeck(1, &hand, g);
    }
  }
  ReinflateCardsInHand();
}

int Player::FindCardIndexInHand(CardName card_name) const {
  for (int i = 0; i < cards_in_hand.size(); ++i) {
    const Card& card = cards_in_hand[i];
    if (card.card_name == card_name) {
      return i;
    }
  }
  return -1;
}

void Player::BuyPhase(Game* game, const Strategy* strategy, std::mt19937& g) {
  cout << "BuyPhase(...)" << endl;
  PlayAllTreasures(game);
  ShowHand();
  ShowInPlay();
  vector<CardName> buys = strategy->ChooseBuys(this, game, g);
  for (CardName card_name : buys) {
    BuyCard(game, strategy, card_name);
  }
}

void Player::CleanUp(Game* game, const Strategy* strategy) {
  cout << "CleanUp(...)" << endl;
  for (int i = cards_in_play.size() - 1; i >= 0; --i) {
    CleanUpCardFromPlay(game, strategy, i);
  }
  for (int i = cards_in_hand.size() - 1; i >= 0; --i) {
    CleanUpCardFromHand(game, strategy, i);
  }
  hand.Clear();
}

void Player::CleanUpCardFromPlay(Game* game, const Strategy* strategy, int i) {
  const Card& card = cards_in_play[i];
  if (ShouldDiscardFromPlay(game, strategy, card)) {
    discard_pile.AddCard(card.card_name);
  }
  cards_in_play.erase(cards_in_play.begin() + i);
}

bool Player::ShouldDiscardFromPlay(Game* game, const Strategy* strategy,
				   const Card& card) {
  return true;
}

void Player::CleanUpCardFromHand(Game* game, const Strategy* strategy, int i) {
  const Card& card = cards_in_hand[i];
  if (ShouldDiscardFromHand(game, strategy, card)) {
    discard_pile.AddCard(card.card_name);
  }
  cards_in_hand.erase(cards_in_hand.begin() + i);
}

bool Player::ShouldDiscardFromHand(Game* game, const Strategy* strategy,
				   const Card& card) {
  return true;
}

void Player::InflateCardsInHand() {
  for (CardName card_name : hand.cards) {
    Card* card = Card::MakeCard(card_name);
    cards_in_hand.push_back(*card);
  }
}

void Player::ReinflateCardsInHand() {
  cards_in_hand.clear();
  InflateCardsInHand();
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
