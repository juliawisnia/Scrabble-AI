# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

You should grade everything in the hw1 folder (lowercase h).
For the flexCharManager, my implentation method was to create
a boolean array that was statically allocated, and was the same
size as the buffer.  In this array, if there is a char in 
a spot, it will go true (everything is initialized to false).
Then, for allocate_chars I loop through this array to look for
the first empty spot that will allow for all the necessary
characters to fill it.