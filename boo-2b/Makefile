# Jason Booth   project 2b   boo-2b
# Makefile to make the executable for playing the game Flip
# -std=c++11 is used to allow for initializer lists
# -Wno-deprecated is used to remove the error message associated with the 
# d_except.h file using a deprecated library

# Make executable
Game: deck.h d_except.h card.o deck.o
	g++ -std=c++11 -Wno-deprecated main.cpp card.o deck.o -o Game 

# For deck class
deck.o: node.h deck.h card.h d_except.h d_random.h
	g++ -std=c++11 -Wno-deprecated -c deck.cpp -o deck.o

# For card class
card.o: card.h d_except.h
	g++ -std=c++11 -Wno-deprecated -c card.cpp -o card.o

clean: 
	rm *.o Game