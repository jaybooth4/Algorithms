// Jason Booth   Project 5c   boo-5c
// This project was created on a Linux Ubuntu 14.04 System, compiles, works
// This file reads a graph from the keyboard, and applies both shortest
// Path algorithms

#include <iostream>
#include <boost/graph/adjacency_list.hpp>  // BGL library
#include "graphProcedures.h"
#include "d_except.h"

int main() {

	// Create graph
	Graph g;

	// Starting and ending nodes
	Graph::vertex_descriptor start;
	Graph::vertex_descriptor end;

	// Get location
	string fileLocation;
	cin >> fileLocation;

	// Try catch initializing with opening the file
	try {
		initializeGraph(fileLocation, g, start, end);
	}
	catch (const fileOpenError& re) {
		cerr << re.what() << endl;  // Output file error message
	}

	cout << "DIJKSTRA ALGORITHM: " << endl << endl;

	// If each weight is positive, apply algorithm
	if(checkPositive(g)) {
		if(dijkstra(g, start)) {  // Path exists from start to each other node
			printPath(g, start, end);
		}
		// Not a path to each node
		else {
			cout << "A shortest path does not exist from the " << 
			"starting node to each node." << endl;
			printPath(g, start, end);  // Still print, if no path to end
			// This case is handled in printPath
		}
	}
	// Negative weights
	else {
		cout << "Negative weights found, Dijkstra could " <<
		"not be applied" << endl << endl;
	}

	cout << "BELLMAN FORD ALGORITHM: " << endl << endl;

	// If no negaitive cycles, print the path
	if(bellmanFord(g, start))
		printPath(g, start, end);
	else
		cout << "Negative cycles found." << endl << endl;

	return 0;

}
