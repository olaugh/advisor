#ifndef PILE_H
#define PILE_H

#include <vector>

#include "card.h"
#include "card_set.h"

class Pile {
 public:
  Pile(CardName card, int n);
  bool IsEmpty() const;
  void ShowPile() const;
  CardName TopCardName() const;
  const Card* TopCard() const;
  void TakeCard(CardSet* dest);
  
  CardSet cards;
  CardName contents;
};

#endif
