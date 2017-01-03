// Jason Booth   project 3b   boo-3b
// This file implements the heap functionality

#ifndef HEAP_H  // Header guard for multiple inclusion
#define HEAP_H

#include <algorithm>  // For std::swap
#include <iostream>  // For printing
#include <vector>  // For vectors

using namespace std;

// The heap class contains a pointer to a heap and has functionality to
// Transform it into a max or min heap and sort the values.
// This class uses indexing in accordance with the heap algorithms used in
// Class where the indexes start at one. Only when using the function swap
// Are the values converted back into array indexing, and -1 is used.
template <typename T>
class heap {
    public:

	// Default constructor, assign pointer to NULL
	heap() {

		// Point to NULL
		values = NULL;

	}
    
	// Takes in a vector<T> and assigns the pointer to point to it
	// Heap is passed by reference so changing it will change the actual vector
	// Calls buildMaxHeap function
    void initializeMaxHeap(vector<T>& heap) {

    	// Values points to the address of the passed vector
    	values = &heap;

    	// Builds max head
        buildMaxHeap(values->size());

    };
    
    // Makes the vector values points to a max heap
    void buildMaxHeap(const int& size) {

    	// Calls max heapify to sort the list
    	for (int i = size; i >= 1; i--)
    		maxHeapify(i, size);  // i is the index

    };

    // Max heapifies the node and recursively calls on children
    void maxHeapify(const int& index, const int& size) {

    	int largest = index;  // Set largest to initial value
        int leftChild = left(index);  // Get left node index
        int rightChild = right(index);  // Get right node index

        // If within the bounds of the heap
        if(leftChild != -1) {

        	// If less than size and child > parent
			if ((leftChild <= size) &&
					((*values)[leftChild-1] > (*values)[index-1]))
				largest = leftChild;  // Assign largest
        }

        // If within the bounds of the heap
        if(rightChild != -1) {

        	// If less than size and child > parent and left
			if ((rightChild <= size) &&
					((*values)[rightChild-1] > (*values)[largest-1]))
				largest = rightChild;  // Assign largest
        }

        // If largest changed
        if (largest != index) {
            swap((*values)[index-1], (*values)[largest-1]);  // Swap values
            maxHeapify(largest, size);  // Check children
        }

    };

	// Takes in a vector<T> and assigns the pointer to point to it
	// Heap is passed by reference so changing it will change the actual vector
	// Calls buildMinHeap function
    void initializeMinHeap(vector<T>& heap) {

    	// Values points to the address of the passed vector
    	values = &heap;

    	// Builds max head
        buildMinHeap(values->size());

    };

    // Makes the vector values points to a min heap
    void buildMinHeap(const int& size) {

    	// Calls min heapify to sort the list
    	for (int i = size/2; i >= 1; i--)
    		minHeapify(i, size);  // i is the index
    }

    // Min heapifies the node and recursively calls on children
    void minHeapify(const int& index, const int& size) {
        
        int smallest = index;  // Set smallest to initial value
        int leftChild = left(index);  // Get left node index
        int rightChild = right(index);  // Get right node index

        // If within the bounds of the heap
        if(leftChild != -1) {

        	// If less than size and child < parent
			if ((leftChild <= size) &&
					((*values)[leftChild-1] < (*values)[index-1]))
				smallest = leftChild;  // Assign smallest
        }

        // If within the bounds of the heap
        if(rightChild != -1) {

        	// If less than size and child < parent
			if ((rightChild <= size) &&
					((*values)[rightChild-1] < (*values)[smallest-1]))
				smallest = rightChild;  // Assign smallest
        }

        // If smallest changed
        if (smallest != index) {
            swap((*values)[index-1], (*values)[smallest-1]);  // Swap values
            minHeapify(smallest, size);  // Check children
        }

    };

    // Sorts the list
    void heapSort(int size) {

      // Moves largest value to end and calls maxHeapify to adjust positions
  	  for (int i = size; i >= 2; i--) {
  		  swap((*values)[0], (*values)[i-1]);  // Moves largest value to end
  		  size--;  // Adjusted size
  		  maxHeapify(1, size);  // Call max heapify on adjusted size of vector
    	}

    }

    // Returns the parent of the given index
    int parent(const int& index) {

    	// Check bounds
        if (index > 0 && index <= values->size())
            return index/2;  // Return
        else 
            return -1;  // If not in bounds
    };

    // Calculates left child and returns it if within bounds, else return -1
    int left(const int& index)
    { 
    	int leftChild = 2 * index;  // Left child index

    	// Check bounds
        if (leftChild <= values->size() && leftChild > 0)
            return leftChild;  // Return
        else
        	return -1;  // If not in bounds

    };

    // Calculates right child and returns it if within bounds, else return -1
    int right(const int& index)
    { 
    	int rightChild = 2 * index + 1;  // Right child index

    	// Check bounds
    	if (rightChild <= values->size() && rightChild > 0)
            return rightChild;  // Return
        else
        	return -1;  // If not in bounds

    };

    // Returns size of the vector pointed at by values
    int size() {

    	// Return size
    	return values->size();

    };

    // Prints the vector
    void print() {

    	// Print each element
        for (int i = 0; i < values->size(); i++)
            cout << (*values)[i] << " ";

        cout << endl;  // For formatting

    };

    private:
     vector <T>* values;  // Pointer to vector
};

#endif  // HEAP_H
