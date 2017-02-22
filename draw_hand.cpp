#include <ctime>
#include <iostream>
#include <memory>
#include <random>

#include "card.h"
#include "card_set.h"
#include "deck.h"
#include "game.h"

using std::cout;
using std::endl;
using std::unique_ptr;

int main(int argc, char **argv) {
  cout << "Testing drawing a hand..." << endl;
  Game game;
  
  unique_ptr<CardSet> deck(new InitialBaseDeck);

  std::random_device rd;
  std::mt19937 g(rd());
  
  deck->Shuffle(g);

  CardSet hand;
  deck->Draw(5, &hand);

  vector<Card*> hand_cards;
  for (const CardName card_name : hand.cards) {
    hand_cards.push_back(Card::MakeCard(card_name));
  }

  for (const Card* card : hand_cards) {
    cout << card->display_name << endl;
  }
  return 0;
}
