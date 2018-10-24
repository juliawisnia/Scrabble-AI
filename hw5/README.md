# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

Cave Exploration:
In order to implement my cave.cpp, the underlying data
structure I used was a stack.  Once I have determined that
the string is valid, I compare the first and second elements.
If they are complements of each other (N & S or E & W), meaning
that when they are next to each other they "cancel out", and the
rope is not affected, I simply continue and do nothing with the
stack.  If this is not the case, I push to the stack.  Once I have
iterated through the string, I go back to the stack, and look
for adjacent complements again.  If I find a pair, I pop them both,
meaning that the only way for the rope to be rolled up in the end
is if the stack is empty, otherwise it is not rolled up.

Write a Comparator
My comparator converts all letters to uppercase, then all characters
to their ASCII values.  From here, it just checks the range for upper-
case characters, and assigns based on this, and the same with numbers.
If it encounters a character other than these, it simply sets its value
to zero, essentially not counting it.

k-Way MergeSort
To implement MergeSort, I used a vector of pairs that stored the
first and last indicies of the partitions I made on each call to 
mergeSort, (in my case, the helper function multMergeSort).  If 
there were less than k elements between these indicies, I called
selectionSort on that part of the array, otherwise I called 
multMergeSort until this condition was met.  After all partitions
were at their lowest values, I make one call to merge.  In merge,
the inicies array essentially acts as the pointers for each
partition.  I repeatedly find the min of these "pointers," then
push that min to a temp vector.  Once this is done, I increment
the first element of the pair where the min element was found.  Once
the frist element of the pair is greater than the second, I erase
that pair from the index array, because all the elements in its range
have been found as mins.  This process stops only once the index
array is empty, meaning that all min elements have been found and
placed in their proper place.  I then fill myArray with temp, starting
at the lowest index from the index array and up to the highest.

Fatalist Hypothesis
In order to test this hypothesis, I must test the two conditions.
First, I sort by the greater-than-or-equal-to condition of each 
statement, then I go up this sorted array and make sure that
the next grade is strictly greater than its previous.  If this
is false at anytime, the function immediately returns false.
I then sort by the other condition, and do the same for the other grade.
If both of these complete without returning false, then the hypothesis
is true, and thus the function returns true.  I implemented a comparator
to compare the second elements of the pair, and used STL's sort.

The answers to problem 2 & problem 4(c) are in my hw5.txt.