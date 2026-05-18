#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	struct StackNode {
		SortedIndexedList::Node* data;
		StackNode* next;
		StackNode(SortedIndexedList::Node* d, StackNode* n) : data(d), next(n) {}
	};

	StackNode* top;
	SortedIndexedList::Node* current;

	void push(SortedIndexedList::Node* node);
	SortedIndexedList::Node* pop();
	void pushLeft(SortedIndexedList::Node* node);
	void clearStack();

public:
	void first();
	void next();
	bool valid() const;
	TComp getCurrent() const;
};