#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <climits>
#include <vector>

#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value> 
{
	protected:
		/*perform a left rotation at the parameter node.If r has no right child, 
		this function should do nothing. This should run in constant time.*/
		void leftRotate(Node<Key, Value>* z);
		/*perform a right rotation at the parameter node. If r has no left child, 
		this function should do nothing. This should run in constant time.*/
		void rightRotate(Node<Key, Value>* node);
	public:
		/*given another BST, checks that the set of keys in both trees are identical. 
		This should run in O(n) time, where n is the number of nodes in the tree.*/
		bool sameKeys(const rotateBST& t2) const;
		/*given another BST t2, if t2 contains the same keys as the one for this, transform 
		the BST t2 into the one for this using only rotations. If the BST t2 does not have the same keys as this, 
		this function should do nothing and neither BST should be modified.*/
		void transform(rotateBST& t2) const;
	private:
		void InOrder(std::vector<Key>& result, Node<Key, Value>* start) const;
		void allRightRotates(rotateBST& t2);
		void leftRotateToRoot(rotateBST& t2);
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* z) {
	// has no right child
	if (z->getRight() == NULL) return;

	bool rotateRoot = false;
	bool rotateLeftChild = false;
	if (z == this->mRoot) rotateRoot = true;
	else if (z->getKey() < z->getParent()->getKey()) rotateLeftChild = true;

	Node<Key, Value>* y = z->getRight();
	Node<Key, Value>* t1 = y->getLeft();

	// y node
	y->setLeft(z);

	if (rotateRoot) {
		y->setParent(NULL);
		this->mRoot = y;
	}

	else {
		y->setParent(z->getParent());
		if (rotateLeftChild) y->getParent()->setLeft(y);
		else z->getParent()->setRight(y);
	}

	// z node
	z->setParent(y);
	if (t1 != NULL) {
		t1->setParent(z);
		z->setRight(t1);
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* z) {
	if (z->getLeft() == NULL) return;

	bool rotateRoot = false;
	bool rotateLeftChild = false;
	if (z == this->mRoot) rotateRoot = true;
	else if (z->getKey() < z->getParent()->getKey()) rotateLeftChild = true;

	Node<Key, Value>* y = z->getLeft();
	Node<Key, Value>* t2 = y->getRight();

	// y node
	y->setRight(z);

	if (rotateRoot) {
		y->setParent(NULL);
		this->mRoot = y;
	}

	else {
		y->setParent(z->getParent());
		if (rotateLeftChild) y->getParent()->setLeft(y);
		else z->getParent()->setRight(y);
	}	

	// z node
	z->setParent(y);
	if (t2 != NULL) {
		t2->setParent(z);
		z->setLeft(t2);
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::InOrder(std::vector<Key>& result, Node<Key, Value>* start) const {
    if(start->getLeft() != NULL) {
        InOrder(result, start->getLeft());
    }

    result.push_back(start->getKey());

    if(start->getRight() != NULL) {
        InOrder(result, start->getRight());
    }
}

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const {
	std::vector<Key> thisResult;
	std::vector<Key> thatResult;
	InOrder(thisResult, this->mRoot);
	InOrder(thatResult, t2.mRoot);

	if (thisResult == thatResult) return true;
	else return false;

}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const {
	// don't have the same keys
	if (!sameKeys(t2)) return;

	allRightRotates(t2);

}

template <typename Key, typename Value>
void rotateBST<Key, Value>::allRightRotates(rotateBST& t2) {
	// base case, there are no left children
	if (t2.mRoot->getLeft() == NULL) return;

	while (t2.mRoot->getLeft() != NULL) {
		rightRotate(t2.mRoot);
	}
	allRightRotates(t2);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotateToRoot(rotateBST& t2) {
	while (t2.mRoot != this->mRoot) {
		leftRotate(t2.mRoot);
	}
}