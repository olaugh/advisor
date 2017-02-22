#include "card.h"

int Card::Cost() const {
  return base_cost;
}

bool Card::IsTreasure() const {
  for (CardType card_type : card_types) {
    if (card_type == TREASURE) {
      return true;
    }
  }
  return false;
}

Copper::Copper() {
  card_types.insert(TREASURE);

  card_name = COPPER;

  display_name = "Copper";
  display_plural = "Coppers";

  base_cost = 0;
  
  treasure_plus_coin = 1;
}

Silver::Silver() {
  card_types.insert(TREASURE);

  card_name = SILVER;

  display_name = "Silver";
  display_plural = "Silvers";

  base_cost = 3;
  
  treasure_plus_coin = 2;
}

Gold::Gold() {
  card_types.insert(TREASURE);

  card_name = GOLD;

  display_name = "Gold";
  display_plural = "Golds";

  base_cost = 6;
  
  treasure_plus_coin = 3;
}

Estate::Estate() {
  card_types.insert(VICTORY);

  card_name = ESTATE;

  display_name = "Estate";
  display_plural = "Estates";

  base_cost = 2;
  
  final_vp = 1;
}

Duchy::Duchy() {
  card_types.insert(VICTORY);

  card_name = DUCHY;

  display_name = "Duchy";
  display_plural = "Duchies";

  base_cost = 5;
  
  final_vp = 3;
}

Province::Province() {
  card_types.insert(VICTORY);

  card_name = PROVINCE;

  display_name = "Province";
  display_plural = "Provinces";

  base_cost = 8;
  
  final_vp = 6;
}

Card* Card::MakeCard(CardName card_name) {
  switch (card_name) {
  case COPPER: return new Copper;
  case SILVER: return new Silver;
  case GOLD: return new Gold;
  case ESTATE: return new Estate;
  case DUCHY: return new Duchy;
  case PROVINCE: return new Province;
  default: return nullptr;
  }
  return nullptr;
}

int Card::NumInPile(CardName card_name, int num_players) {
  switch (card_name) {
  case COPPER: return 46;
  case SILVER: return 40;
  case GOLD:   return 30;
  default:     return  8;
  }
}
