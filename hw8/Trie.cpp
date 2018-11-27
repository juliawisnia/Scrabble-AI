#include "Trie.h"
#include <algorithm>

TrieSet::TrieSet() {
	TrieNode* _root = new TrieNode;
	_root->letter = '&';
	_root->inSet = false;
	_root->parent = nullptr;

	this->root = _root;
	insertChildren(this->root);
}

TrieSet::~TrieSet() {
	helper(root->children[0]);
}

void TrieSet::helper(TrieNode* node) {
	if (node == root && !hasChildren(node)) {
		deleteChildren(root);
		delete root;
		return;
	}

	// if it has no children, delete it's children and go to it's parent
	if (!hasChildren(node)) {
		TrieNode* temp = node->parent;
		deleteChildren(node);
		helper(temp);
	}

	// move on to the 'first' sequential child
	else {
		TrieNode* temp = node->parent;
		for (size_t i = 0; i < node->children.size(); ++i) {
			helper(node->children[i]);
		}
		helper(temp);
	}
}

void TrieSet::insert (std::string input) {
	TrieNode* traverse = this->root;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	for (size_t i = 0; i < input.size(); i++) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		// move onto the next node, always guaranteed to have a '$' or char so won't segfault
		traverse = traverse->children[index];
		
		// new unexplored path
		if (traverse->letter == '$') {
			traverse->letter = input[i];
			insertChildren(traverse);
		}
	}

	// set the word to true
	traverse->inSet = true;
}

void TrieSet::remove (std::string input) {
	TrieNode* traverse = this->root;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	// make sure that the word is in it
	for (size_t i = 0; i < input.size(); ++i) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		// move onto the next node, always guaranteed to have a '$' or char so won't segfault
		traverse = traverse->children[index];

		// word is not complete and is thus not in the set
		if (traverse->letter == '$') {
			return;
		}
	}

	deleteChildren(traverse);

}

TrieNode* TrieSet::prefix (std::string px) {
	TrieNode* traverse = this->root;
	std::transform(px.begin(), px.end(), px.begin(), ::tolower);

	for (size_t i = 0; i < px.size(); ++i) {
		// convert to ASCII indexing
		int index = px[i] - 97;
		// move onto the next node, always guaranteed to have a '$' or char so won't segfault
		traverse = traverse->children[index];
		
		// word is not complete and is thus not in the set
		if (traverse->letter == '$') {
			return NULL;
		}
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

bool TrieSet::hasChildren (TrieNode* node) {
	for (size_t i = 0; i < node->children.size(); i++) {
		if (node->children[i] != '$') return true;
	}
	return false;
}

void TrieSet::deleteChildren (TrieNode* node) {
	while (!hasChildren(node) && node != this->root) {
		node->letter = '$';
		node->inSet = false;
		for (size_t i = 0; i < node->children.size(); ++i) {
			delete node->children[i];
		}
		node = node->parent;
	}
}