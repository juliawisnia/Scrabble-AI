# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

search.cpp
My search starts at the top-left corner of the graph,
and pushes all characters that are that type to a stack,
and when it finds a neighbor that is a different type,
it markes it as the "next" to search, so when the stack
is empty, and a "next" has been found, this "next" is
pushed to the stack, and is the next to be searched.
Everytime it encounters the char is it searching for,
it adds to a counter, currCountry, and when the stack
is empty compares it to the previous larger country,
replacing only if it is larger.  It exits when the stack
is empty and there is no "next" found, the prints the
largest country to cout.

coloring.cpp
For this, I ahve a struct for each of the countries.
My coloring uses essentially the same search algorithm
from search, except it iterates over a set of all the
countries that are present in the graph, and my function
findAllNeighbors inserts all of the neighbors into the
set of neighbors in the country's vector struct. Once
inserted, the algorithm that determines the color 
compares the values of each country's colors to that
of its neighbor, and if it has the same value, increases
the neighbor's color by 1.  This iterates through all
of the countries, thus ensuring that all have different
colors than their neighbors.  Then, I sort the countries
so they print in alphabetical order, and print their name
and color values to cout.

MinHeap.h
My MinHeap has several helper functions, the main two
which are heapifyDown and heapifyUp.  heapifyDown is
called when you remove a node from the heap, and it
has swapped the greatest leaf node with the first node.
After this, it moves this element down the heap until
it is sorted into its correct position.  heapifyUp is
called after insert, which adds an element at the end
of the heap, and sorts by priority, bubbling the element
up the heap until it is in the right place.
