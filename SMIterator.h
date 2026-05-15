#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	TElem* sortedElems;
	int current;
	int nr_elems;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

