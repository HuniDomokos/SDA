#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

void ListIterator::push(SortedIndexedList::Node* node) {
	top = new StackNode(node, top);
}

SortedIndexedList::Node* ListIterator::pop() {
	StackNode* tmp = top;
	SortedIndexedList::Node* data = tmp->data;
	top = top->next;
	delete tmp;
	return data;
} // Theta 1

void ListIterator::clearStack() {
	while (top != nullptr) pop();
} // Theta n

void ListIterator::pushLeft(SortedIndexedList::Node* node) {
	while (node != nullptr) {
		push(node);
		node = node->left;
	}
} // Average O(log n) Worst case: O(n)

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	top = nullptr;
	current = nullptr;
	pushLeft(list.root);
	if (top != nullptr) current = pop();
} // Average O(log n) Worst case: O(n)

void ListIterator::first() {
	clearStack();
	current = nullptr;
	pushLeft(list.root);
	if (top != nullptr) current = pop();
} // Theta n

void ListIterator::next() {
	if (!valid()) throw exception();
	pushLeft(current->right);
	if (top != nullptr) current = pop();
	else current = nullptr;
}  // Theta n amortized

bool ListIterator::valid() const {
	return current != nullptr;
} // Theta 1

TComp ListIterator::getCurrent() const {
	if (!valid()) throw exception();
	return current->data;
} // Theta 1