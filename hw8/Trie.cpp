#include "Trie.h"

TrieSet::TrieSet() {
	childrenSize = 26;
	TrieNode* _root = new TrieNode;
	_root->letter = '$';
	_root->inSet = false;
	_root->parent = nullptr;

	this->root = _root;
	insertChildren(this->root);
}

TrieSet::~TrieSet() {
	clearHelper(this->root);
}

void TrieSet::clearHelper(TrieNode* traverse) {
	if (traverse != nullptr) {
		for (size_t i = 0; i < childrenSize; i++) {
			if (traverse->children[i] != nullptr) clearHelper(traverse->children[i]);
		}
		delete traverse;
	}
}

// THIS WAS TAKEN FROM JAMIE'S SCRABBLE CODE. I AM USING THE CODE BUY
inline void makeLowercase(std::string & toConvert) {
	for(size_t index = 0; index < toConvert.length(); ++index) {
		toConvert[index] = (char)std::tolower(toConvert[index]);
	}
}

void TrieSet::insert(std::string input) {
	makeLowercase(input);
	TrieNode* traverse = prefix(input);

	// if it's already in the set, just set this prefix to true and return
	if (traverse != nullptr) {
		traverse->inSet = true;
		return;
	}

	traverse = this->root;
	for (size_t i = 0; i < input.size(); i++) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		
		// new path
		if (traverse->children[index] == nullptr) {
			TrieNode* insertChild = new TrieNode;
			insertChild->parent = traverse;
			insertChild->letter = input[i];
			insertChild->inSet = false;

			traverse->children[index] = insertChild;
			insertChildren(traverse->children[index]);
		}
		// move onto next node to traverse
		traverse = traverse->children[index];
	}

	// set the word to true
	traverse->inSet = true;
}

void TrieSet::remove(std::string input) {
	makeLowercase(input);
	// make sure the word is in the function
	TrieNode* traverse = prefix(input);
	if (traverse == nullptr) return;

	// set it to false, then see if there is any memory that we can deallocate
	traverse->inSet = false;
	deleteChildren(traverse);
}

TrieNode* TrieSet::prefix(std::string px) {
	makeLowercase(px);
	TrieNode* traverse = this->root;

	for (size_t i = 0; i < px.size(); i++) {
		// convert to ASCII indexing
		int index = px[i] - 97;
		// no child with that letter, word is not in set
		if (traverse->children[index] == nullptr) return nullptr;
		
		traverse = traverse->children[index];
	}

	// return the final letter where the prefix is
	return traverse;
}

void TrieSet::insertChildren(TrieNode* node) {
	for (size_t i = 0; i < childrenSize; i++) {
		node->children[i] = nullptr;
	}	
}

bool TrieSet::hasChildren(TrieNode* node) {
	for (size_t i = 0; i < childrenSize; i++) {
		if (node->children[i] != nullptr) return true;
	}
	return false;
}

void TrieSet::deleteChildren(TrieNode* node) {
	while (!hasChildren(node) && !isRoot(node)) {
		// if this is a word, we can't delete anymore memory so return
		if (node->inSet) return;

		TrieNode* temp = node->parent;
		int index = node->letter - 97;
		// set child to null before we delete it
		temp->children[index] = nullptr;
		delete node;
		node = temp;
	}
}

bool TrieSet::isRoot(TrieNode* node) {
	if (node->letter == '$') return true;
	return false;
}