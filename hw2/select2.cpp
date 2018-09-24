Item* LLSelectionSort(Item * head) {
	if (!head) return nullptr;

	if (!head->next) return head;

	Item* curr=head;
	Item* min=findMin(head);
	if (min==head) curr=head->next;

	recurse(curr);

	return head;
}

void recurse(Item* curr) {
	if (!curr->next) return; //curr is last element

	Item* min=findMin(curr);

	if (min==curr) {
		curr=curr->next; //advance curr
		recurse(curr);
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

	//min is next to curr	
	min->next=curr;

	if (!curr->prev) {
		min->prev=nullptr; //curr is first element
		curr->prev=min;
		recurse (curr);
	}

	else {
		min->prev=curr->prev;
		curr->prev->next=min;
		curr->prev=min;
		recurse (curr); //don't advance curr
	}

/*	//you're not moving to the head
	if (curr->prev) {
		min->prev=curr->prev;
		min->next=curr;
		curr->next->prev=min;
	}

	else {
		min->prev=nullptr;
	}
*/
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