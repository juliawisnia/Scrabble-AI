#include "selection_sort.h"
#include <iostream>

Item* findMin(Item * head) {
	if (!head) return nullptr; //no elements
	if (!head->next) return head; //only one element

	Item* search=head;
	Item* min_item=head;

	//get value of first element for comparison
	int min=head->getValue();

	//traverse entire list
	while (search->next) {
		search=search->next;
		if ((search->getValue())<=min) {
			min=search->getValue();
			min_item=search;
		}
	}
	//return pointer to the item with min value
	return min_item;
}

void recurse(Item* curr) {
	//everything before curr is sorted at all times
	Item* min=findMin(curr);

	if ((min==curr && !curr->next) || !min) {
		return;
	}

	//if curr is at min, advance and recurse after that
	if (min==curr && curr->next) {
		recurse (curr->next);
		return;
	}

	//min is not the last element
	if (min->next) {
		min->prev->next=min->next;
		min->next->prev=min->prev;
	}

	//min is the last element
	else {
		min->prev->next=nullptr;
	}

	//curr is first element
	if (!curr->prev) {
		min->prev=nullptr;
		curr->prev=min;
		min->next=curr;
		recurse (curr);
	}

	//curr is in the middle
	else {
		min->prev=curr->prev;
		curr->prev->next=min;
		curr->prev=min;
		min->next=curr;
		recurse (curr);
	}
}

Item* LLSelectionSort(Item * head) {
	//no Items
	if (!head) return nullptr;

	//only one Item
	if (!head->next) return head;

	Item* curr=head;
	//take val of head for comparison
	Item* min=findMin(head);
	//advance curr if the head is min of entire list
	if (min==head) curr=head->next;

	recurse(curr);

	return min;
}