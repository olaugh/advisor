#include <algorithm>
#include <random>

#include "card_set.h"

void CardSet::Shuffle(std::mt19937& g) {
  std::shuffle(cards.begin(), cards.end(), g);
}

void CardSet::Draw(int n, CardSet* dest) {
  for (int i = 0; i < n; ++i) {
    if (!cards.empty()) {
      dest->cards.push_back(cards.back());
      cards.pop_back();
    }
  }
}

bool CardSet::IsEmpty() const {
  return cards.empty();
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
