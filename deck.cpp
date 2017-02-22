#include "deck.h"

InitialBaseDeck::InitialBaseDeck() {
  for (int i = 0; i < 7; ++i) {
    cards.push_back(COPPER);
  }
  for (int i = 0; i < 3; ++i) {
    cards.push_back(ESTATE);
  }
}
