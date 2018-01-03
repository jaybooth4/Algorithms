This project is uses a wordsearch algorithm and a large list of words which are sorted using
insertion sort, quick sort, and merge sort. Words are then looked up using a binary search and 
hashmaps. An analysis of the runtime is included below.


Jason Booth   project 3b   boo-3b
This file describes the project and the timing information for several tests

-------------------------------------------------------------------------------

With regard to the sorting algorithms:
Insert sort:
	By far the slowest sorting algorithm 
	Average time: 166.718 sec
Quick sort:
	Fastest sorting algorithm
	Average time: .094 sec
Merge sort:
	Third fastest sorting algorithm
	Average time: .422 sec
Heap sort:
	Second fastest sorting algorithm
	Average time: .236 sec

-------------------------------------------------------------------------------

With regard to searching:
Hash table:
	The time for searching using this data structure is highly dependent on 
	the size of the hash table. With a table of size 31, the time for 
	searching was about 4.05 seconds. With a size of 997, the time was .160
	seconds. With a size of 90001, the time was .011 seconds. With an increased
	amount of searches using the input30 dataset, the time was .145 sec.
Binary search:
	The time for searching the input15 file was .023 sec. The time for 
	searching the input30 file is .251. These are higher than the respective
	times for the optimal hash table.

-------------------------------------------------------------------------------

Overall these results agree with the algorithmic complexity of each 
algorithm/data structure.
