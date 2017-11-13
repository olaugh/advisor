#include <algorithm>
#include <iostream>
#include <random>

#include "card_set.h"

using std::cout;
using std::endl;

void CardSet::Shuffle(std::mt19937& g) {
  std::shuffle(cards.begin(), cards.end(), g);
}

void CardSet::Draw(int n, CardSet* dest) {
  for (int i = 0; i < n; ++i) {
    if (!cards.empty()) {
      const CardName& card_name = cards.back();
      std::unique_ptr<Card> card(Card::MakeCard(card_name));
      cout << "Drew a " << card->display_name << endl;
      dest->cards.push_back(cards.back());
      cards.pop_back();
    }
  }
}

bool CardSet::IsEmpty() const {
  return cards.empty();
}

void CardSet::RemoveAt(int i) {
  cards.erase(cards.begin() + i);
}

void CardSet::Clear() {
  cards.clear();
}

void CardSet::AddCard(CardName card) {
  cards.push_back(card);
}

int CardSet::Size() const {
  return cards.size();
}
