// Jason Booth   Project 5b   boo-5b
// This project was created on a Linux Ubuntu 14.04 System
// This file creates a graph and calls functions from the maze class

#include <iostream>  // For cout
#include <limits.h>  // For limits
#include <vector>  // For STL vector
#include <list>  // For STL list
#include <fstream>  // For reading in a file
#include <queue>  // For STL queue
#include "graphOperations.h"  // For maze class and search operations
#include <boost/graph/adjacency_list.hpp>  // BGL library


int main()
{
  try
  {
      // File stream
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

      cout << "Maze: " << endl;
      
      // Print the maze
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      // Declare a graph and map the maze to it
      Graph g;
      m.mapMazeToGraph(g);
	
      // Clear all values
      clearVisited(g);
      setNodeWeights(g, 1);     
      clearMarked(g);      
      clearPred(g);

      cout << "Executing DFS Recursive method" << endl;

      stack<Graph::vertex_descriptor> result1 = 
      findPathDFSRecursive(m, g, m.getVertex(g, 0, 0), 
      m.getVertex(g, m.numRows()-1, m.numCols()-1));
      m.printPath(g, m.getVertex(g, m.numRows()-1, m.numCols()-1), result1);

      cout << "Executing DFS Stack method" << endl;

      stack<Graph::vertex_descriptor> result2 = 
      findPathDFSStack(m, g, m.getVertex(g, 0, 0), 
      m.getVertex(g, m.numRows()-1, m.numCols()-1));
      m.printPath(g, m.getVertex(g, m.numRows()-1, m.numCols()-1), result2);

      cout << "Executing Shortest Path DFS method" << endl;

      stack<Graph::vertex_descriptor> result3 = 
      findShortestPathDFS(m, g, m.getVertex(g, 0, 0), 
      m.getVertex(g, m.numRows()-1, m.numCols()-1));
      m.printPath(g, m.getVertex(g, m.numRows()-1, m.numCols()-1), result3);

      cout << "Executing Shortest Path BFS method" << endl;

      stack<Graph::vertex_descriptor> result4 = 
      findShortestPathBFS(m, g, m.getVertex(g, 0, 0), 
      m.getVertex(g, m.numRows()-1, m.numCols()-1));
      m.printPath(g, m.getVertex(g, m.numRows()-1, m.numCols()-1), result4);


  }

  catch  (indexRangeError &ex)
   {
      // Catch and print errors
      cerr << ex.what() << endl;
      exit(1);
   }

      return 0;
}
