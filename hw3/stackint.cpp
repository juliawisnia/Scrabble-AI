#include <iostream>
#include "stackint.h"

StackInt::StackInt() {
}

StackInt::~StackInt() {
}

bool StackInt::empty() const {
	if (list.empty()) return true;
	return false;
}

void StackInt::push(const int& val) {
	list.push_back(val);
}

int StackInt::top() const {
	int val=list.get(list.size()-1);
	return val;
}

void StackInt::pop() {
	list.remove(list.size()-1);
}