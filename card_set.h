#ifndef CARD_SET_H
#define CARD_SET_H

#include <random>
#include <vector>

#include "card.h"

using std::vector;

class CardSet {
 public:
  void Shuffle(std::mt19937& g);
  void Draw(int n, CardSet* dest);
  bool IsEmpty() const;
  void RemoveAt(int i);
  void Clear();
  void AddCard(CardName card);
  int Size() const;
  
  vector<CardName> cards;
};

#endif
