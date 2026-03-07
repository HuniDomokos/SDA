#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->rel = r;
	this->bagSize = 10;
	this->count = 0;
	this->Bag =  new TComp[bagSize];
}

void SortedBag::add(TComp e) {
	if (this->currentSize < bagSize) {
	this->Bag[this->currentSize] = e;
	this->currentSize++;
}
	else {
	throw std::out_of_range("Bag is full");
}
}


bool SortedBag::remove(TComp e) {
	for (int i = 0; i < this->currentSize; i++) {
	if (this->Bag[i] == e) {
		for(int j = i; j < this->currentSize - 1; j++) {this->Bag[j] = this->Bag[j + 1];}

    this->currentSize--;
	return true;
}
}
	return false;
}


bool SortedBag::search(TComp elem) const {

	for (int i = 0; i < this->currentSize; i++) {
    if (this->Bag[i] == elem) {return true;}
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	if (search(elem)) {
		int count = 0;
	for (int i = 0; i < this->currentSize; i++) {
		if (this->Bag[i] == elem) {count++;}
    }
    return count;
	}
	return 0;
}



int SortedBag::size() const {
	return this->currentSize;
}


bool SortedBag::isEmpty() const {
	return this->currentSize == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] this->Bag;
}
