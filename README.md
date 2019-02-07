# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

I USED THE CODE BUY WITH THE 10 POINT DEDUCTION.

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

Scrabble AI:
Both my AIs work in the same way, the only difference is 
CPUS will sort the priority queue by largest score whereas
CPUL does it by longest length.  I use backtracking to find
the valid words, cutting it when it's an invalid prefix. 
My AIs each have a strategy function.  All functions related
to the AIs can be found in CPUL.cpp/CPUL.h, and CPUS.cpp/CPUS.h.
Each function takes in the parameter of horizontal, so it can
run in each direction with one function.  YOU CAN RUN MY CODE
by the Makefile.

Not sure who is going to grade this, but the 104 teaching staff
has taught me so much this semster, patiently waded through my
code with me, and taught me so so much about coding in practice
and theory.  I have aboslutely loved this class, so thank you!