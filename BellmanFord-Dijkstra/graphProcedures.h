// Jason Booth   Project 5c   boo-5c
// This file implements the graph procedures including the 
// Bellman Ford and the dijkstra algorithms

#include <iostream>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>  // BGL library
#include "heap.h"

using namespace std;
using namespace boost;

#define LargeValue 99999999  // Used as several default values

struct VertexProperties;  // Defines data stored in each vertex
struct EdgeProperties;  // Defines data stored in each edge

typedef adjacency_list<vecS, vecS,
                       bidirectionalS, VertexProperties, EdgeProperties> Graph;

// Create a struct to hold properties for each vertex
struct VertexProperties
{
   pair<int,int> cell; // maze cell (x,y) value
   Graph::vertex_descriptor pred; // predecessor node
   int weight;
   bool visited;
   bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   int weight;
   bool visited;
   bool marked;
};

typedef adjacency_list<vecS, vecS,
                       bidirectionalS, VertexProperties, EdgeProperties> Graph;

// Initialize g using data.  Set start and end nodes.
void initializeGraph(string fileLocation, Graph &g, 
					Graph::vertex_descriptor &start,
		     		Graph::vertex_descriptor &end)
{

	ifstream fin;  // Input file stream
	fin.open(fileLocation.c_str());  // Attempt to open

	// Error handling, if file cannot be opened throw error
	if (!fin) {
		throw fileOpenError(fileLocation);  // Name of file
	}

   EdgeProperties e;  // Used to read in the weight of each edge

   int n, i, j;  // Number of nodes, nodes that make up the edge
   int startId, endId;
   fin >> n;
   fin >> startId >> endId;
   Graph::vertex_descriptor v;

   // Set start and end nodes
   for (int i = 0; i < n; i++)
   {
      v = add_vertex(g);
      if (i == startId)
	 start = v;
      if (i == endId)
	 end = v;
   }

   // Add nodes
   while (fin.peek() != '.')
   {
      fin >> i >> j >> e.weight;
      add_edge(i,j,e,g);
   }

   // Close file
   fin.close();

}

// Set all node weights to w
void setNodeWeights(Graph &g, int w) {

    // Iterate through each vertex and set each weight property to w
        pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
      vertices(g);
        for (Graph::vertex_iterator vItr = vItrRange.first;
       vItr != vItrRange.second; ++vItr)
                g[*vItr].weight = w;  // Set each weight
        g[*vItrRange.second].weight = w;  // Set last weight

}

// Set each predecessor to a default value
void clearPred(Graph &g) {

    // Iterate through each vertex and set pred to LargeValue
        pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
      vertices(g);
        for (Graph::vertex_iterator vItr = vItrRange.first;
      vItr != vItrRange.second; ++vItr)
                g[*vItr].pred = LargeValue;  // Set to LargeValue
        g[*vItrRange.second].pred = LargeValue;  // Set last

}

// Check to see if any edge has a negative weight
bool checkPositive(Graph &g) {

	// Iterate over edges
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange =
		      edges(g);
	for (Graph::edge_iterator eItr = eItrRange.first;
		 eItr != eItrRange.second; ++eItr) {
			if(g[*eItr].weight < 0)
				return false;  // Negative value
	}
	if(g[*eItrRange.second].weight < 0)
		return false;
	return true;  // All positive

}

// Clears all predecessors and sets node weights to LargeValue, sets start node
void initSingleSource(Graph &g, Graph::vertex_descriptor start) {

	clearPred(g);  // Clear predecessors
	setNodeWeights(g, LargeValue);  // Set weights
	g[start].weight = 0;  // Start

}

// Relaxes the edge between nodes node1 and node2
void relax(Graph &g, Graph::vertex_descriptor node1, 
		  Graph::vertex_descriptor node2, 
		  Graph::edge_descriptor edge) {

	if(g[node1].weight > (g[node2].weight + g[edge].weight)) {
			g[node1].weight = (g[node2].weight + g[edge].weight);
			g[node1].pred = node2;
	}

}

// Bellman ford algorithm for finding the shortest path
bool bellmanFord(Graph &g, Graph::vertex_descriptor start) {

	initSingleSource(g, start);  // Initialize

	// Node used for relax function
	Graph::vertex_descriptor targ;  
	Graph::vertex_descriptor src;  

	// First-Last vertices and edges
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
		      vertices(g);
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange =
		      edges(g);

	// For each vertex - 1, relax each edge
	for (Graph::vertex_iterator vItr = vItrRange.first;
      vItr != vItrRange.second; ++vItr) {
		for (Graph::edge_iterator eItr = eItrRange.first;
		      eItr != eItrRange.second; ++eItr) {
				targ = target(*eItr, g);
				src = source(*eItr, g);
				relax(g, targ, src, *eItr);
		}
	}

	// One more time checking for negative weights
	for (Graph::edge_iterator eItr = eItrRange.first;
	      eItr != eItrRange.second; ++eItr) {
			targ = target(*eItr, g);
			src = source(*eItr, g);
			if(g[targ].weight > (g[src].weight + g[*eItr].weight))
				return false;  // Negative cycle found
	}

	return true;  // No negative cycles

}

// Dijkstra's algorithm to find the shortest path from start to all nodes
bool dijkstra(Graph &g, Graph::vertex_descriptor start) {

	// Initialize
	initSingleSource(g, start);

	// Heap to store minimum priority list
	heapV <Graph::vertex_descriptor, Graph> heap;

	// Put all verticies in a vector to initialize heap
	vector <Graph::vertex_descriptor> vect;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
		      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
	      vItr != vItrRange.second; ++vItr) {
		vect.push_back(*vItr);
	}

	// Initialize and build
	heap.initializeMinHeap(vect, g);
	heap.buildMinHeap(vect.size(), g);

	// While there are elements in the heap
	while(heap.size() != 0) {
		// Get minimum
		Graph::vertex_descriptor shortest = heap.extractMinHeapMinimum(g);
		
		// For each adjacent edge where there is an edge from 
		// Shortest to the vertex
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange =
		                adjacent_vertices(shortest, g);
		for(Graph::adjacency_iterator vItr = vItrRange.first;
		                         vItr != vItrRange.second; ++vItr) {
			pair<Graph::edge_descriptor, bool> checkEdge = edge(shortest, (*vItr), g);
			if (checkEdge.second == true) {
				Graph::edge_descriptor edge = checkEdge.first;
				relax(g, (*vItr), shortest, edge);  // Relax edge
			}
		}
		heap.buildMinHeap(heap.size(), g);  // Reorder into min heap
		// If there are any disconnected components return false
		if(g[heap.getMinHeapMinimum()].weight == LargeValue) {
			heap.buildMinHeap(heap.size(), g);
			return false;
		}
	}
	return true;  // No disconnected components

}

// Prints the path from the ending node to the starting node in the form
// end --> end-1 --> end-2 ... --> start. If no path, prints error message
void printPath(Graph& g, Graph::vertex_descriptor start, Graph::vertex_descriptor end) {
	
	// If last node was never visited
	if (g[end].weight == LargeValue)
		cout << "No path exists from the start to end" << endl;
	else {
		// 
		Graph::vertex_descriptor v = end;
		cout << v;
		while(v != start) {
			v = g[v].pred;
			cout << " --> " << v;
		}
		cout << endl;
	}
	cout << endl;
}

