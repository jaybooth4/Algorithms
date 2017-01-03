# Jason Booth   Project 4a   boo-4a

# -Wno-deprecated is used to remove the error message associated with the
# d_except.h file using a deprecated library
# -I flags used to include the dircectory containing headers

# Make executable
executable: board.o
	g++ -std=c++11 -Wno-deprecated -Iinc/ src/main.cpp board.o -o executable 

# Compile board file
board.o: inc/board.h
	g++ -std=c++11 -Wno-deprecated -c -Iinc/ src/board.cpp -o board.o

# Clean
clean: 
	rm *.o executable
