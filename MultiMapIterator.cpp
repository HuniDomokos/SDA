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
} // 0(1)

void MultiMapIterator::next() {
	if (!this->valid()) {
		throw std::logic_error("next(): Invalid position");
	}

	this->currentValue = col.keys[currentKey].valNext[currentValue];

	if (this->currentValue == -1) {
		this->currentKey = col.keys[currentKey].next;
		while (this->currentKey != -1 && col.keys[currentKey].valHead == -1) {
			this->currentKey = col.keys[currentKey].next;
		}

		if (this->currentKey != -1) {
			this->currentValue = col.keys[currentKey].valHead;
		}
	}
} // Best case: 0(1) Worst Case: 0(n)

bool MultiMapIterator::valid() const {
	return this->currentKey != -1 && this->currentValue != -1;
} // 0(1)

TElem MultiMapIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::logic_error("getCurrent(): Invalid position");
	}

	TKey k = col.keys[currentKey].key;
	TValue v = col.keys[currentKey].values[currentValue];
	return std::make_pair(k, v);
} // 0(1)