CXX = g++
CXXFLAGS = -Wall -g -std=c++11

test_game: test_game.o card.o game.o player.o deck.o card_set.o pile.o
	$(CXX) $(CXXFLAGS) -o test_game test_game.o game.o player.o \
		                        deck.o card.o card_set.o \
	                                pile.o strategy.o
test_game.o: test_game.cpp
	$(CXX) $(CXXFLAGS) -c test_game.cpp
draw_hand: draw_hand.o card.o game.o player.o deck.o card_set.o
	$(CXX) $(CXXFLAGS) -o draw_hand draw_hand.o game.o player.o \
		                        deck.o card.o card_set.o
draw_hand.o: draw_hand.cpp
	$(CXX) $(CXXFLAGS) -c draw_hand.cpp
strategy.o: strategy.cpp
	$(CXX) $(CXXFLAGS) -c strategy.cpp
pile.o: pile.cpp pile.h card_set.o card.o
	$(CXX) $(CXXFLAGS) -c pile.cpp
game.o: game.cpp game.h player.o strategy.o
	$(CXX) $(CXXFLAGS) -c game.cpp
player.o: player.cpp player.h deck.o card_set.o strategy.o
	$(CXX) $(CXXFLAGS) -c player.cpp
deck.o: deck.cpp deck.h card_set.o
	$(CXX) $(CXXFLAGS) -c deck.cpp
card_set.o: card_set.cpp card_set.h card.o
	$(CXX) $(CXXFLAGS) -c card_set.cpp
card.o: card.cpp card.h
	$(CXX) $(CXXFLAGS) -c card.cpp
