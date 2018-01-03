// Jason Booth   Project 5-b   boo-5b
// This file defines several graph operations and includes the maze class

#include "maze.h"  // For maze class

using namespace boost;  // For BGL
using namespace std;

#define LargeValue 99999999  // Used as several default values

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

// Set all edge weights to w
void setEdgeWeights(Graph &g, int w) {

    // Iterate through each edge and set each weight property to w
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange =
      edges(g);
	for (Graph::edge_iterator eItr = eItrRange.first;
       eItr != eItrRange.second; ++eItr)
		g[*eItr].weight = w;  // Set each weight
	g[*eItrRange.second].weight = w;  // Set last weight

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

// This function recursively traverses the graph and returns the first stack
// Which traverses across the end
stack<Graph::vertex_descriptor> traverseRecursive(maze m, Graph g, 
Graph::vertex_descriptor v, Graph::vertex_descriptor end) {

	// Stack to be returned
	stack<Graph::vertex_descriptor> found;

	// Case for first cell so that graph will be check to the right and below
	
	// If first cell
	if (v == m.getVertex(g, 0, 0)) {

		// Set as visited
		g[v].visited = true;

		// If node to the right
		if(m.isLegal(0, 1)) {
				g[m.getVertex(g, 0, 1)].pred = v;  // Set predecessor
				// Get Stack
				found = traverseRecursive(m, g, m.getVertex(g, 0, 1), end);
					if (!found.empty()) {  // If not empty, return
						found.push(v);  // Add first node
						return found; 
					}
		}

		// If node below
		if(m.isLegal(1, 0)) {
				g[m.getVertex(g, 1, 0)].pred = v;  // Set predecessor
				// Get stack
				found = traverseRecursive(m, g, m.getVertex(g, 1, 0), end);
				if (!found.empty()) {  // If not empty, return
					found.push(v);  // Add first node
					return found;
				}
		}
	}

	// Base case for if node is the ending node
	if(v == end) {
		Graph::vertex_descriptor itr = end;  // Set a descriptor
		// Push each node in path on the stack
		while(itr != m.getVertex(g, 0, 0)) {
			found.push(itr);  // Add first node
			itr = g[itr].pred;
		}
		// Return stack 
		return found;
	}

	// If the node has not been visited
	if(!(g[v].visited)) {
		// Visit
		g[v].visited = true;
		// For each adjacent node
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange =
		adjacent_vertices(v, g);
		Graph::adjacency_iterator vItr = vItrRange.first;
		while(vItr != vItrRange.second) {
			// If it has not been visited
			if((g[(*vItr)].visited) == false) {
				// Get the path
				g[*vItr].pred = v;  // Set predecessor
				found = traverseRecursive(m, g, *vItr, end);
				if (!found.empty()) {  // If not empty
					return found;
				}
			}
			++vItr;  // Next adjacent edge
		}
	}
	return found;  // Return empty stack
}

stack<Graph::vertex_descriptor> findPathDFSRecursive(maze m, Graph &g, 
Graph::vertex_descriptor start, Graph::vertex_descriptor end) {

	// Set each boolean flag to false, each pred to LargeValue
	clearVisited(g);
	clearPred(g);

	// Set stack
	stack<Graph::vertex_descriptor> stack = traverseRecursive(m, g, start, end);

	// Return
	return stack;

}

// This function returns true if a DFS path is found using a stack
bool traverseStack(maze m, Graph &g, Graph::vertex_descriptor v, 
Graph::vertex_descriptor end) {

	// To hold adjascent values
	stack <Graph::vertex_descriptor> s;

	// Base case for node to the right of first cell
	if(m.isLegal(0, 1)) {
		g[m.getVertex(g, 0,1)].pred = v;  // Set pred
		s.push(m.getVertex(g, 0, 1));  // Add to stack
	}

	// Base case for node below first cell
	if(m.isLegal(1, 0)) {
		g[m.getVertex(g, 1, 0)].pred = v;  // Set pred
		s.push(m.getVertex(g, 1, 0));  // Add to stack
	}

	g[v].visited = true;  // First cell is visited

	Graph::vertex_descriptor u;  // Stores current descriptor

	while(!(s.empty())) {  // While there are values in the stack

		u = s.top();  // Assign u
		s.pop();  // Remove element from stack

		if(u == end)  // Got to the last node
			return true; 

		// If the node has not been visited
		if (!(g[u].visited)) {
			// Visit
			g[u].visited = true;
			
			// For each adjacent node
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> 
			vItrRange = adjacent_vertices(u, g);
			for(Graph::adjacency_iterator vItr = vItrRange.first; 
			vItr != vItrRange.second; ++vItr) {
				if((g[(*vItr)].visited) == false) {  // If not visited
					s.push(*vItr);  // Add to stack
					g[*vItr].pred = u;  // Set pred
				}
			}
		}
	}
	if (g[end].pred == LargeValue)  // If last pred value did not change
		return false;
	return true;  // Algoirthm worked

}

// This function calculates the first DFS path using a stack
stack<Graph::vertex_descriptor> findPathDFSStack(maze m, Graph &g, 
Graph::vertex_descriptor start, Graph::vertex_descriptor end) {

	// Set each boolean flag to false
	clearVisited(g);
	clearPred(g);

	stack<Graph::vertex_descriptor> stack;  // Stores path

	Graph::vertex_descriptor itr;  // Used to add nodes

	bool dfs = traverseStack(m, g, start, end);  // If true, path found

	if(dfs) {  // If path found, add from end to beginning
		itr = end;  
		while(itr != start) {
			stack.push(itr);
			itr = g[itr].pred;
		}
		stack.push(start);
	}

	return stack;  // Return
}

// This function uses recursion to calculate the shortest path using DFS
stack<Graph::vertex_descriptor> traverseShortestPathDFS(maze m, Graph g, 
Graph::vertex_descriptor v, Graph::vertex_descriptor end, 
stack<Graph::vertex_descriptor>& largeStack ) {

	// Bad starting best value
	stack<Graph::vertex_descriptor> bestStack = largeStack;  
	stack<Graph::vertex_descriptor> dfs;  // Assigned after each recursive call

	// Base case. If end, add end to dfs and return
	if(v == end) {
		dfs.push(end);
		return dfs;
	}

	// Adjacent iterators
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> 
	vItrRange = adjacent_vertices(v, g);

	// If the node has not been visited
	if(!(g[v].visited)) {
		g[v].visited = true;  // Visit
		Graph::adjacency_iterator vItr = vItrRange.first;
		while(vItr != vItrRange.second) {  // For each adjacent node
			// If the node has not been visited or it is the end
			if((g[(*vItr)].visited) == false  || (*vItr) == end) {
				// Calculate path
				dfs = traverseShortestPathDFS(m, g, *vItr, end, largeStack);
				// If the path is not empty
				if (!dfs.empty()) {
					if(dfs.size() < bestStack.size()) {  // Set best path
						bestStack = dfs;
						bestStack.push(*vItr);  // Add node
					}
				}
			}
			++vItr;  // Next adjacent
		}
	}
	if(bestStack.size() < largeStack.size()) {  // If bestStack changed
		return bestStack;
	}
	else {
		stack<Graph::vertex_descriptor> stack;
		return stack;  // No path, return empty stack
	}
}

// This function uses recursion to calculate the shortest path using DFS
stack<Graph::vertex_descriptor> findShortestPathDFS(maze m, Graph &g, 
Graph::vertex_descriptor start, Graph::vertex_descriptor end) {

	// Set each visited to false, pred to LargeValue
	clearVisited(g);
	clearPred(g);

	// Set two DFS values, one for each node next to base case node(0, 0)
	stack<Graph::vertex_descriptor> dfs1;
	stack<Graph::vertex_descriptor> dfs2;

	// Used in traverse as a bad starting stack length
	stack<Graph::vertex_descriptor> largeStack;

	// Add each node to largeStack
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
	      vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first;
	      vItr != vItrRange.second; ++vItr)
			largeStack.push(*vItr);

	// First node visited
	g[m.getVertex(g, 0, 0)].visited = true;

	// If there is a node to the right of node(0,0)
	if(m.isLegal(0, 1)) {
		g[m.getVertex(g, 0, 1)].pred = start;  // Set pred
		// Get stack
		dfs1 = traverseShortestPathDFS(m, g, m.getVertex(g, 0, 1), 
		end, largeStack);
	}

	// If there is a node below node(0,0)
	if(m.isLegal(1, 0)) {
		g[m.getVertex(g, 1, 0)].pred = start;  // Set pred
		// Get stack
		dfs2 = traverseShortestPathDFS(m, g, m.getVertex(g, 1, 0), 
		end, largeStack);
	}

	if(dfs1.size() < dfs2.size()) {  // If DFS1 < DFS2
		if(!dfs1.empty()) {  // If DFS1 is not empty
			return dfs1;
		}
		return dfs2;  // Is either a stack or empty
	} else {
		if(!dfs2.empty()) {  // If DFS2 is not empty
			return dfs2;
		}
		return dfs1;  // Is either a stack or empty
	}
}

