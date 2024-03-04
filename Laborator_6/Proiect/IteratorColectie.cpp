#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	this->index = 0;
    this->lg = col.lg;
    this->array = new TElem [this->lg];
    this->key = 0;
    for (int i = 0; i < col.capacitate; i++) {
        if (this->col.hashTable[i] != this->col.sters && this->col.hashTable[i] != this->col.gol) {
            this->array[this->key] = this->col.hashTable[i];
            this->key++;
        }
    }
}

void IteratorColectie::prim() {
	this->index = 0;
}

void IteratorColectie::urmator() {
	if (!valid()) throw std::exception();
    this->index++;
}

bool IteratorColectie::valid() const {
	if (this->index < this->lg && this->index >= 0)
        return true;
	return false;
}

TElem IteratorColectie::element() const {
    if(!valid()) throw std::exception();
    return this->array[this->index];
}
