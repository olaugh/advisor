#ifndef CARD_H
#define CARD_H

#include <set>
#include <string>

using std::string;

enum CardType {
  ACTION,
  ATTACK,
  CURSE_TYPE,
  REACTION,
  TREASURE,
  VICTORY,
};

enum CardName {
  CELLAR,
  CHAPEL,
  MOAT,
  HARBINGER,
  MERCHANT,
  VASSAL,
  VILLAGE,
  WORKSHOP,
  BUREAUCRAT,
  MILITIA,
  MONEYLENDER,
  POACHER,
  REMODEL,
  SMITHY,
  THRONE_ROOM,
  BANDIT,
  COUNCIL_ROOM,
  FESTIVAL,
  LABORATORY,
  LIBRARY,
  MARKET,
  MINE,
  SENTRY,
  WITCH,
  ARTISAN,
  
  CURSE,
  
  COPPER,
  SILVER,
  GOLD,
  
  ESTATE,
  DUCHY,
  PROVINCE,

  GARDENS,
};

class Card {
public:
  static Card* MakeCard(CardName card_name);
  static int NumInPile(CardName, int num_players);

  bool IsTreasure() const;
  int Cost() const;
  
  std::set<CardType> card_types;
  CardName card_name;
  string display_name;
  string display_plural;
  
  int base_cost;
  
  int action_plus_actions;
  int action_plus_buys;
  int action_plus_cards;
  int action_plus_coin;
  
  int treasure_plus_coin;
  
  int final_vp;
};

class Copper : public Card {
public:
  Copper();
};

class Silver : public Card {
public:
  Silver();
};

class Gold : public Card {
public:
  Gold();
};

class Estate : public Card {
public:
  Estate();
};

class Duchy : public Card {
public:
  Duchy();
};

class Province : public Card {
public:
  Province();
};

#endif
