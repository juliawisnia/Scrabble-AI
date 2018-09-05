# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

You should grade everything in the hw1 folder (lowercase h) 
EXCEPT the test.cpp files, which I just used to test my code.
For simpleCharManager, my implementation looped through the 
buffer looking for null characters, and when it hit one it
tested if there were enough spaces to hold all of n, if so,
it would return the pointer to that space.
For the flexCharManager, my implentation method was to create
a boolean array that was statically allocated, and was the same
size as the buffer.  In this array, if there is a char in 
a spot, it will go true (everything is initialized to false).
Then, for allocate_chars I loop through this array to look for
the first empty spot that will allow for all the necessary
characters to fill it.  It would return the pointer to the
memblock, pointing to the physical_location in the buffer.
My driver cases test memory allocation and deallocation, and
test the fragmentation examples in my flexCharManager.