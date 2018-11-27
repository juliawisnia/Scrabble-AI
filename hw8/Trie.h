#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <algorithm>
#include <stack>
#include <set>
#include <iostream>

struct TrieNode {
  char letter; // what letter it is holding
  bool inSet;   // Is this node the end of a string in your dictionary?
  TrieNode *parent;
  TrieNode *children[26]; // one child for each letter of the alphabet.
};

class TrieSet {
  public:

    TrieSet (); // a constructor for an empty trie
    ~TrieSet (); // destructor

    void insert (std::string input);
    /* Add this string to the set.
    Do nothing if the string is already in the set. */

    void remove (std::string input);
    /* Removes this string from the set.
    Do nothing if the string is not already in the set. */

    TrieNode* prefix (std::string px);
    /* returns the TrieNode matching the provided string, or returns NULL 
    if it is not the prefix of a word in the Trie. */

    // prints trieSet for debugging purposes
    void printSet();

  private:
    size_t childrenSize;
    TrieNode* root;
    // function to insert 26 new children initialized with '$'
    void insertChildren(TrieNode* node);

    // returns false if all children are '$' meaning the end of a word
    bool hasChildren (TrieNode* node);

    // deletes all children of node if they are all '$', then moves on until
    // it reaches a node with children initialized to letters or the root
    void deleteChildren (TrieNode* node);

    // helper function that recursively deallocates all memory from the set
    void clearHelper(TrieNode* traverse);

    // returns true iff node is the root
    bool isRoot(TrieNode* node);

};

#endif