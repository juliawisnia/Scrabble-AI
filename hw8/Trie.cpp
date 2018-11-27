#include "Trie.h"

TrieSet::TrieSet() {
	childrenSize = 26;
	TrieNode* _root = new TrieNode;
	_root->letter = '&';
	_root->inSet = false;
	_root->parent = nullptr;

	this->root = _root;
	insertChildren(this->root);
}

TrieSet::~TrieSet() {
	//clearHelper(this->root);
}

void TrieSet::clearHelper(TrieNode* traverse) {
	if (traverse != NULL) {
		for (size_t i = 0; i < childrenSize; i++) {
			clearHelper(traverse->children[i]);
		}
		delete traverse;
	}
}

void TrieSet::insert (std::string input) {
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	TrieNode* traverse = prefix(input);

	// if it's already in the set, just set this prefix to true and return
	if (traverse != NULL) {
		traverse->inSet = true;
		return;
	}

	traverse = this->root;
	for (size_t i = 0; i < input.size(); i++) {
		// convert to ASCII indexing
		int index = input[i] - 97;
		// move onto the next node, always guaranteed to have a '$' or char so won't segfault
		traverse = traverse->children[index];
		
		// new path
		if (traverse->letter == '$') {
			traverse->letter = input[i];
			insertChildren(traverse);
		}
	}

	// set the word to true
	traverse->inSet = true;
}

void TrieSet::remove (std::string input) {
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	// make sure the word is in the function
	TrieNode* traverse = prefix(input);
	if (traverse == NULL) return;

	// set it to false, then see if there is any memory that we can deallocate
	traverse->inSet = false;
	deleteChildren(traverse);
	return;
}

TrieNode* TrieSet::prefix (std::string px) {
	TrieNode* traverse = this->root;
	std::transform(px.begin(), px.end(), px.begin(), ::tolower);

	for (size_t i = 0; i < px.size(); i++) {
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
	for (size_t i = 0; i < childrenSize; i++) {
		TrieNode* insertChild = new TrieNode;
		insertChild->letter = '$';
		insertChild->inSet = false;
		insertChild->parent = node;
		node->children[i] = insertChild;
	}	
}

bool TrieSet::hasChildren (TrieNode* node) {
	for (size_t i = 0; i < childrenSize; i++) {
		if (node->children[i]->letter != '$') return true;
	}
	return false;
}

void TrieSet::deleteChildren (TrieNode* node) {
	while (!hasChildren(node) && !isRoot(node)) {
		// if this is a word, we can't delete anymore memory so return
		if (node->inSet) return;
		// otherwise set this letter to the '$' and delete its children
		node->letter = '$';
		// delete all it's children's memory
		for (size_t i = 0; i < childrenSize; i++) {
			delete node->children[i];
		}
		node = node->parent;
	}
}

bool TrieSet::isRoot(TrieNode* node) {
	if (node->letter == '&') return true;
	return false;
}

void TrieSet::printSet() {
	TrieNode* traverse = this->root->children[0];
	std::cout << traverse->letter << traverse->children[0]->letter << traverse->children[3]->children[0]->letter << std::endl;
// //	TrieNode* traverse = this->root;
// 	std::cout << this->root->letter << std::endl;
// 	for (size_t i = 0; i < 26; i++) {
// 		if (this->root->children[i]->letter != '$') std::cout << i << " " << root->children[i]->letter << " ";
// 	}
// 	std::cout << std::endl;
// 	for (size_t i = 0; i < 26; i++) {
// 		if (this->root->children[0]->children[i]->letter != '$') std::cout << i << " " << root->children[0]->children[i]->letter << " ";
// 	}
// 	std::cout << std::endl;
// 	for (size_t i = 0; i < 26; i++) {
// 		if (this->root->children[0]->children[3]->children[i]->letter != '$') std::cout << i << " " << root->children[0]->children[3]->children[i]->letter << " ";
// 	}
// 	std::cout << "___________________" << std::endl;

}