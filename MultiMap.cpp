#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <vector>

MultiMap::MultiMap() {
    this->keyCapacity = 10;
    this->valCapacity = 10;
    this->nodes = new Node[keyCapacity];
    this->valuePool = new ValueNode[valCapacity];
    this->keyHead = -1;
    this->keyTail = -1;
    this->firstEmptyKey = 0;
    this->firstEmptyVal = 0;
    this->map_size = 0;

    for (int i = 0; i < keyCapacity - 1; i++) {
        nodes[i].next = i + 1;
    }
    nodes[keyCapacity - 1].next = -1;

    for (int i = 0; i < valCapacity - 1; i++) {
        valuePool[i].next = i + 1;
    }
    valuePool[valCapacity - 1].next = -1;
}

void MultiMap::resizeKeys() {
    int oldCap = keyCapacity;
    keyCapacity *= 2;
    Node* newNodes = new Node[keyCapacity];
    for (int i = 0; i < oldCap; i++) {
        newNodes[i] = nodes[i];
    }
    for (int i = oldCap; i < keyCapacity - 1; i++) {
        newNodes[i].next = i + 1;
    }
    newNodes[keyCapacity - 1].next = -1;
    delete[] nodes;
    nodes = newNodes;
    firstEmptyKey = oldCap;
}

void MultiMap::resizeValues() {
    int oldCap = valCapacity;
    valCapacity *= 2;
    ValueNode* newVals = new ValueNode[valCapacity];
    for (int i = 0; i < oldCap; i++) {
        newVals[i] = valuePool[i];
    }
    for (int i = oldCap; i < valCapacity - 1; i++) {
        newVals[i].next = i + 1;
    }
    newVals[valCapacity - 1].next = -1;
    delete[] valuePool;
    valuePool = newVals;
    firstEmptyVal = oldCap;
}

void MultiMap::add(TKey c, TValue v) {
    int currentKey = keyHead;
    int targetKeyIdx = -1;

    while (currentKey != -1) {
        if (nodes[currentKey].key == c) {
            targetKeyIdx = currentKey;
            break;
        }
        currentKey = nodes[currentKey].next;
    }

    if (targetKeyIdx == -1) {
        if (firstEmptyKey == -1) resizeKeys();
        targetKeyIdx = firstEmptyKey;
        firstEmptyKey = nodes[firstEmptyKey].next;

        nodes[targetKeyIdx].key = c;
        nodes[targetKeyIdx].valHead = -1;
        nodes[targetKeyIdx].valTail = -1;
        nodes[targetKeyIdx].prev = keyTail;
        nodes[targetKeyIdx].next = -1;

        if (keyHead == -1) keyHead = targetKeyIdx;
        if (keyTail != -1) nodes[keyTail].next = targetKeyIdx;
        keyTail = targetKeyIdx;
    }

    if (firstEmptyVal == -1) resizeValues();
    int newValIdx = firstEmptyVal;
    firstEmptyVal = valuePool[firstEmptyVal].next;

    valuePool[newValIdx].value = v;
    valuePool[newValIdx].prev = nodes[targetKeyIdx].valTail;
    valuePool[newValIdx].next = -1;

    if (nodes[targetKeyIdx].valHead == -1) {
        nodes[targetKeyIdx].valHead = newValIdx;
    } else {
        valuePool[nodes[targetKeyIdx].valTail].next = newValIdx;
    }
    nodes[targetKeyIdx].valTail = newValIdx;
    map_size++;
}

bool MultiMap::remove(TKey c, TValue v) {
    int currentKey = keyHead;
    while (currentKey != -1) {
        if (nodes[currentKey].key == c) {
            int currentVal = nodes[currentKey].valHead;
            while (currentVal != -1) {
                if (valuePool[currentVal].value == v) {
                    if (valuePool[currentVal].prev != -1)
                        valuePool[valuePool[currentVal].prev].next = valuePool[currentVal].next;
                    else
                        nodes[currentKey].valHead = valuePool[currentVal].next;

                    if (valuePool[currentVal].next != -1)
                        valuePool[valuePool[currentVal].next].prev = valuePool[currentVal].prev;
                    else
                        nodes[currentKey].valTail = valuePool[currentVal].prev;

                    valuePool[currentVal].next = firstEmptyVal;
                    firstEmptyVal = currentVal;
                    map_size--;

                    if (nodes[currentKey].valHead == -1) {
                        if (nodes[currentKey].prev != -1)
                            nodes[nodes[currentKey].prev].next = nodes[currentKey].next;
                        else
                            keyHead = nodes[currentKey].next;

                        if (nodes[currentKey].next != -1)
                            nodes[nodes[currentKey].next].prev = nodes[currentKey].prev;
                        else
                            keyTail = nodes[currentKey].prev;

                        nodes[currentKey].next = firstEmptyKey;
                        firstEmptyKey = currentKey;
                    }
                    return true;
                }
                currentVal = valuePool[currentVal].next;
            }
            return false;
        }
        currentKey = nodes[currentKey].next;
    }
    return false;
}

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> result;
    int currentKey = keyHead;
    while (currentKey != -1) {
        if (nodes[currentKey].key == c) {
            int currentVal = nodes[currentKey].valHead;
            while (currentVal != -1) {
                result.push_back(valuePool[currentVal].value);
                currentVal = valuePool[currentVal].next;
            }
            return result;
        }
        currentKey = nodes[currentKey].next;
    }
    return result;
}

int MultiMap::size() const {
    return map_size;
}

bool MultiMap::isEmpty() const {
    return map_size == 0;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
    delete[] nodes;
    delete[] valuePool;
}