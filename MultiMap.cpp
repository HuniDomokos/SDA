#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <vector>

// N = numarul de chei unice     M = numarul de valori asociate unei chei      CK= capacitatea totala a vectorului de chei      CV = capacitatea curenta a vectorului de valori al unei chei

MultiMap::MultiMap() {
    capKeys = 10;
    keys = new KeyNode[capKeys];
    headKey = -1;
    tailKey = -1;
    firstEmptyKey = 0;
    count = 0;

    for (int i = 0; i < capKeys - 1; i++) {
        keys[i].next = i + 1;
    }
    keys[capKeys - 1].next = -1;
}     //Best/Worst case: 0(CK)

void MultiMap::resizeKeys() {
    int oldCap = capKeys;
    capKeys *= 2;
    KeyNode* newKeys = new KeyNode[capKeys];
    for (int i = 0; i < oldCap; i++) {
        newKeys[i] = keys[i];
    }
    for (int i = oldCap; i < capKeys - 1; i++) {
        newKeys[i].next = i + 1;
    }
    newKeys[capKeys - 1].next = -1;
    delete[] keys;
    keys = newKeys;
    firstEmptyKey = oldCap;
} //Best/Worst case: 0(CK)

void MultiMap::resizeValues(int keyIdx) {
    int oldCap = keys[keyIdx].valCapacity;
    int newCap = (oldCap == 0) ? 5 : oldCap * 2;

    TValue* newVals = new TValue[newCap];
    int* newNext = new int[newCap];
    int* newPrev = new int[newCap];

    for (int i = 0; i < oldCap; i++) {
        newVals[i] = keys[keyIdx].values[i];
        newNext[i] = keys[keyIdx].valNext[i];
        newPrev[i] = keys[keyIdx].valPrev[i];
    }

    for (int i = oldCap; i < newCap - 1; i++) {
        newNext[i] = i + 1;
    }
    newNext[newCap - 1] = -1;

    delete[] keys[keyIdx].values;
    delete[] keys[keyIdx].valNext;
    delete[] keys[keyIdx].valPrev;

    keys[keyIdx].values = newVals;
    keys[keyIdx].valNext = newNext;
    keys[keyIdx].valPrev = newPrev;
    keys[keyIdx].valCapacity = newCap;
    keys[keyIdx].firstEmptyVal = oldCap;
}  //Best/Worst case: 0(CV)

int MultiMap::findKeyIndex(TKey c) const {
    int current = headKey;
    while (current != -1) {
        if (keys[current].key == c) return current;
        current = keys[current].next;
    }
    return -1;
}  //Best case: 0(1)   Worst case: 0(n)

void MultiMap::add(TKey c, TValue v) {
    int keyIdx = findKeyIndex(c);

    if (keyIdx == -1) {
        if (firstEmptyKey == -1) resizeKeys();
        keyIdx = firstEmptyKey;
        firstEmptyKey = keys[keyIdx].next;

        keys[keyIdx].key = c;
        keys[keyIdx].next = -1;
        keys[keyIdx].prev = tailKey;

        keys[keyIdx].valCapacity = 5;
        keys[keyIdx].values = new TValue[5];
        keys[keyIdx].valNext = new int[5];
        keys[keyIdx].valPrev = new int[5];

        for (int i = 0; i < 4; i++) keys[keyIdx].valNext[i] = i + 1;
        keys[keyIdx].valNext[4] = -1;

        keys[keyIdx].valHead = -1;
        keys[keyIdx].valTail = -1;
        keys[keyIdx].valCount = 0;
        keys[keyIdx].firstEmptyVal = 0;

        if (headKey == -1) headKey = keyIdx;
        else keys[tailKey].next = keyIdx;
        tailKey = keyIdx;
    }

    if (keys[keyIdx].firstEmptyVal == -1) resizeValues(keyIdx);

    int valIdx = keys[keyIdx].firstEmptyVal;
    keys[keyIdx].firstEmptyVal = keys[keyIdx].valNext[valIdx];

    keys[keyIdx].values[valIdx] = v;
    keys[keyIdx].valNext[valIdx] = -1;
    keys[keyIdx].valPrev[valIdx] = keys[keyIdx].valTail;

    if (keys[keyIdx].valHead == -1) keys[keyIdx].valHead = valIdx;
    else keys[keyIdx].valNext[keys[keyIdx].valTail] = valIdx;

    keys[keyIdx].valTail = valIdx;
    keys[keyIdx].valCount++;
    count++;
}  //Best case: 0(1)    Worst case: 0(N)

bool MultiMap::remove(TKey c, TValue v) {
    int keyIdx = findKeyIndex(c);
    if (keyIdx == -1) return false;

    int valIdx = keys[keyIdx].valHead;
    while (valIdx != -1) {
        if (keys[keyIdx].values[valIdx] == v) {
            if (keys[keyIdx].valPrev[valIdx] != -1)
                keys[keyIdx].valNext[keys[keyIdx].valPrev[valIdx]] = keys[keyIdx].valNext[valIdx];
            else
                keys[keyIdx].valHead = keys[keyIdx].valNext[valIdx];

            if (keys[keyIdx].valNext[valIdx] != -1)
                keys[keyIdx].valPrev[keys[keyIdx].valNext[valIdx]] = keys[keyIdx].valPrev[valIdx];
            else
                keys[keyIdx].valTail = keys[keyIdx].valPrev[valIdx];

            keys[keyIdx].valNext[valIdx] = keys[keyIdx].firstEmptyVal;
            keys[keyIdx].firstEmptyVal = valIdx;
            keys[keyIdx].valCount--;
            count--;

            if (keys[keyIdx].valCount == 0) {
                if (keys[keyIdx].prev != -1)
                    keys[keys[keyIdx].prev].next = keys[keyIdx].next;
                else
                    headKey = keys[keyIdx].next;

                if (keys[keyIdx].next != -1)
                    keys[keys[keyIdx].next].prev = keys[keyIdx].prev;
                else
                    tailKey = keys[keyIdx].prev;

                delete[] keys[keyIdx].values;
                delete[] keys[keyIdx].valNext;
                delete[] keys[keyIdx].valPrev;
                keys[keyIdx].values = nullptr;
                keys[keyIdx].valNext = nullptr;
                keys[keyIdx].valPrev = nullptr;

                keys[keyIdx].next = firstEmptyKey;
                firstEmptyKey = keyIdx;
            }
            return true;
        }
        valIdx = keys[keyIdx].valNext[valIdx];
    }
    return false;
}  //best case: 0(1)     Worst case: 0(N+M)

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> res;
    int keyIdx = findKeyIndex(c);
    if (keyIdx != -1) {
        int valIdx = keys[keyIdx].valHead;
        while (valIdx != -1) {
            res.push_back(keys[keyIdx].values[valIdx]);
            valIdx = keys[keyIdx].valNext[valIdx];
        }
    }
    return res;
}  //best case: 0(1)   worst case: 0(N+M)

int MultiMap::size() const {
    return count;
}

bool MultiMap::isEmpty() const {
    return count == 0;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
    int current = headKey;
    while (current != -1) {
        int next = keys[current].next;
        delete[] keys[current].values;
        delete[] keys[current].valNext;
        delete[] keys[current].valPrev;
        current = next;
    }
    delete[] keys;
}   //Best/Worst case: 0(N)