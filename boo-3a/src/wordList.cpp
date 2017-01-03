// Jason Booth   project 3a   boo-3a
// This file defines the wordlist class

#include "wordList.h"  // Include header file

// This function reads in the words from a file and stores them in the vector words
void wordList::readWords(const string& fileLocation) {

	ifstream fin;  // Input file stream
	fin.open(fileLocation.c_str());  // Attempt to open

	// Error handling, if file cannot be opened throw error
	if (!fin) {
		throw fileOpenError(fileLocation);  // Name of file
	}

	// Read in each word and add it to the end of words
	string x;
	while (true) {  // Infinite loop
		if (fin.eof()) {
			break;
		}  // Stop at end of file
		fin >> x;  // Read in
		words.push_back(x);  // Add to end of words
	}

	fin.close();  // Close file

}

// Returns the size of the words vector
int wordList::size() {

	// Size of words
	return words.size();

}

// Implements insert sort algorithm
void wordList::sortInsert() {

	int j, i = 0;  // Iterators
	string key = "";  // Key

	// For each word in words starting at 1
	for (j = 1; j < words.size(); j++) {
		key = words[j];  // Assign key
		i = j - 1;  // Change i

		// Until spot has been found or end is reached
		while ((i > 0) && (words[i] > key)) {
			words[i + 1] = words[i];  // Switch spots
			i--;  // Adjust i
		}

		words[i + 1] = key; // Assign Position next to sorted word
	}

}

// Implements quick sort algorithm
void wordList::sortQuick(const int& first, const int& endRight) {

	int middle;  // End of left side of quick sort

	// More than 1 element in iteration
	if (first < endRight) {
		middle = quickAux(first, endRight);  // Find endLeft
		sortQuick(first, middle - 1);  // Sort left
		sortQuick(middle + 1, endRight);  // Sort right
	}

}

// Auxillary function to determine the value for middle in sortQuick
int wordList::quickAux(const int& first, const int& pivotIndex) {

	string pivot = words[pivotIndex];  // Pivot value
	int endLeft = first - 1;  //  Assign initial value for end of left list

	// For each element
	for (int curr = first; curr < pivotIndex; curr++) {

		// If less than pivot, exchange and increase value for endLeft
		if (words[curr] <= pivot) {
			endLeft++;  // Increase endLeft
			swap(words[curr], words[endLeft]);  // Exchange current and endLeft
		}

	}

	swap(words[endLeft + 1], words[pivotIndex]);  // Exchange pivot and next to endLeft
	return (endLeft + 1);  // Return index

}

// Implements merge sort algorithm
void wordList::sortMerge(const int& first, const int& last) {

	// If the first is less than the last (not a base case)
	if (first < last) {
		int middle = (first + last) / 2;  // Set value for middle
		sortMerge(first, middle);  // Split first half of the list
		sortMerge(middle + 1, last);  // Split second half
		mergeAux(first, middle, last);  // Merge lists
	}
}

// Auxillary function for merge sort
void wordList::mergeAux(const int& first, const int& middle, const int& last) {

	int i, j, k = 0;  // Iterators
	vector <string> L;  // Left vector
	vector <string> R;  // Right vector
	int n1 = (middle - first) + 1;  // Length of left vector
	int n2 = last - middle;  // Length of right vector

	// Populate left vectora
	for (i = 0; i < n1; i++)
		L.push_back(words[first + i]);

	// Populate right vector
	for (j = 0; j < n2; j++)
		R.push_back(words[middle + j + 1]);

	L.push_back(ENDWORD);  // Add "zzzzzzz" for comparisons
	R.push_back(ENDWORD);
	i = 0;  // Reset iterators
	j = 0;

	// Merge values, take from L or R depending on which is smallest
	for (k = first; k <= last; k++) {  // For each element in L and R
		if (L[i] <= R[j]) {  // Left is less than right
			words[k] = L[i];  // Assign value from L
			i++;  // Increase index
		} else {  // Right is less than left
			words[k] = R[j];  // Assign value from R
			j++;  // Increase index
		}
	}

}

// Implements binary search algorithm for
int wordList::binarySearch(const string& key) {

	// Return result of search
	return binarySearchAux(key, 0, words.size() - 1);

}

// Auxillary function for binary search
int wordList::binarySearchAux(const string& key, const int& left,
							  const int& right) {

	// If not found
	if (right < left)
		return -1;

	// Assign middle
	int mid = (left + right) / 2;

	// If key has been found
	if (key == words[mid])
		return mid;
	else if (key < words[mid])  // Search left
		return (binarySearchAux(key, left, mid - 1));
	else  // Search right
		return (binarySearchAux(key, mid + 1, right));
}

// Overloaded << operator
ostream& operator <<(ostream& ostr, const wordList& inList) {

	// For each element
	for (int i = 0; i < inList.words.size(); i++)
		ostr << inList.words[i] << endl;  // Print element
	return ostr;  // Return stream
}

// Overloaded [] operator, returns row using array indexing
string& wordList::operator[](const int& index) {

	// Check index accessor less than 0
	if (index < 0) {
		throw rangeError("Error: wordList index must be greater "
				"than or equal to 0");
	}

	// Check index accessor greater than size
	if (index >= words.size()) {
		throw rangeError("Error: wordList index must be less than "
				"size of word list");
	}

	// Return vector using array indexing
	return words[index];

}

// Overloaded [] operator for const matrix
const string& wordList::operator[](const int& index) const {

	// Check index accessor less than 0
	if (index < 0) {
		throw rangeError("Error: wordList index must be greater "
				"than or equal to 0");
	}

	// Check index accessor greater than size
	if (index >= words.size()) {
		throw rangeError("Error: wordList index must be less than "
				"size of word list");
	}

	// Return vector using array indexing
	return words[index];
}
