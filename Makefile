CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -O3
LIBRARY_PATH=/usr/local/Cellar/protobuf/2.6.1/lib:$LIBRA‌​RY_PATH
DYLDLIBS = -L/usr/local/Cellar/protobuf/2.6.1/lib -llibprotobuf:$DYLDLIBS

PROTOS         := $(wildcard *.proto)
PROTO_OBJS     := $(PROTOS:.proto=.pb.o)

protoc_middleman: dominion.proto
	protoc --cpp_out=. dominion.proto
	@touch protoc_middleman

test_game: test_game.o card.o game.o player.o deck.o card_set.o pile.o \
           protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -o test_game test_game.o game.o player.o \
		                        deck.o card.o card_set.o \
	                                pile.o strategy.o
test_game.o: test_game.cpp card.o game.o player.o deck.o card_set.o pile.o \
	     protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c test_game.cpp
draw_hand: draw_hand.o card.o game.o player.o deck.o card_set.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -o draw_hand draw_hand.o game.o player.o \
					deck.o card.o card_set.o
draw_hand.o: draw_hand.cpp protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c draw_hand.cpp
strategy.o: strategy.cpp strategy.h card.o game.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c strategy.cpp
pile.o: pile.cpp pile.h card_set.o card.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c pile.cpp
game.o: game.cpp game.h protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c game.cpp
player.o: player.cpp player.h deck.o card_set.o strategy.o game.o
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c player.cpp
deck.o: deck.cpp deck.h card_set.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c deck.cpp
card_set.o: card_set.cpp card_set.h card.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c card_set.cpp
card.o: card.cpp card.h protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	$(CXX) $(CXXFLAGS) -c card.cpp
