#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
	sortedElems = new TElem[map.nr_elements + 1];
	int count = 0;
	TElem null_pair = NULL_TPAIR

	for (int i = 0; i < map.capacity; i++) {
		if (map.table[i] != null_pair && map.table[i] != SortedMap::DELETED)
			sortedElems[count++] = map.table[i];
	}

	for (int i = 1; i < count; i++) {
		TElem current_elem = sortedElems[i];
		int j = i - 1;
		while (j >= 0 && !map.rel(sortedElems[j].first, current_elem.first)) {
			sortedElems[j + 1] = sortedElems[j];
			j--;
		}
		sortedElems[j + 1] = current_elem;
	}

	sortedElems[count] = NULL_TPAIR
	current = 0;
} // O(capacity + n^2) - O(capacity) to collect, O(n^2) insertion sort

void SMIterator::first(){
	current = 0;
} // Theta(1)

void SMIterator::next(){
	if (!valid())
		throw exception();
	current++;
} // Theta(1)

bool SMIterator::valid() const {
	TElem null_pair = NULL_TPAIR
	return sortedElems[current] != null_pair;
} // Theta(1)

TElem SMIterator::getCurrent() const {
	if (!valid())
		throw exception();
	return sortedElems[current];
} // Theta(1)