// This function returns true if it finds a BFS path using a queue
bool traverseBFS(maze m, Graph &g, Graph::vertex_descriptor v, 
Graph::vertex_descriptor end) {

	queue <Graph::vertex_descriptor> q;  // Stores nodes

	if(m.isLegal(0, 1)) {  // If to the right of starting is legal
		g[m.getVertex(g, 0,1)].pred = v;  // Assign pred
		q.push(m.getVertex(g, 0,1)); // Add to queue
	}

	if(m.isLegal(1, 0)) {  // If below starting is legal
		g[m.getVertex(g, 1, 0)].pred = v;  // Assign pred
		q.push(m.getVertex(g, 1, 0));  // Add to queue
	}

	g[v].visited = true;  // First node visited

	Graph::vertex_descriptor u;  // Vertex Descriptor

	while(!(q.empty())) {  // While there are elements in the queue

		u = q.front();  // Get first element
		q.pop();  // Remove element

		if(u == end)  // Base case if end node, return true
			return true;

		// If the node has not been visited
		if (!(g[u].visited)) {
			g[u].visited = true;  // Visit
			// For each adjacent node
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> 
			vItrRange = adjacent_vertices(u, g);
			for(Graph::adjacency_iterator vItr = vItrRange.first; 
			vItr != vItrRange.second; ++vItr) {
				// If node has not been visited
				if((g[(*vItr)].visited) == false) {
					q.push(*vItr);  // Add to queue
					g[*vItr].pred = u;  // Assign pred
				}
			}
		}
	}
	if (g[end].pred == LargeValue)  // If end has not been changed
		return false;
	return true;  // Algorithm worked

}

// This function calculates the BFS path using a queue
stack<Graph::vertex_descriptor> findShortestPathBFS(maze m, Graph &g, 
Graph::vertex_descriptor start, Graph::vertex_descriptor end) {

	// Set each visited flag to false and pred to LargeValue
	clearVisited(g);
	clearPred(g);

	// Stores nodes in path
	stack<Graph::vertex_descriptor> stack;

	// Used to add each node to path
	Graph::vertex_descriptor itr;

	// See if path exists
	bool dfs = traverseBFS(m, g, start, end);

	// If path, add each element to stack
	if(dfs) {
		itr = end;  // Set to end
		while(itr != start) {
			stack.push(itr);  // Add each element
			itr = g[itr].pred;  // Next node
		}
		stack.push(start);  // Add first node
	}

	return stack;  // Return full stack or empty
}
