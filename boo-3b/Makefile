# Jason Booth   project 3b   boo-3b
# This file is a Makefile to make the executable for the word search
# -std=c++11 is used to allow for initializer lists
# -Wno-deprecated is used to remove the error message associated with the 
# -I flags used to include the dircectory containing headers
# d_except.h file using a deprecated library

# Make executable
executable: wordList.o
	g++ -std=c++11 -Wno-deprecated -Iinc/ src/main.cpp wordList.o -o executable 

# Compile wordList file
wordList.o: inc/wordList.h
	g++ -std=c++11 -Wno-deprecated -c -Iinc/ src/wordList.cpp -o wordList.o

# Clean
clean: 
	rm *.o executable
