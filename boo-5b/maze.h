// Jason Booth   Project 5b   boo-5b
// This file defines the maze class and several BGL structs/typedefs

#include <iostream>  // For cout
#include <limits.h>  // For INT_MAX
#include <list>  // For STL list
#include <fstream>  // For file reading
#include <queue>  // For STL queue
#include <vector>  // For STL vector
#include <stack>  // For STL stack
#include <boost/graph/adjacency_list.hpp>  // Boost library
#include "d_except.h"  // Exception handling
#include "d_matrix.h"  // Matrix class

#define LargeValue 99999999  // Initial value for nodes

using namespace boost;
using namespace std;


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

// Class to store the maze data for printing and accessing graph
class maze
{
public:
   maze(ifstream &fin);  // Reads in maze and assigns the value matrix
   void print(int,int,int,int);  // Print the maze
   bool isLegal(int i, int j);  // Checks if the value is legal
   void mapMazeToGraph(Graph &g);  // Maps maze to a graph
   // Prints path contained in the stack
   void printPath(Graph& g, Graph::vertex_descriptor end,
                        stack<Graph::vertex_descriptor> &s);
   int numRows(){return rows;};  // Returns number of rows
   int numCols(){return cols;};  // Returns number of cols
   Graph::vertex_descriptor getVertex(Graph&, int, int);
   // Overloaded << operator
   friend ostream &operator<<(ostream &ostr, const Graph &g);

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   matrix<Graph::vertex_descriptor> graphCell;  // Contains graph mappings
   matrix<bool> value;  // Contains values at each cell
};


// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
maze::maze(ifstream &fin)
{
   fin >> rows;  // Assign rows and cols
   fin >> cols;
   
   char x;
   
   // Assign size of value and graphCell matrices
   value.resize(rows,cols);  
   graphCell.resize(rows,cols);

   // Read in and assign value matrix
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
}

// Print out a maze, with the goal and current cells marked on the
// board.
void maze::print(int goalI, int goalJ, int currI, int currJ)
{
   cout << endl;

   // Check that the printing values are in range
   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols) {
      throw rangeError("Bad value in maze::print");
   }

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols) {
      throw rangeError("Bad value in maze::print");
   }
   // Print maze
   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
bool maze::isLegal(int i, int j)
{
   // Check if in range
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");
   
   // Return value in the index
   return value[i][j];
}

// Create a graph g that represents the legal moves in the maze m.
void maze::mapMazeToGraph(Graph &g) {

    // Adds verticies to the graph
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (value[row][col]) {
                // Add vertex
				Graph::vertex_descriptor v = add_vertex(g);
                
                // Map cell to cell in matrix
				g[v].cell = make_pair(row, col);

                // Set graphCell matrix
				graphCell[row][col] = v;
			}
		}
	}

    // Adds edges to the graph by checking if there is a cell to the right and
    // Below each cell
	for (int row = 0; row < rows; row++) {
	for (int col = 0; col < cols; col++) {
            
	if (value[row][col]) {
	    if((row + 1) < rows) {
                if(value[row + 1][col])  {  // If below cell is filled
                    pair<Graph::edge_descriptor,bool> edge = 
                    add_edge(graphCell[row][col], graphCell[row + 1][col], g);
                    g[edge.first].weight = 0;
                }
            }

            if((col + 1) < cols) {
                if(value[row][col + 1]) {  // If right cell is filled
                    pair<Graph::edge_descriptor,bool> edge = 
                    add_edge(graphCell[row][col], graphCell[row][col + 1], g);
                    g[edge.first].weight = 0;
                }
            }

            if((row - 1) >= 0) {
                if(value[row - 1][col])  {  // If below cell is filled
                    pair<Graph::edge_descriptor,bool> edge =
                    add_edge(graphCell[row][col], graphCell[row - 1][col], g);
                    g[edge.first].weight = 0;
                }
            }

            if((col - 1) >= 0) {
                if(value[row][col - 1]) {  // If right cell is filled
                    pair<Graph::edge_descriptor,bool> edge =
                    add_edge(graphCell[row][col], graphCell[row][col - 1], g);
                    g[edge.first].weight = 0;
                }
            }
	}
	}
	}

}

Graph::vertex_descriptor maze::getVertex(Graph &g, int row, int col) {
   // Check if in range
   if (row < 0 || row > rows || col < 0 || col > cols)
	  throw rangeError("Bad value in maze::getVertex");

   // Return value in the index
   return graphCell[row][col];
}

// Prints the path stored in the stack
void maze::printPath(Graph& g, Graph::vertex_descriptor end,
                     stack<Graph::vertex_descriptor> &s) {

	Graph::vertex_descriptor Itr;
	int col, row, endRow, endCol;

    // Set end row numbers
	endRow = g[end].cell.first;
	endCol = g[end].cell.second;

    // If the stack is empty
	if (s.empty()) {
		cout << "No path exists" << endl;
		return;
	}

    // While there are still numbers in the stack
	while ( s.size() != 1 ) {


        // Set Itr, pop the stack
		Itr = s.top();
		s.pop();

        // Read row and col values, and print graph
        row = g[Itr].cell.first;
        col = g[Itr].cell.second;


        // Print graph
		print(endRow, endCol, row, col);
	}
}

// Overlaoded << operator, prints properties of each vertex edge
ostream &operator<<(ostream &ostr, const Graph &g) {
  
  // Gets first and last verticies
  pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
  
  // Iterate through each vertex
  for (Graph::vertex_iterator vItr = 
  vItrRange.first; vItr != vItrRange.second; ++vItr) {

	  // Print out node number
	  ostr << "Node: " << (*vItr) << endl;
      // Print cell data
      ostr << "Cell: " << g[*vItr].cell.first << " " 
      << g[*vItr].cell.second << endl;
      // Print pred
      ostr << "Pred: " << g[*vItr].pred << endl;
      // Print weight
      ostr << "Weight: " << g[*vItr].weight << endl;
      // Print visited
      ostr << "Visited: " << g[*vItr].visited << endl;
      // Print marked
      ostr << "Marked: " << g[*vItr].marked << endl;
  }

    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
  for (Graph::edge_iterator eItr = 
  eItrRange.first; eItr != eItrRange.second; ++eItr) {

	  // Print out edge number
	  ostr << "Edge: " << (*eItr) << endl;
      // Print weight
      ostr << "Weight: " << g[*eItr].weight << endl;
      // Print visited
      ostr << "Visited: " << g[*eItr].visited << endl;
      // Print marked
      ostr << "Marked: " << g[*eItr].marked << endl;
  }

  // Print total information
  ostr << endl << "Number of Vertices: " << num_vertices(g) << endl;
  ostr << "Number of Edges: " << num_edges(g) << endl;

  // Return ostream
  return ostr;
}
    
