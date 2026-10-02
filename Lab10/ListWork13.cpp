#include <iostream>
#include "input.h"
#include "list.h"
void ListWork13(LinkedList &l) {
	ListNode* current = l.get_head();
	while (current != nullptr) {
		if (current->data % 3 == 0) {
			std::cout << current->data << " ";
		}
		current = current->next;
	}
}