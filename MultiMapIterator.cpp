#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	this->first();
}

void MultiMapIterator::first() {
	this->currentKey = col.headKey;
	if (this->currentKey != -1) {
		this->currentValue = col.keys[currentKey].valHead;
	} else {
		this->currentValue = -1;
	}
}

void MultiMapIterator::next() {
	if (!this->valid()) {
		throw std::logic_error("next(): Invalid iterator state.");
	}

	// Move to next value in the current key's private DLLA
	this->currentValue = col.keys[currentKey].valNext[currentValue];

	// If reached end of values for current key, find next key that has values
	if (this->currentValue == -1) {
		this->currentKey = col.keys[currentKey].next;
		while (this->currentKey != -1 && col.keys[currentKey].valHead == -1) {
			this->currentKey = col.keys[currentKey].next;
		}

		if (this->currentKey != -1) {
			this->currentValue = col.keys[currentKey].valHead;
		}
	}
}

bool MultiMapIterator::valid() const {
	return this->currentKey != -1 && this->currentValue != -1;
}

TElem MultiMapIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::logic_error("getCurrent(): Invalid iterator state.");
	}

	TKey k = col.keys[currentKey].key;
	TValue v = col.keys[currentKey].values[currentValue];
	return std::make_pair(k, v);
}