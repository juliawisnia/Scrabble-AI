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
	//if no items, return null
	if (!head) return nullptr;

	if (!(head->next)) return head; //only one element

	Item* smallest=findMin(head);
	std::cout<<"FIRST ITEM: "<<smallest->getValue()<<std::endl<<std::endl;
	if (smallest->next==nullptr) {
		smallest->prev->next=nullptr;
	}

	else {
		smallest->prev->next=smallest->next;
	}

	smallest->prev=nullptr;
	smallest->next=head->next;
	head->next->prev=smallest;
	head=smallest;

	Item* curr=head;

	int cnt=1;

	while (curr->next!=nullptr) {
		Item* min=findMin(curr->next);
		//std::cout<<cnt<<" "<<min->getValue()<<std::endl;
		if (min==curr && !curr->next) break;

		if (min->next==nullptr) {
			min->prev->next=nullptr;

			min->prev=curr;
			min->next=curr->next;
			curr->next->prev=min;
			curr=min;
			curr=curr->next;
		}

		else {
			min->prev->next=min->next;
			min->next=min->next->prev;

			min->prev=curr;
			min->next=curr->next;
			curr->next->prev=min;
			curr=min;
			curr=curr->next;
		}
		cnt++;
	}

	return head;
}

Item* prepend(Item* curr, Item* smallest) {

	if (smallest->next) {
		//update the 2 surrounding nodes pointers as to remove smallest
		smallest->prev->next=smallest->next;
		smallest->next->prev=smallest->prev;

		smallest->next=curr->next;
		smallest->prev=curr;
		curr->next=smallest;
		curr->next->prev=smallest;
		curr=smallest;
	}

	/*else {
		//if smallest is the last item
		smallest->prev->next=nullptr;

		smallest->next=curr;
		curr->prev->next=smallest;
		smallest->prev=curr->prev;
		curr=smallest;
	}*/

	return curr;
}