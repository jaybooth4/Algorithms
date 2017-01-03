# Jason Booth   project 2a   boo-2a
# Makefile to make the executable for printing the deck
# -std=c++11 is used to allow for initializer list
# -Wno-deprecated is used to remove the error message associated with the 
# d_except.h file using a deprecated library

# Make executable
printCards: deck.h card.o deck.o
	g++ -std=c++11 -Wno-deprecated main.cpp card.o deck.o -o printCards 

# For deck class
deck.o: node.h deck.h card.h node.h
	g++ -std=c++11 -Wno-deprecated -c deck.cpp -o deck.o

# For card class
card.o: card.h
	g++ -std=c++11 -Wno-deprecated -c card.cpp -o card.o

clean: 
	rm *.o printCards
