#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	current = 0;
}

void ListIterator::first() {
	current = 0;
}

void ListIterator::next() {
	if (!valid()) throw exception();
	current++;
}

bool ListIterator::valid() const {
	return current < list.nr_elems;
}

TComp ListIterator::getCurrent() const {
	if (!valid()) throw exception();
	return list.getElement(current);
}


