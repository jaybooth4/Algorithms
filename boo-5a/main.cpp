// Jason Booth   Project 5a   boo-5a
// This project was created on a Linux Ubuntu 14.04 System on 
// the terminal. Compiles, and runs.
// This file creates a graph and calls functions from the maze class

#include <iostream>  // For cout
#include <limits.h>  // For INT_MAX
#include <vector>  // For STL vector
#include <list>  // For STL list
#include <fstream>  // For reading in a file
#include <queue>  // For STL queue
#include "maze.h"  // FOr maze class
#include <boost/graph/adjacency_list.hpp>  // BGL library

using namespace boost;
using namespace std;

#define LargeValue 99999999

// Mark all nodes in g as not visited.
void clearVisited(Graph &g){

      // Iterate through each vertex and set each visited property to false
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
      vItr != vItrRange.second; ++vItr)
		g[*vItr].visited = false;
}

// Set all node weights to w
void setNodeWeights(Graph &g, int w) {

      // Iterate through each vertex and set each weight property to w
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = 
      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
       vItr != vItrRange.second; ++vItr)
		g[*vItr].weight = w;
}

// Set all node marked properties to false
void clearMarked(Graph &g) {

      // Iterate through each vertex and set each marked property to false
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = 
      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; 
      vItr != vItrRange.second; ++vItr)
		g[*vItr].marked = false;
}


int main()
{
  try
  {
      ifstream fin;

      // Read the maze from the file.
      string fileName = "mazes/maze1.txt";
      
      // If file can be opened
      fin.open(fileName.c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      // Call constructor, close file
      maze m(fin);
      fin.close();
      
      // Print the maze
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      // Declare a graph and map the maze to it
      Graph g;
      m.mapMazeToGraph(g);
	
      clearVisited(g);
      setNodeWeights(g, 1);     
      clearMarked(g);      

      // Print properties of all verticies and edges
      cout << g << endl;

  }

  catch  (indexRangeError &ex)
   {
      // Catch and print errors
      cerr << ex.what() << endl;
      exit(1);
   }

      return 0;
}
