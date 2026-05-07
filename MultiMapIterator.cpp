#include "MultiMapIterator.h"
#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	first();
}
// Best/Worst: Theta(1)

void MultiMapIterator::first() {
	currentKey = col.headKey;
	if (currentKey != -1) currentValue = col.keys[currentKey].headValue;
	else currentValue = -1;
}
// Best/Worst: Theta(1)

bool MultiMapIterator::valid() const {
	return currentKey != -1 && currentValue != -1;
}
// Best/Worst: Theta(1)

TElem MultiMapIterator::getCurrent() const {
	if (!valid()) throw std::exception();
	return { col.keys[currentKey].key, col.values[currentValue].value };
}
// Best/Worst: Theta(1)

void MultiMapIterator::next() {
	if (!valid()) throw std::exception();

	currentValue = col.values[currentValue].next;

	if (currentValue == -1) {
		currentKey = col.keys[currentKey].next;
		if (currentKey != -1) {
			currentValue = col.keys[currentKey].headValue;
		}
	}
}
// Best Case: Theta(1)
//Worst Case: Theta(1)