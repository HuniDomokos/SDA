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
}

void ListIterator::clearStack() {
	while (top != nullptr) pop();
}

void ListIterator::pushLeft(SortedIndexedList::Node* node) {
	while (node != nullptr) {
		push(node);
		node = node->left;
	}
}

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	top = nullptr;
	current = nullptr;
	pushLeft(list.root);
	if (top != nullptr) current = pop();
}

void ListIterator::first() {
	clearStack();
	current = nullptr;
	pushLeft(list.root);
	if (top != nullptr) current = pop();
}

void ListIterator::next() {
	if (!valid()) throw exception();
	pushLeft(current->right);
	if (top != nullptr) current = pop();
	else current = nullptr;
}

bool ListIterator::valid() const {
	return current != nullptr;
}

TComp ListIterator::getCurrent() const {
	if (!valid()) throw exception();
	return current->data;
}