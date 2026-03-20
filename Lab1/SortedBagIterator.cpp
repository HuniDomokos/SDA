#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->Bag = b;
	this->current = 0;
	this->current_frequency = 0;
}

TComp SortedBagIterator::getCurrent() {
	if (!this->Bag.isEmpty()) {return this->Bag[current];}
	return NULL_TCOMP;
}

bool SortedBagIterator::valid() {
	return (this->current < this->Bag.size()) && (this->current_frequency < this->Bag[current].second);
}

void SortedBagIterator::next() {
	if(this->Bag[current].second > this->current_frequency) this->current_frequency++;
	else {this->current++; this->current_frequency = 0;}
}

void SortedBagIterator::first() {
	this->current = 0;
	this->current_frequency = 0;
}

