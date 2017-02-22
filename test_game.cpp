#include <iostream>
#include "game.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
  cout << "Testing playing a game..." << endl;
  Game game(2);
  
  vector<const Strategy*> strategies;
  Strategy default_strategy;
  strategies.push_back(&default_strategy);
  strategies.push_back(&default_strategy);
  
  game.PlayGame(strategies);
  cout << "Finished!" << endl;
}
