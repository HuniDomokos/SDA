#include "MultiMapIterator.h"

#include <stdexcept>

#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->current_key = col.head;
	if(this->current_key) this->current_val = col.head->valHead;
	else this->current_val = nullptr;
}

TElem MultiMapIterator::getCurrent() const{
	if (this->valid()) {
		return pair<int,int>(this->current_key->key,this->current_val->value);
	}
	else throw std::logic_error("getCurrent()");
	return NULL_TELEM;
}

bool MultiMapIterator::valid() const {
	if (this->current_key && this->current_val) {return true;}
	return false;
}

void MultiMapIterator::next() {
	if (!this->valid()) {
		throw std::logic_error("next()");
	}
	if (this->current_val->next) {
		this->current_val = this->current_val->next;
	}
	else if (this->current_key->next) {
		this->current_key = this->current_key->next;
		this->current_val = this->current_key->valHead;
	}
	else {
		this->current_key = nullptr;
		this->current_val = nullptr;
	}
}

void MultiMapIterator::first() {
	this->current_key = this->col.head;
	if (this->current_key) this->current_val = this->col.head->valHead;
	else this->current_val = nullptr;
}

