#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    lg = col.dim();
    curent = 0;
    array = new TElem [lg];
    index = 0;
    for (int i = 0; i < col.capacity; i++) {
        if (col.elems[i].first != col.empty) {
            auto aux = col.elems[i].second;
            while (aux != 0) {
                array[index] = col.elems[i].first;
                index++;
                aux--;
            }
        }
    }
}

TElem IteratorColectie::element() const{
    if(!valid()) throw std::exception();
    return array[curent];
}

bool IteratorColectie::valid() const {
    if(curent < lg && curent >= 0) return true;
    return false;
}

void IteratorColectie::urmator() {
    if(!valid()) throw std::exception();
    curent++;
}

void IteratorColectie::prim() {
    curent = 0;
}