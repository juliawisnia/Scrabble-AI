#include "Trie.h"
#include <algorithm>

TrieSet::TrieSet() {
	TrieNode* _root = new TrieNode;
	_root->letter = '&';
	_root->inSet = false;
	_root->parent = nullptr;

	this->root = _root;
	insertChildren(root);
}

TrieSet::~TrieSet() {

}

void TrieSet::insert (std::string input) {
	TrieNode* traverse = root;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	for (size_t i = 0; i < input.size(); i++) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		// new unexplored path
		if (traverse->children[index] == '$') {
			traverse->children[index]->letter = input[i];
			insertChildren(traverse->children[index]);
		}
		// move onto the next node
		traverse = traverse->children[index];
	}

	// set the word to true
	traverse->inSet = true;
}

void TrieSet::remove (std::string input) {
	TrieNode* traverse = root;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	for (size_t i = 0; i < input.size(); ++i) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		// word is not complete and is thus not in the set
		if (traverse->children[index] == '$') {
			return;
		}
		// move onto the next node
		traverse = traverse->children[index];
	}

	// set the word to false, 'removing' it from the set of words
	traverse->inSet = false;

}

TrieNode* TrieSet::prefix (std::string px) {
	TrieNode* traverse = root;
	std::transform(px.begin(), px.end(), px.begin(), ::tolower);

	for (size_t i = 0; i < px.size(); ++i) {
		// convert to ASCII indexing
		int index = px[i] - 97;
		// word is not complete and is thus not in the set
		if (traverse->children[index] == '$') {
			return NULL;
		}
		// move onto the next node
		traverse = traverse->children[index];
	}

	// return the final letter where the prefix is
	return traverse;
}

void TrieSet::insertChildren (TrieNode* node) {
	for (size_t i = 0; i < node->children.size(); ++i) {
		TrieNode* insertChild = new TrieNode;
		insertChild->letter = '$';
		insertChild->inSet = false;
		insertChild->parent = node;
		node->children[i] = insertChild;
	}	
}
