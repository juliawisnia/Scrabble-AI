# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

The files in my hw2 folder that were used for testing should
not be graded. These files are hw1q4.txt, hw2q1.txt,
hw2q3.txt, hw2q4.txt, and hw2q4.cpp.

SELECTION_SORT
My selection sort works recursively. First, I implement a 
findMin function that gets the value of the head element, then 
subsequently compares every next value checking if it is less. 
Once search->nextis nullptr, I return a pointer to the smallest 
item.

Next, I implemented a function recurse that keeps track of a 
pointer curr. The elements before curr are always a sorted list.
findMin is callled on curr of every iteration of recurse, and
the smallest element is pushed before curr. The function returns
once min==curr and there is no curr to next. I check for the 
edge cases when elements are next to each other, when min is
the last element of the array, when curr is the first element,
and when the min element is curr. After I find min, I recurse
curr again. 

My LLSelection sort simply finds the absolute min of the list
by recursing from head, then sets curr equal to that element
and calls recurse, returning the min item.

CIRCULAR_LIST_INT
I don't implement a different constructor other than the
default provided in this .h file. My first function findItem
traverses the linked list through a for loop until it reaches
the index that it's finding, then returns a pointer to the 
Item found. My get function checks if the list is empty, then
if not, gets the size. In order for it to wrap around, I use
modulo, then traverse to the index and return the value of 
that element. The count member is incremented and decremented
in push_back and remove (respectively), so size simply returns
count. push_back adds a new element before the head, and updates
the surrounding pointers. It checks for when len==0, then adds
a new item and returns, or moves past that and updates pointers.
set traverses to the index, then updates the value of the item,
and remove updates pointers as well as deallocating the item's
memory, so all my destructor has to do is call remove until 
head=nullptr, then delete head.

DUCK_DUCK_GOOSE
This file reads in the information from the txt file, checks
that all was read in correctly, then allocates a GameData list
on the heap. From here, all the player IDs are put into the new
list. Then, while no one has won, simulateDDGRound is called.
This function utilizes the functions of my circular_list, and
continually updates and removes players from the linked list.
It checks for the edge cases when the same random numbers are
chosen, there are no players, and the goose is picked again as
it. All steps are written to the ofstream output.