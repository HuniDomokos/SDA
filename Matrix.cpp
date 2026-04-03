#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	if (nrLines <= 0 || nrCols <= 0) {
		throw exception();
	}
	this->numRows = nrLines;
	this->numCols = nrCols;

	Node* prevRow = nullptr;
	for (int i = 0; i < this->numRows; i++) {
		Node* newRow = new Node(i, -1, NULL_TELEM, nullptr, nullptr);
		newRow->nextRow = newRow;

		if (i == 0) this->rowHead = newRow;
		else prevRow->nextCol = newRow;
		prevRow = newRow;
	}

	Node* prevCol = nullptr;
	for (int j = 0; j < this->numCols; j++) {
		Node* newCol = new Node(-1, j, NULL_TELEM, nullptr, nullptr);
		newCol->nextCol = newCol;

		if (j == 0) this->colHead = newCol;
		else prevCol->nextRow = newCol;
		prevCol = newCol;
	}
}


int Matrix::nrLines() const {
	return this->numRows;
}


int Matrix::nrColumns() const {
	return this->numCols;
}


TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= numRows || j < 0 || j >= numCols) {
		throw std::exception();
	}

	Node* currentRow = this->rowHead;
	for (int row_index = 0; row_index < i; row_index++) {
		currentRow = currentRow->nextCol;
	}

	Node* currentCol = currentRow->nextRow;
	while (currentCol != currentRow) {
		if (currentCol->col == j) return currentCol->data;
		if (currentCol->col > j) break;
		currentCol = currentCol->nextRow;
	}

	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= numRows || j < 0 || j >= numCols) {
		throw std::exception();
	}

	Node* currentRow = this->rowHead;
	for (int row_index = 0; row_index < i; row_index++) {
		currentRow = currentRow->nextCol;
	}

	Node* currentCol = this->colHead;
	for (int col_index = 0; col_index < j; col_index++) {
		currentCol = currentCol->nextRow;
	}

	Node* prevRow = currentRow;
	while (prevRow->nextRow != currentRow && prevRow->nextRow->col < j) {
		prevRow = prevRow->nextRow;
	}

	Node* prevCol = currentCol;
	while (prevCol->nextCol != currentCol && prevCol->nextCol->row < i) {
		prevCol = prevCol->nextCol;
	}

	Node* target = prevRow->nextRow;
	TElem prevVal = NULL_TELEM;
	bool exists = (target != currentRow && target->col == j);
	if (exists) prevVal = target->data;


	if (exists && e == NULL_TELEM) {
		prevRow->nextRow = target->nextRow;
		prevCol->nextCol = target->nextCol;
		delete target;
	}
	else if (exists && e != NULL_TELEM) {
		target->data = e;
	}
	else if (!exists && e != NULL_TELEM) {
		Node* newNode = new Node(i, j, e, nullptr, nullptr);

		newNode->nextRow = prevRow->nextRow;
		prevRow->nextRow = newNode;

		newNode->nextCol = prevCol->nextCol;
		prevCol->nextCol = newNode;
	}

	return prevVal;
}

Matrix::~Matrix() {
	//TODO - Implementation
}


