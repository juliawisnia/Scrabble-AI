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
	
}
