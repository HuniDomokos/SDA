#pragma once
#include <vector>
#include <utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	struct KeyNode {
		TKey key;

		TValue* values;
		int* valNext;
		int* valPrev;

		int valHead;
		int valTail;
		int firstEmptyVal;
		int valCapacity;
		int valCount;

		int next;
		int prev;

		KeyNode() : key(-1), values(nullptr), valNext(nullptr), valPrev(nullptr),
					valHead(-1), valTail(-1), firstEmptyVal(-1), valCapacity(0),
					valCount(0), next(-1), prev(-1) {}
	};


	KeyNode* keys;
	int capKeys;
	int headKey;
	int tailKey;
	int firstEmptyKey;
	int count;

	// Helper functions
	void resizeKeys();
	void resizeValues(int keyIdx);
	int findKeyIndex(TKey c) const;

public:
	MultiMap();

	void add(TKey c, TValue v);

	bool remove(TKey c, TValue v);

	vector<TValue> search(TKey c) const;

	int size() const;

	bool isEmpty() const;

	MultiMapIterator iterator() const;

	~MultiMap();
};