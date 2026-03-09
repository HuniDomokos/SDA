#include "SortedBag.h"

#include <bits/error_constants.h>

#include "SortedBagIterator.h"

#include <pair>

SortedBag::SortedBag(Relation r, int bagSize) {
	this->rel = r;
	this->bagSize = bagSize;
	this->count = 0;
	this->Bag =  new std::pair<TComp,int>[bagSize];
}

void SortedBag::add(TComp e) {
	if (this->currentSize < bagSize) {
	for (int i = 0; i< this->currentSize; i++) {
		if (this->Bag[i].first == e) {this->Bag[i].second++; return;}
	}
	this->Bag[this->currentSize].first = e;
	this->Bag[this->currentSize].second = 1;
		this->currentSize++;
}
	else {
	throw std::invalid_argument("Bag is full");
}
}


bool SortedBag::remove(TComp e) {
	for (int i = 0; i < this->currentSize; i++) {
	if (this->Bag[i].first == e) {
		for(int j = i; j < this->currentSize - 1; j++) {this->Bag[j] = this->Bag[j + 1];}

    this->currentSize--;
	return true;
}
}
	return false;
}


bool SortedBag::search(TComp elem) const {

	for (int i = 0; i < this->currentSize; i++) {
    if (this->Bag[i].first == elem) {return true;}
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	if (search(elem)){
	for (int i = 0; i < this->currentSize; i++) {
		if (this->Bag[i].first == elem) {return this->Bag[i].second;}
    }
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
