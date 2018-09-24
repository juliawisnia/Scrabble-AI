#include <iostream>
#include "circular_list_int.h"
#include <string>

CircularListInt::Item * CircularListInt::findItem(size_t index) const {
	Item* found=this->head;
	for (size_t i=0; i<index; i++) {
		found=found->next;
	}
	return found;
}

CircularListInt::CircularListInt() {
}

CircularListInt::~CircularListInt() {
	//while the list is not empty
	while (!empty()) {
		remove(count);
	}
	delete this->head;
}

int CircularListInt::get(size_t index) const {
	if (empty()) return 0;	

	size_t len=size();

	//enables "wrapping" of index
	if (index>=len) {
		index=index%len;
	}
	//item is at head
	if (index==0) return this->head->value;

	//traverse until you reach the index
	Item* val=this->head;
	for (size_t i=0; i<index; i++) {
		val=val->next;
	}

	return val->value;
}

size_t CircularListInt::size() const {
	if (empty()) return 0;

	return this->count;
}

bool CircularListInt::empty() const {
	if (!this->head) return true;
	return false;
}

void CircularListInt::push_back(int value) {
	Item* add=new Item(value);
	size_t len=size();

	(this->count)++; //add to size after checking

	//if list is empty
	if (len==0) {
		head=add;
		add->prev=add;
		add->next=add;
		return;
	}

	//update pointers on last and new elements
	add->prev=this->head->prev;
	add->next=this->head;

	this->head->prev->next=add;
	this->head->prev=add;
}

void CircularListInt::set(size_t index, int value) {
	if (empty()) return;

	size_t len=size();
	Item* traverse=this->head;

	//enable "wrapping"
	if (index>=len) {
		index=index%len;
	}

	//element is at head
	if (index==0) {
		this->head->value=value;
		return;
	}

	//traverse until you reach the element
	for (size_t i=0; i<index; i++) {
		traverse=traverse->next;
	}

	traverse->value=value;

}

void CircularListInt::remove(size_t index) {
	if (empty()) return;

	size_t len=size();
	(this->count)--; //decrement size after checking

	//delete element memory
	if (len==1) {
		delete this->head;
		this->head=nullptr;
		return;
	}

	//enable "wrapping"
	if (index>=len) {
		index=index%len;
	}

	Item* traverse=this->head;
	//traverse list until you reach the index
	for (size_t i=0; i<index; i++) {
		traverse=traverse->next;
	}

	//element is at head
	if (index==0) {
		this->head=this->head->next;
	}
	//update pointers of surrounding
	traverse->next->prev=traverse->prev;
	traverse->prev->next=traverse->next;

	//delete memory of item
	delete *&traverse;
}