// Jason Booth   Project 6a   boo-6a
// This project was created on a Linux Ubuntu 14.04 System, compiles, works
// This file reads a graph from the keyboard, and applies connected, 
// cyclic, and spanning tree algorithms

#include <iostream>
#include <boost/graph/adjacency_list.hpp>  // BGL library
#include "graphOperations.h"
#include "d_except.h"

void printConnectedCyclic(bool connected, bool cyclic) {
	if(connected)
		cout << "This graph is fully connected." << endl;
	else
		cout << "This graph is not fully connected." << endl;


	if(cyclic)
			cout << "This graph contains cycles." << endl << endl;
	else
		cout << "This graph does not contain cycles." << endl << endl;
}

int main() {

	// Create graph
	Graph g;

	cout << "Please enter file name" << endl;

	// Get file location
	string fileLocation;
	cin >> fileLocation;

	// Try catch initializing with opening the file
	try {
		initializeGraph(fileLocation, g);
	}
	catch (const fileOpenError& re) {
		cerr << re.what() << endl;  // Output file error message
	}

	cout << endl << "Original graph information:" << endl << endl;

	// Check connectivity and cyclic
	printConnectedCyclic(isConnected(g), isCyclic(g));

	cout << endl << "Spanning tree information:" << endl << endl;

	// Graph of spanning forest
	Graph sf;

	// Find spanning forest
	findSpanningForest(g, sf);

	// Check connectivity and cyclic
	printConnectedCyclic(isConnected(sf), isCyclic(sf));

	// Print graph information
	print(sf);

	return 0;

}

