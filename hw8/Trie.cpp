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
	int cnt = 0;
	TrieNode* traverse = this->root->children[cnt];

	while (traverse != root) {
		if (traverse->letter == '$') {
			TrieNode* temp = traverse->parent;
			delete traverse;
			taverse = temp;
			if (cnt > 25) {
				temp->letter = '$';
				cnt = 0;
			}

			else cnt++;
		}
	}

	else {
		cnt = 0;
		traverse = traverse->children[cnt];
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

	// set the word to false, 'removing' it from the set of words
	traverse->inSet = false;

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
