#include "selection_sort.h"
#include <iostream>

Item* findMin(Item * head) {
	if (!head) return nullptr; //no elements

	Item* search=head;
	Item* min_item=nullptr;
	int min=search->getValue();

	if (!search->next) return head; //only one element

	while (search->next) {
		search=search->next;
		if (search->getValue()<min) {
			min=search->getValue();
			min_item=search;
		}
	}
	return min_item;
}

Item* LLSelectionSort(Item * head) {
	if (!head) return nullptr;

	if (!head->next) return head;

	Item* curr=head;
	Item* min=findMin(head);
	if (min==head) curr=head->next;

	recurse(curr);

	return min;
}

void recurse(Item* curr) {
	Item* min=findMin(curr);

	if ((min==curr && !curr->next) || !min) {
		return;
	}

	//if min is at curr, advance and recurse after that
	if (min==curr && curr->next) recurse (curr->next);

	//min is not the last element
	if (min->next) {
		min->prev->next=min->next;
		min->next->prev=min->prev;
	}

	//min is the last element
	else {
		min->prev->next=nullptr;
	}

	if (!curr->prev) {
		min->prev=nullptr; //curr is first element
		curr->prev=min;
		min->next=curr;
		recurse (curr);
	}

	else {
		min->prev=curr->prev;
		curr->prev->next=min;
		curr->prev=min;
		min->next=curr;
		recurse (curr); //don't advance curr
	}
}