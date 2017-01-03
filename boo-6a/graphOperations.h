// Jason Booth   Project 6a   boo-6a
// This file implements the graph procedures including the 
// isConnected, isCyclic, and findSpanningForest functions

#include <iostream>
#include <fstream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>  // BGL library
#include "d_except.h"

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
void initializeGraph(string fileLocation, Graph &g)
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
   Graph::vertex_descriptor v;

   // Set start and end nodes
   for (int i = 0; i < n; i++)
   {
      v = add_vertex(g);
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

// Mark all nodes in g as not visited.
void clearVisited(Graph &g){
    // Iterate through each vertex
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
      vItr != vItrRange.second; ++vItr) {
		g[*vItr].visited = false;  // Not visited
		g[*vItr].pred = 0;  // Clear the predecessors
	}

	// Need to set the last value
	g[*vItrRange.second].visited = false;
	g[*vItrRange.second].pred = 0;
}

// Set all node marked properties to false
void clearMarked(Graph &g) {
    // Iterate through each vertex and set each marked property to false
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
      vItr != vItrRange.second; ++vItr)
		g[*vItr].marked = false;  // Set to false
	g[*vItrRange.second].marked = false;  // Set last vertex

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

// Prints the total weight of the graph and the total number of components
// (Considering the pair going to and from nodes to be a single edge)
void print(Graph& g) {

	// Initialize sum and numEdge
	int sum = 0;
	int numEdge = 0;

	// For each edge
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange =
  edges(g);
	for (Graph::edge_iterator eItr = eItrRange.first;
   eItr != eItrRange.second; ++eItr) {
			sum += g[*eItr].weight;  // Calculate sum
			// Print edge
			cout << source(*eItr, g) << "--" << target(*eItr, g) << endl;
			// Increase number of edges
			numEdge++;
	}

	int numNodes = num_vertices(g);

	// Print (number of connected components = nodes - number of edges)
	cout << "Total sum of forest: " << sum/2 << endl;
	cout << "Total number of Connected Components: " << 
	numNodes - (numEdge/2) << endl << endl;

}

// Depth first search, used to check connectivity. If all nodes are connected
// A single call to this function should visit each node
void dfs(Graph &g, Graph::vertex_descriptor start) {

	g[start].visited = true;

	// For each adjacent node
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange =
	adjacent_vertices(start, g);
	Graph::adjacency_iterator vItr = vItrRange.first;
	while(vItr != vItrRange.second) {

		// If node has not been visited
		if(g[*vItr].visited == false) {
			// Visit node, and recursively call dfs
			g[*vItr].pred = start;  // Set predecessor
			dfs(g, *vItr);
		}
		++vItr;  // Next adjacent edge
	}
}

// This function clears properties and then calls dfs. Then it checks
// To see if each node has been visited. If a node has not been visited
// It returns false, otherwise true.
bool isConnected(Graph &g) {

	// Clear values
	clearMarked(g);
	clearVisited(g);
	clearPred(g);

	// Call dfs on the starting node
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
    vertices(g);
	dfs(g, *vItrRange.first);

	// For each node, check if any nodes not visited
	for (Graph::vertex_iterator vItr = vItrRange.first;
   vItr != vItrRange.second; ++vItr) {
		if(g[*vItr].visited == false)
			return false;
	}
	// All nodes visited
	return true;

}

// This function implements a dfs where if a cycle is found true is returned
bool dfsHelp(Graph &g, Graph::vertex_descriptor start, 
			Graph::vertex_descriptor previous) {

	// Visit starting node
	g[start].visited = true;

	// For each adjacent node
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange =
	adjacent_vertices(start, g);
	Graph::adjacency_iterator vItr = vItrRange.first;
	while(vItr != vItrRange.second) {

		// If node is not the previous node
		if((*vItr) != previous) {

			// If the node has been visited, cycle found, return true
			if(g[*vItr].visited == true)
				return true;
			// Recursively call dfs setting new previous node
			g[*vItr].pred = start;  // Set predecessor
			dfsHelp(g, *vItr, start);
		}
		++vItr;  // Next adjacent edge
	}
	// No cycles found
	return false;

}

// Calls dfsHelp and returns true is cycles are found, false otherwise
bool isCyclic(Graph &g) {

	// Clear variables
	clearMarked(g);
	clearVisited(g);
	clearPred(g);

	// For each graph in g
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
    vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
   vItr != vItrRange.second; ++vItr) {
		if(g[*vItr].visited == false) {  // If node not visited (new graph)
			if(dfsHelp(g, *vItr, *vItr))  // If cycle found
				return true;
		}
	}

	// No cycles found
	return false;

}

// This function creates a spanning tree for the given graph and saves it in sf
// The function uses visited and marked flags to traverse the graph
void bfs(Graph &g, Graph::vertex_descriptor start, Graph &sf) {

	// Queue for storing nodes of the graph
	queue <Graph::vertex_descriptor> q;  // Stores nodes

	// Push the first element onto the queue, visited
    q.push(start);
	g[start].visited = true;

	// Vertex Descriptor, new edge descriptors
	Graph::vertex_descriptor u;  
	pair<Graph::edge_descriptor, bool> newEdge1, newEdge2;

	// This algorithm works by marking nodes that are in the sf, and using
	// The visited flag to determine what to add to the queue
	while(!(q.empty())) {  // While there are elements in the queue

		u = q.front();  // Get first element
		q.pop();  // Remove element from queue

		if ((!(g[u].marked)) && (g[u].visited)) {
			g[u].marked = true;  // Mark node, is in sf
			
			// For each adjacent node
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> 
			vItrRange = adjacent_vertices(u, g);
			for(Graph::adjacency_iterator vItr = vItrRange.first; 
			vItr != vItrRange.second; ++vItr) {
				// If node has not been visited, add to queue and to sf
				if((g[(*vItr)].visited) == false) {

					// Create bi-directional edge, assign weights
					newEdge1 = add_edge(u, *vItr, sf);
					newEdge2 = add_edge(*vItr, u, sf);
					sf[newEdge1.first].weight = 
					g[edge(*vItr, u, g).first].weight;
					sf[newEdge2.first].weight = 
					g[edge(*vItr, u, g).first].weight;
					q.push(*vItr);  // Add to queue
					g[*vItr].pred = u;  // Assign pred, visited
					g[*vItr].visited = true;
				}
			}
		}
	}

}

// This function creates the spanning forest of the given graph
void findSpanningForest(Graph &g, Graph &sf) {

	// Clear values
	clearMarked(g);
	clearVisited(g);
	clearPred(g);

	// Add all values to sf
   Graph::vertex_descriptor v;
   pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
   vertices(g);
   for (Graph::vertex_iterator vItr = vItrRange.first;
   vItr != vItrRange.second; ++vItr) {
	   add_vertex(sf);
   }

   // Create each tree
   for (Graph::vertex_iterator vItr = vItrRange.first;
   vItr != vItrRange.second; ++vItr) {
		if(g[*vItr].visited == false)
			bfs(g, *vItr, sf);
   }

}
