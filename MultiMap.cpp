#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->head = nullptr;
	this->tail = nullptr;
	this->map_size = 0;
}


void MultiMap::add(TKey c, TValue v) {
	Node* current = this->head;

	while (current != nullptr) {
		if (current->key == c) {
			ValueNode* newVal = new ValueNode(v, current->valTail, nullptr);
			if (current->valTail) current->valTail->next = newVal;
			else current->valHead = newVal;
			current->valTail = newVal;
			this->map_size++;
			return;
		}
		current = current->next;
	}
	Node* newKey = new Node(c,this->tail,nullptr);
	if (this->tail != nullptr) this->tail->next = newKey;
	else this->head = newKey;
	this->tail = newKey;

	ValueNode* newVal = new ValueNode(v, nullptr, nullptr);
	newKey->valHead = newVal;
	newKey->valTail = newVal;

	this->map_size++;
} // Theta(n)


bool MultiMap::remove(TKey c, TValue v) {
	Node* current = this->head;
	while (current != nullptr) {
		if (current->key == c) {
			ValueNode* curr_val = current->valHead;
			while (curr_val != nullptr) {
				if (curr_val->value == v) {
					if (curr_val->prev != nullptr && curr_val->next != nullptr) {
						curr_val->prev->next = curr_val->next;
						curr_val->next->prev = curr_val->prev;
						delete curr_val;
					}
					else if (curr_val->prev == nullptr) {
						current->valHead = curr_val->next;
						if (curr_val->next) curr_val->next->prev = nullptr;
						delete curr_val;
					}
					else if (curr_val->next == nullptr) {
						current->valTail = curr_val->prev;
						if (curr_val->prev) curr_val->prev->next = nullptr;
						delete curr_val;
					}

					if (current->valHead == nullptr) {
						if (current->prev) current->prev->next = current->next;
						else               this->head = current->next;

						if (current->next) current->next->prev = current->prev;
						else               this->tail = current->prev;

						delete current;
					}
					this->map_size--;
					return true;
				}
				curr_val = curr_val->next;
			}
		}
		current = current->next;
	}
	return false;
} // O(n^2) Best case: is empty Theta(1)


vector<TValue> MultiMap::search(TKey c) const {
	Node* current = this->head;
	while (current != nullptr) {
		if (current->key == c) {
			vector<TValue> v;
			ValueNode* curr_val = current->valHead;
			while (curr_val != nullptr) {
				v.push_back(curr_val->value);
				curr_val = curr_val->next;
			}
			return v;
		}
		current = current->next;
	}
	return vector<TValue>();
} // O(n^2) Best case : is Empty Theta(1)


int MultiMap::size() const {
	return this->map_size;
} // Theta(1)


bool MultiMap::isEmpty() const {
	return this->head == nullptr;
} // Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	Node* current = this->head;
	while (current != nullptr) {
		ValueNode* curr_val = current->valHead;
		while (curr_val != nullptr) {
			ValueNode* next_val = curr_val->next;
			delete curr_val;
			curr_val = next_val;
		}
		Node* next_node = current->next;
		delete current;
		current = next_node;
	}
} // Theta (n^2)

