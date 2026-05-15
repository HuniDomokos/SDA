#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <cstdlib>
using namespace std;

const TElem SortedMap::DELETED = {-222222, -222222};

SortedMap::SortedMap(Relation r) {
    capacity = 11;
    nr_elements = 0;
    rel = r;
    table = new TElem[capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = NULL_TPAIR
}

int SortedMap::hash1(TKey k) const {
    return abs(k) % capacity;
}

int SortedMap::hash2(TKey k) const {
    return 1 + (abs(k) % (capacity - 1));
}

int SortedMap::probe(TKey k, int i) const {
    return (hash1(k) + i * hash2(k)) % capacity;
}

void SortedMap::resize() {
    int old_capacity = capacity;
    TElem* old_table = table;
    capacity = capacity * 2 + 1;
    table = new TElem[capacity];
    TElem null_pair = NULL_TPAIR

    for (int i = 0; i < capacity; i++)
        table[i] = null_pair;

    nr_elements = 0;
    for (int i = 0; i < old_capacity; i++) {
        if (old_table[i] != null_pair && old_table[i] != DELETED)
            add(old_table[i].first, old_table[i].second);
    }
    delete[] old_table;
}

TValue SortedMap::add(TKey k, TValue v) {
    if (nr_elements >= capacity / 2)
        resize();

    int i = 0;

    while (i < capacity) {
        int pos = probe(k, i);
        TElem null_pair = NULL_TPAIR

        if (table[pos] == null_pair) {
            table[pos] = {k, v};
            nr_elements++;
            return NULL_TVALUE;
        }
        else if (table[pos].first == k) {
            TValue old = table[pos].second;
            table[pos].second = v;
            return old;
        }
        i++;
    }

    return NULL_TVALUE;
} // Average O(1) , Worst case O(n)

TValue SortedMap::search(TKey k) const {
    int i = 0;
    TElem null_pair = NULL_TPAIR

    while (i < capacity) {
        int pos = probe(k, i);
        if (table[pos] == null_pair)
            return NULL_TVALUE;
        if (table[pos] != DELETED && table[pos].first == k)
            return table[pos].second;
        i++;
    }
    return NULL_TVALUE;
} // Average O(1) , Worst case O(n)

TValue SortedMap::remove(TKey k) {
    int i = 0;
    TElem null_pair = NULL_TPAIR

    while (i < capacity) {
        int pos = probe(k, i);
        if (table[pos] == null_pair)
            return NULL_TVALUE;
        if (table[pos] != DELETED && table[pos].first == k) {
            TValue old = table[pos].second;
            table[pos] = DELETED;
            nr_elements--;
            return old;
        }
        i++;
    }
    return NULL_TVALUE;
} // Average O(1) , Worst case O(n)

int SortedMap::size() const {
    return nr_elements;
} // Theta 1

bool SortedMap::isEmpty() const {
    return nr_elements == 0;
} // Theta 1

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
} // Theta 1

SortedMap::~SortedMap() {
    delete[] table;
} // Theta 1