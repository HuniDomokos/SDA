#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	rel = r;
	root = nullptr;
	nr_elems = 0;
} // Theta 1

int SortedIndexedList::size() const {
	return nr_elems;
} // Theta 1

bool SortedIndexedList::isEmpty() const {
	return nr_elems == 0;
} // Theta 1

TComp SortedIndexedList::getElement(int i) const{
	Node* current = root;
	if (i < 0 || i >= nr_elems) throw out_of_range("Index out of range");

	while (current != nullptr) {
		if (current->nodes_left == i) return current->data;
		else if (current->nodes_left < i) {
			i -= current->nodes_left + 1;
			current = current->right;
		}
			else current = current->left;
		}
	return NULL_TCOMP;
} // Theta log(n)

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= nr_elems) throw out_of_range("Index out of range");

    Node* current = root;
    Node* parent = nullptr;
    bool wentLeft = false;
	TComp removed = NULL_TCOMP;

    while (current != nullptr) {
        if (current->nodes_left == i) break;
        else if (i < current->nodes_left) {
            parent = current;
            wentLeft = true;
            current->nodes_left--;
            current = current->left;
        }
        else {
            i -= current->nodes_left + 1;
            parent = current;
            wentLeft = false;
            current = current->right;
        }
    }

    removed = current->data;

	// no children
    if (!current->left && !current->right) {
        if (parent == nullptr) root = nullptr;
        else if (wentLeft)  parent->left = nullptr;
        else parent->right = nullptr;
        delete current;
    }

	// 1 child
    else if (!current->left || !current->right) {
        Node* child = current->left ? current->left : current->right;
        if (parent == nullptr) root = child;
        else if (wentLeft) parent->left = child;
        else parent->right = child;
        delete current;
    }

	// 2 children
    else {
        Node* successorParent = current;
        Node* successor = current->right;

        while (successor->left != nullptr) {
            successorParent = successor;
            successorParent->nodes_left--;
            successor = successor->left;
        }

        current->data = successor->data;

        if (successorParent == current) successorParent->right = successor->right;
        else successorParent->left = successor->right;

        delete successor;
    }

    nr_elems--;
    return removed;
}

int SortedIndexedList::search(TComp e) const {
    Node* current = root;
    int pos = 0;
    int found = -1;

    while (current != nullptr) {
        if (current->data == e) {
            found = pos + current->nodes_left;
            current = current->left;
        }
        else if (rel(e, current->data)) {
            current = current->left;
        }
        else {
            pos += current->nodes_left + 1;
            current = current->right;
        }
    }
    return found;
}

void SortedIndexedList::add(TComp e) {
    Node* newNode = new Node(e);
    nr_elems++;

    if (root == nullptr) { root = newNode; return; }

    Node* current = root;
    while (current != nullptr) {
        if (rel(e, current->data)) {
            current->nodes_left++;
            if (current->left == nullptr) { current->left = newNode; return; }
            current = current->left;
        }
        else {
            if (current->right == nullptr) { current->right = newNode; return; }
            current = current->right;
        }
    }
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
void SortedIndexedList::deleteTree(SortedIndexedList::Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

SortedIndexedList::~SortedIndexedList() {
    deleteTree(root);
}
