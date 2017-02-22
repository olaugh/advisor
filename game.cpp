#include <iostream>
#include <vector>

#include "card.h"
#include "game.h"
#include "player.h"

using std::cout;
using std::endl;
using std::vector;

Game::Game(int num_players) {
  player_on_turn = 0;

  std::random_device rd;
  std::mt19937 g(rd());

  vector<CardName> kingdom;
  kingdom.push_back(COPPER);
  kingdom.push_back(SILVER);
  kingdom.push_back(GOLD);
  kingdom.push_back(ESTATE);
  kingdom.push_back(DUCHY);
  kingdom.push_back(PROVINCE);

  for (int i = 0; i < num_players; ++i) {
    cout << "i: " << i << endl;
    Player player;
    player.Shuffle(g);
    player.DrawToHand();

    players.push_back(player);
  }

  MakePiles(kingdom, num_players);
  ShowPiles();
}

void Game::PlayGame(const vector<const Strategy*>& strategies) {
  PlayTurn(strategies);
}

void Game::PlayTurn(const vector<const Strategy*>& strategies) {
  cout << "player_on_turn: " << player_on_turn << endl;
  Player* player = &(players[player_on_turn]);
  player->PlayTurn(this, strategies[player_on_turn]);
  if (IsOver()) {
    HandleGameOver();
  }
  ++player_on_turn;
  if (player_on_turn >= players.size()) {
    player_on_turn = 0;
  }
}

void Game::HandleGameOver() {
  cout << "Game over!" << endl;
}

bool Game::IsOver() {
  // true if Provinces empty or three piles empty
  const Pile* provinces = FindPile(PROVINCE);
  if (provinces != nullptr &&
      provinces->IsEmpty()) {
    return true;
  }
  if (NumEmptyPiles() >= 3) {
    return true;
  }
  return false;
}

const Pile* Game::FindPile(CardName card_name) const {
  for (const Pile& pile : piles) {
    if (pile.contents == card_name) {
      return &pile;
    }
  }
  return nullptr;
}

int Game::NumEmptyPiles() const {
  int num_empty_piles = 0;
  for (const Pile& pile : piles) {
    if (pile.IsEmpty()) {
      ++num_empty_piles;
    }
  }
  return num_empty_piles;
}

void Game::MakePiles(const vector<CardName>& kingdom, int num_players) {
  for (CardName card_name : kingdom) {
    int num_cards = Card::NumInPile(card_name, num_players);
    Pile pile(card_name, num_cards);
    piles.push_back(pile);
  }
}

void Game::ShowPiles() const {
  for (const Pile& pile : piles) {
    pile.ShowPile();
  }
}

vector<Card> Game::CardsAtopPiles() const {
  vector<Card> cards;
  for (const Pile& pile : piles) {
    const Card* card = pile.TopCard();
    if (card != nullptr) {
      cards.push_back(*card);
      delete(card);
    }
  }
  return cards;
}