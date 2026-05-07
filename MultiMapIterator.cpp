#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	this->first();
}

TElem MultiMapIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::logic_error("getCurrent(): Iterator is invalid.");
	}
	TKey k = col.nodes[currentKeyIdx].key;
	TValue v = col.valuePool[currentValIdx].value;
	return std::make_pair(k, v);
}

bool MultiMapIterator::valid() const {
	return this->currentKeyIdx != -1 && this->currentValIdx != -1;
}

void MultiMapIterator::next() {
	if (!this->valid()) {
		throw std::logic_error("next(): Iterator is invalid.");
	}

	this->currentValIdx = col.valuePool[currentValIdx].next;

	if (this->currentValIdx == -1) {
		this->currentKeyIdx = col.nodes[currentKeyIdx].next;
		if (this->currentKeyIdx != -1) {
			this->currentValIdx = col.nodes[currentKeyIdx].valHead;
		}
	}
}

void MultiMapIterator::first() {
	this->currentKeyIdx = col.keyHead;
	if (this->currentKeyIdx != -1) {
		this->currentValIdx = col.nodes[currentKeyIdx].valHead;
	} else {
		this->currentValIdx = -1;
	}
}