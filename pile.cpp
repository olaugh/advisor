#include <iostream>
#include <memory>

#include "card.h"
#include "card_set.h"
#include "pile.h"

using std::cout;
using std::endl;

Pile::Pile(CardName card_name, int n) {
  for (int i = 0; i < n; ++i) {
    cards.AddCard(card_name);
  }
  contents = card_name;
}

bool Pile::IsEmpty() const {
  return cards.IsEmpty();
}

void Pile::ShowPile() const {
  std::unique_ptr<Card> card(Card::MakeCard(contents));
  
  cout << "x" << cards.Size() << " " << card->display_name << endl;
}

CardName Pile::TopCardName() const {
  return cards.cards.back();
}

const Card* Pile::TopCard() const {
  if (IsEmpty()) {
    return nullptr;
  }
  Card* card = Card::MakeCard(TopCardName());
  return card;
}
