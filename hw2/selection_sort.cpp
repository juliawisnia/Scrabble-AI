#include "selection_sort.h"
#include <iostream>

Item* findMin(Item * head) {
	if (!head) return nullptr;

	Item* search=head->next;
	Item* min_item=nullptr;
	int min=10000;

	while (search!=nullptr) {
		if (search->getValue()<min) {
			min=search->getValue();
			min_item=search;
		}
		search=search->next;
	}

	return min_item;
}

Item* LLSelectionSort(Item * head) {
	if (!head) return nullptr;

	Item* smallest=findMin(head);
	head=prepend(head, smallest);

	Item* search=head->next;
	Item* item=nullptr;

	while(search!=nullptr) {
		item=findMin(search);
		search=prepend(search, item);
		search=search->next;
	}

	return head;
}

Item* prepend(Item* head, Item* smallest) {
	Item* temp=smallest;

	temp->prev->next=head;
	temp->next->prev=head;

	head=smallest;
	head->next->prev=smallest;
	smallest->prev=nullptr;

	return head;
}