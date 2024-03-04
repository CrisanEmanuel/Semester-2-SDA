#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict { d }, curent { d.prim }{}

void IteratorDictionar::prim() {
	this->curent = this->dict.prim;
}

void IteratorDictionar::urmator() {
    if (!this->valid()) throw exception();
    this->curent = this->dict.urm[this->curent];
}

TElem IteratorDictionar::element() const{
    if (!this->valid()) throw exception();
    return make_pair(this->dict.elems[curent].first, this->dict.elems[curent].second);
}

bool IteratorDictionar::valid() const {
    return (this->curent != -1 && this->dict.elems[curent].first != this->dict.empty);
}

void IteratorDictionar::avanseazaKPasi(int k) {
    if (k <= 0) throw exception();
    while (k > 0)  {
        if (!this->valid()) throw exception();
        this->urmator();
        k--;
    }
}
