#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
    void deleteNode(AVLNode<Key, Value>* search);
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    //std::cout << "avl insert" << std::endl;
    // if node is already in tree, just update values and move on
    Node<Key, Value>* temp = this->internalFind(keyValuePair.first);
    AVLNode<Key, Value>* search = dynamic_cast<AVLNode<Key, Value>*>(temp);

    if (search != NULL) {
        search->setValue(keyValuePair.second);
        return;
    }

    // if it's the empty tree, insert new AVLNode
    if (this->mRoot == NULL) {
        AVLNode<Key, Value>* add = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        (this->mRoot) = add;
        return;
    }
    // adapted BST insert, just now inserting AVLNodes
    else search = dynamic_cast<AVLNode<Key, Value>*>(this->mRoot);

    while (search != NULL) {
        if (keyValuePair.first < search->getKey()) {
            if (search->getLeft() == NULL) {
                AVLNode<Key, Value>* insertLeft = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, search);
                search->setLeft(insertLeft);
                // set to the child so that we can traverse from the newly inserted node
                search = search->getLeft();
                break;
            }
            else search = search->getLeft();
        }
        else {
            if (search->getRight() == NULL) {
                AVLNode<Key, Value>* insertRight = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, search);
                search->setRight(insertRight);
                search = search->getRight();
                break;
            }
            else search = search->getRight();
        }
    }

    // update all heights until an unbalanced tree is found, balance it then return
    while (search->getParent() != NULL) {
        search = search->getParent();

        int heightLeft = 0;
        int heightRight = 0;

        AVLNode<Key, Value>* leftChild = search->getLeft();
        AVLNode<Key, Value>* rightChild = search->getRight();
        // plus one, because each node is initialized w val of 0, but an empty tree has val 0
        if (leftChild != NULL) {
            heightLeft = leftChild->getHeight() + 1;
        }
        if (rightChild != NULL) {
            heightRight = rightChild->getHeight() + 1;
        }

        // unbalanced, do rotations
        if (std::abs(heightLeft - heightRight) > 1) {
            // going to rotate this node, will have one less child
            int prevHeight = search->getHeight();
            int newHeight = prevHeight - 1;
            search->setHeight(newHeight);
            // left child is heavier, do a right rotate
            if (heightLeft > heightRight) {
                bool zigzag = false;
                // zig-zag rotation
                int zagRightHeight = 0;
                int zagLeftHeight = 0;
                if (leftChild->getRight() != NULL) zagRightHeight = leftChild->getRight()->getHeight() + 1;
                if (leftChild->getLeft() != NULL) zagLeftHeight = leftChild->getLeft()->getHeight() + 1;

                if (zagRightHeight > zagLeftHeight) {
                    zigzag = true;
                    this->leftRotate(leftChild);
                }

                this->rightRotate(search);
                // search will become child, dec by one
                int prevHeight = search->getHeight();
                int newHeight = prevHeight - 1;
                search->setHeight(newHeight);

                if (zigzag) { 
                    // parent will increase by one
                    prevHeight = search->getParent()->getHeight();
                    newHeight = prevHeight + 1;
                    search->getParent()->setHeight(newHeight);  

                    // guaranteed to be left child, will decrease by one
                    prevHeight = search->getParent()->getLeft()->getHeight();
                    newHeight = prevHeight - 1;
                    search->getParent()->getLeft()->setHeight(newHeight);              
                }

                return;
            }
            // right child is heavier, do a left rotate
            else {
                bool zigzag = false;
                // zig-zag rotation
                int zagRightHeight = 0;
                int zagLeftHeight = 0;
                if (rightChild->getRight() != NULL) zagRightHeight = rightChild->getRight()->getHeight() + 1;
                if (rightChild->getLeft() != NULL) zagLeftHeight = rightChild->getLeft()->getHeight() + 1;

                if (zagRightHeight < zagLeftHeight) {
                    zigzag = true;
                    this->rightRotate(leftChild);
                }
                this->leftRotate(search);
                // search will become child, dec by one
                int prevHeight = search->getHeight();
                int newHeight = prevHeight - 1;
                search->setHeight(newHeight);

                if (zigzag) { 
                    // parent will increase by one
                    prevHeight = search->getParent()->getHeight();
                    newHeight = prevHeight + 1;
                    search->getParent()->setHeight(newHeight);  

                    // guaranteed to be right child, will decrease by one
                    prevHeight = search->getParent()->getRight()->getHeight();
                    newHeight = prevHeight - 1;
                    search->getParent()->getRight()->setHeight(newHeight);              
                }
                return;
            }
        }
        // if not unbalanced, increase height because it has a new node
        else {
            int prevHeight = search->getHeight();
            int newHeight = prevHeight + 1;
            search->setHeight(newHeight);
        }
    }


    // TODO
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    Node<Key, Value>* temp = this->internalFind(key);
    AVLNode<Key, Value>* nodeToDelete = dynamic_cast<AVLNode<Key, Value>*>(temp);

    // key is not in the tree
    if (nodeToDelete == NULL) return;

    this->deleteNode(nodeToDelete);

    Node<Key, Value>* tempSearch = this->getSmallestNode();
    AVLNode<Key, Value>* search = dynamic_cast<AVLNode<Key, Value>*>(tempSearch);

        while (search->getParent() != NULL) {
        search = search->getParent();

        int heightLeft = 0;
        int heightRight = 0;

        AVLNode<Key, Value>* leftChild = search->getLeft();
        AVLNode<Key, Value>* rightChild = search->getRight();
        // plus one, because each node is initialized w val of 0, but an empty tree has val 0
        if (leftChild != NULL) {
            heightLeft = leftChild->getHeight() + 1;
        }
        if (rightChild != NULL) {
            heightRight = rightChild->getHeight() + 1;
        }

        // unbalanced, do rotations
        if (std::abs(heightLeft - heightRight) > 1) {
            // going to rotate this node, will have one less child
            int prevHeight = search->getHeight();
            int newHeight = prevHeight - 1;
            search->setHeight(newHeight);
            // left child is heavier, do a right rotate
            if (heightLeft > heightRight) {
                bool zigzag = false;
                // zig-zag rotation
                int zagRightHeight = 0;
                int zagLeftHeight = 0;
                if (leftChild->getRight() != NULL) zagRightHeight = leftChild->getRight()->getHeight() + 1;
                if (leftChild->getLeft() != NULL) zagLeftHeight = leftChild->getLeft()->getHeight() + 1;

                if (zagRightHeight > zagLeftHeight) {
                    zigzag = true;
                    this->leftRotate(leftChild);
                }

                this->rightRotate(search);
                // search will become child, dec by one
                int prevHeight = search->getHeight();
                int newHeight = prevHeight - 1;
                search->setHeight(newHeight);

                if (zigzag) { 
                    // parent will increase by one
                    prevHeight = search->getParent()->getHeight();
                    newHeight = prevHeight + 1;
                    search->getParent()->setHeight(newHeight);  

                    // guaranteed to be left child, will decrease by one
                    prevHeight = search->getParent()->getLeft()->getHeight();
                    newHeight = prevHeight - 1;
                    search->getParent()->getLeft()->setHeight(newHeight);              
                }

            }
            // right child is heavier, do a left rotate
            else {
                bool zigzag = false;
                // zig-zag rotation
                int zagRightHeight = 0;
                int zagLeftHeight = 0;
                if (rightChild->getRight() != NULL) zagRightHeight = rightChild->getRight()->getHeight() + 1;
                if (rightChild->getLeft() != NULL) zagLeftHeight = rightChild->getLeft()->getHeight() + 1;

                if (zagRightHeight < zagLeftHeight) {
                    zigzag = true;
                    this->rightRotate(leftChild);
                }
                this->leftRotate(search);
                // search will become child, dec by one
                int prevHeight = search->getHeight();
                int newHeight = prevHeight - 1;
                search->setHeight(newHeight);

                if (zigzag) { 
                    // parent will increase by one
                    prevHeight = search->getParent()->getHeight();
                    newHeight = prevHeight + 1;
                    search->getParent()->setHeight(newHeight);  

                    // guaranteed to be right child, will decrease by one
                    prevHeight = search->getParent()->getRight()->getHeight();
                    newHeight = prevHeight - 1;
                    search->getParent()->getRight()->setHeight(newHeight);              
                }

            }
        }
        // if not unbalanced, increase height because it has a new node
        else {
            int prevHeight = search->getHeight();
            int newHeight = prevHeight + 1;
            search->setHeight(newHeight);
        }
    }
   // TODO
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::deleteNode(AVLNode<Key, Value>* search) {
    // no children
    if (search->getRight() == NULL && search->getLeft() == NULL) {
        if (search == this->mRoot) {
            this->mRoot = NULL;
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
            if (search == this->mRoot) {
                this->mRoot = search->getRight();
                this->mRoot->setParent(NULL);
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
            if (search == this->mRoot) {
                this->mRoot = search->getLeft();
                this->mRoot->setParent(NULL);
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
            if (search == this->mRoot) {
                predecessor->setRight(this->mRoot->getRight());
                this->mRoot->getRight()->setParent(predecessor);
                this->mRoot = predecessor;
                this->mRoot->setParent(NULL);
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
        if (search == this->mRoot) {
            if (predecessor->getLeft() != NULL) {
                predecessor->getParent()->setRight(predecessor->getLeft());
                predecessor->getLeft()->setParent(predecessor->getParent());
            }
            else predecessor->getParent()->setRight(NULL);

            predecessor->setRight(this->mRoot->getRight());
            predecessor->setLeft(this->mRoot->getLeft()); 
            this->mRoot->getRight()->setParent(predecessor);
            this->mRoot->getLeft()->setParent(predecessor);
            this->mRoot = predecessor;
            this->mRoot->setParent(NULL);
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
}
/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
