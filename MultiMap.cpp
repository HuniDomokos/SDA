#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>

MultiMap::MultiMap() {
	this->capKeys = 10;
	this->capValues = 10;
	this->keys = new KeyNode[capKeys];
	this->values = new ValueNode[capValues];

	this->headKey = -1;
	this->tailKey = -1;
	this->count = 0;

	for (int i = 0; i < capKeys - 1; i++) this->keys[i].next = i + 1;
	this->keys[capKeys - 1].next = -1;
	this->firstEmptyKey = 0;

	for (int i = 0; i < capValues - 1; i++) this->values[i].next = i + 1;
	this->values[capValues - 1].next = -1;
	this->firstEmptyValue = 0;
}
// Complexitate: Theta(capKeys + capValues)

void MultiMap::resizeKeys() {
	int oldCap = capKeys;
	capKeys *= 2;
	KeyNode* newKeys = new KeyNode[capKeys];
	for (int i = 0; i < oldCap; i++) newKeys[i] = keys[i];
	for (int i = oldCap; i < capKeys - 1; i++) newKeys[i].next = i + 1;
	newKeys[capKeys - 1].next = -1;
	delete[] keys;
	keys = newKeys;
	firstEmptyKey = oldCap;
}

void MultiMap::resizeValues() {
	int oldCap = capValues;
	capValues *= 2;
	ValueNode* newVals = new ValueNode[capValues];
	for (int i = 0; i < oldCap; i++) newVals[i] = values[i];
	for (int i = oldCap; i < capValues - 1; i++) newVals[i].next = i + 1;
	newVals[capValues - 1].next = -1;
	delete[] values;
	values = newVals;
	firstEmptyValue = oldCap;
}

int MultiMap::allocateKey() {
	if (firstEmptyKey == -1) resizeKeys();
	int res = firstEmptyKey;
	firstEmptyKey = keys[firstEmptyKey].next;
	return res;
}

void MultiMap::freeKey(int index) {
	keys[index].next = firstEmptyKey;
	firstEmptyKey = index;
}

int MultiMap::allocateValue() {
	if (firstEmptyValue == -1) resizeValues();
	int res = firstEmptyValue;
	firstEmptyValue = values[firstEmptyValue].next;
	return res;
}

void MultiMap::freeValue(int index) {
	values[index].next = firstEmptyValue;
	firstEmptyValue = index;
}

void MultiMap::add(TKey c, TValue v) {
	int current = headKey;
	while (current != -1 && keys[current].key != c) {
		current = keys[current].next;
	}

	int newValueIdx = allocateValue();
	values[newValueIdx].value = v;
	values[newValueIdx].next = -1;

	if (current != -1) {
		values[newValueIdx].prev = keys[current].tailValue;
		values[keys[current].tailValue].next = newValueIdx;
		keys[current].tailValue = newValueIdx;
	} else {
		int newKeyIdx = allocateKey();
		keys[newKeyIdx].key = c;
		keys[newKeyIdx].headValue = newValueIdx;
		keys[newKeyIdx].tailValue = newValueIdx;
		values[newValueIdx].prev = -1;

		keys[newKeyIdx].next = -1;
		keys[newKeyIdx].prev = tailKey;
		if (tailKey != -1) keys[tailKey].next = newKeyIdx;
		else headKey = newKeyIdx;
		tailKey = newKeyIdx;
	}
	count++;
}
// Best Case: Theta(1) - cheia e pe prima poziție
//Worst Case: Theta(n) - unde n e nr. de chei unice

bool MultiMap::remove(TKey c, TValue v) {
	int currentK = headKey;
	while (currentK != -1 && keys[currentK].key != c) {
		currentK = keys[currentK].next;
	}

	if (currentK == -1) return false;

	int currentV = keys[currentK].headValue;
	while (currentV != -1 && values[currentV].value != v) {
		currentV = values[currentV].next;
	}

	if (currentV == -1) return false;

	if (values[currentV].prev != -1) values[values[currentV].prev].next = values[currentV].next;
	else keys[currentK].headValue = values[currentV].next;

	if (values[currentV].next != -1) values[values[currentV].next].prev = values[currentV].prev;
	else keys[currentK].tailValue = values[currentV].prev;

	freeValue(currentV);
	count--;

	if (keys[currentK].headValue == -1) {
		if (keys[currentK].prev != -1) keys[keys[currentK].prev].next = keys[currentK].next;
		else headKey = keys[currentK].next;

		if (keys[currentK].next != -1) keys[keys[currentK].next].prev = keys[currentK].prev;
		else tailKey = keys[currentK].prev;

		freeKey(currentK);
	}
	return true;
}
// Best Case: Theta(1) - prima cheie, prima valoare
// Worst Case: Theta(n + m) - n chei, m valori la cheia respectivă

vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> res;
	int currentK = headKey;
	while (currentK != -1 && keys[currentK].key != c) {
		currentK = keys[currentK].next;
	}
	if (currentK != -1) {
		int currentV = keys[currentK].headValue;
		while (currentV != -1) {
			res.push_back(values[currentV].value);
			currentV = values[currentV].next;
		}
	}
	return res;
}
//Best Case: Theta(1) - cheia e prima și nu are valori sau are una
//Worst Case: Theta(n + m) - n chei, m valori

int MultiMap::size() const { return count; }
// Best/Worst: Theta(1)

bool MultiMap::isEmpty() const { return count == 0; }
// Best/Worst: Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
	delete[] keys;
	delete[] values;
}