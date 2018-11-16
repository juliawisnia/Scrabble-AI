#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <climits>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}
	private:
		int height(Node<Key, Value>* root) const;
		void clearHelper(Node<Key, Value>* root);

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL;
	// TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
	// TODO
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if (mRoot == NULL) {
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
	}

	Node<Key, Value>* search = internalFind(keyValuePair.first);
	if (search != NULL) {
		search->setValue(keyValuePair.second);
		return;
	}
	else search = mRoot;

	while (search != NULL) {

		if (keyValuePair.first < search->getKey()) {
			if (search->getLeft() == NULL) {
				Node<Key, Value>* insertLeft = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, search);
				search->setLeft(insertLeft);
				return;
			}
			else search = search->getLeft();
		}
		else {
			if (search->getRight() == NULL) {
				Node<Key, Value>* insertRight = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, search);
				search->setRight(insertRight);
				return;
			}
			else search = search->getRight();
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	Node<Key, Value>* search = internalFind(key);
	// not in the tree
	if (search == NULL) return;
	// no children
	if (search->getRight() == NULL && search->getLeft() == NULL) {
		if (search == mRoot) {
			mRoot = NULL;
			delete search;
			return;
		}
		// search is the right child
		if (search->getKey() > search->getParent()->getKey()) {
			search->getParent()->setRight(NULL);
		}
		// search is the left child
		else {
			search->getParent()->setLeft(NULL);
		}
		delete search;
		return;
	}
	// one child
	else if (search->getRight() == NULL || search->getLeft() == NULL) {
		// has a right child
		if (search->getRight() != NULL) {
			// it's the root
			if (search == mRoot) {
				mRoot = search->getRight();
				mRoot->setParent(NULL);
				delete search;
				return;
			}
			// search is the right child
			if (search->getKey() > search->getParent()->getKey()) {
				search->getParent()->setRight(search->getRight());
				search->getRight()->setParent(search->getParent());
				delete search;
				return;
			}
			// search is the left child
			else {
				search->getParent()->setLeft(search->getRight());
				search->getRight()->setParent(search->getParent());
				delete search;
				return;
			}
		}
		// has a left child
		else {
			if (search == mRoot) {
				mRoot = search->getLeft();
				mRoot->setParent(NULL);
				delete search;
				return;
			}
			// search is the right child
			if (search->getKey() > search->getParent()->getKey()) {
				search->getParent()->setRight(search->getLeft());
				search->getLeft()->setParent(search->getParent());
				delete search;
				return;
			}
			// search is the left child
			else {
				search->getParent()->setLeft(search->getLeft());
				search->getLeft()->setParent(search->getParent());
				delete search;
				return;
			}
		}
	}
	// two children
	else {
		Node<Key, Value>* predecessor = search->getLeft();
		// predecessor is adjacent to search
		if (predecessor->getRight() == NULL) {
			// search is root
			if (search == mRoot) {
				predecessor->setRight(mRoot->getRight());
				mRoot->getRight()->setParent(predecessor);
				mRoot = predecessor;
				mRoot->setParent(NULL);
				delete search;
				return;
			}			
			// search is the right child
			if (search->getKey() > search->getParent()->getKey()) {
				search->getParent()->setRight(predecessor);
				predecessor->setParent(search->getParent());
				predecessor->setRight(search->getRight());
				search->getRight()->setParent(predecessor);
				delete search;
				return;
			}
			// search is left child
			else {
				search->getParent()->setLeft(predecessor);
				predecessor->setParent(search->getParent());
				predecessor->setRight(search->getRight());
				search->getRight()->setParent(predecessor);
				delete search;
				return;
			}
		}

		while (predecessor->getRight() != NULL) {
			predecessor = predecessor->getRight();
		}

		// search is root
		if (search == mRoot) {
			if (predecessor->getLeft() != NULL) {
				predecessor->getParent()->setRight(predecessor->getLeft());
				predecessor->getLeft()->setParent(predecessor->getParent());
			}
			else predecessor->getParent()->setRight(NULL);

			predecessor->setRight(mRoot->getRight());
			predecessor->setLeft(mRoot->getLeft()); 
			mRoot->getRight()->setParent(predecessor);
			mRoot->getLeft()->setParent(predecessor);
			mRoot = predecessor;
			mRoot->setParent(NULL);
			delete search;
			return;
		}

		// search is the right child
		if (search->getKey() > search->getParent()->getKey()) {
			if (predecessor->getLeft() != NULL) {
				predecessor->getParent()->setRight(predecessor->getLeft());
				predecessor->getLeft()->setParent(predecessor->getParent());
			}
			else predecessor->getParent()->setRight(NULL);

			search->getParent()->setRight(predecessor);
			predecessor->setParent(search->getParent());
			predecessor->setRight(search->getRight());
			predecessor->setLeft(search->getLeft());
			predecessor->getLeft()->setParent(predecessor);
			predecessor->getRight()->setParent(predecessor);
			delete search;
			return;
		}
		// search is left child
		else {
			if (predecessor->getLeft() != NULL) {
				predecessor->getParent()->setRight(predecessor->getLeft());
				predecessor->getLeft()->setParent(predecessor->getParent());
			}
			else predecessor->getParent()->setRight(NULL);

			search->getParent()->setLeft(predecessor);
			predecessor->setParent(search->getParent());
			predecessor->setRight(search->getRight());
			predecessor->setLeft(search->getLeft());
			predecessor->getLeft()->setParent(predecessor);
			predecessor->getRight()->setParent(predecessor);
			delete search;
			return;	
		}
	}
	return;
	// TODO
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* root) {
	if (root != NULL) {
		clearHelper(root->getLeft());
		clearHelper(root->getRight());
		remove(root->getKey());
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	clearHelper(mRoot);
	// TODO
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key, Value>* smallest = mRoot;
	while (smallest->getLeft() != NULL) {
		smallest = smallest->getLeft();
	}
	return smallest;
	// TODO
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	Node<Key, Value>* search = mRoot;
	while (search != NULL) {
		if (search->getKey() == key) return search;

		if (key < search->getKey()) {
			if (search->getLeft() == NULL) return NULL;
			else search = search->getLeft();
		}

		if (key > search->getKey()) {
			if (search->getRight() == NULL) return NULL;
			else search = search->getRight();
		}
	}
	return NULL;
	// TODO
}

/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* root) const {
	if (root == NULL) return 0;

	int l = height(root->getLeft());
	int r = height(root->getRight());
	if (l == -1 || r == -1) return -1;
	int comp = std::abs(l - r);
	if (comp > 1) return -1;
	else return std::max(l, r) + 1;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	int h = height(mRoot);
	if (h == -1) return false;
	return true;
}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
