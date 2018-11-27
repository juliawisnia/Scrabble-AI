# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

I WILL BE USING THE GIVEN STARTER CODE WITH THE 10
POINT DEDUCTION.

Trie.cpp:
My Trie is implemented by creating a root node with
the letter '$', and then setting all children to nullptr.
As I insert to the Trie, each time I add to the set I
dynamically allocate a new TrieNode, update all pointers
and letters, and set all its children to nullptr, too.
My destructor is adapted from binary search, so it is a 
post-order clear that recursively calls its helper function
until all memory has been deleted.

Trie.h:
I implemented several helper functions, all of which are
private and they are described in this file.