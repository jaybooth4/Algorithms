# Use "make" to create the Game object
# Compiled on a linux, Ubuntu 14.04 system
# -Wno-deprecated flag used to ignore warnings about 
# Deprecated libraries in exception header file
# If this is tested on a non-linux system these can be removed

Game: mastermind.o response.o code.o
	g++ -Wno-deprecated main.cpp mastermind.o response.o code.o -o Game

mastermind.o: mastermind.h response.h code.h mastermind.cpp
	g++ -Wno-deprecated -c mastermind.cpp -o mastermind.o

response.o: response.h code.h response.cpp
	g++ -c response.cpp -o response.o

code.o: code.h code.cpp
	g++ -c code.cpp -o code.o

clean:
	rm *.o Game 
