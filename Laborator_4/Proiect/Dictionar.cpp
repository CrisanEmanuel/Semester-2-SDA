#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

Dictionar::Dictionar() {
	this->capacitate = 13;
    this->primLiber = 0;
    this->prim = -1;
    this->empty = INT_MAX;
    this->deleted = INT_MIN;
    this->lg = 0;
    this->elems = new TElem [this->capacitate];
    this->urm = new int [this->capacitate];
    initSpatiuLiber();
}

Dictionar::~Dictionar() {
	delete[] this->elems;
    delete[] this->urm;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
    if (this->vid()) {
        auto indexLiber = aloca();
        this->prim = indexLiber;
        this->elems[indexLiber] = std::make_pair(c, v);
        this->lg ++;
        return NULL_TVALOARE;
    }

    if (this->primLiber == -1) { // daca nu mai este loc, redimensionam
        redim();
    }

    int pozitie = -1;
    auto it = this->iterator();
    while (it.valid()) {
        if (it.element().first == c) {
            pozitie = it.curent;
            break;
        }
        it.urmator();
    }

    if (pozitie == -1) { // inseamna ca nu exista element cu aceasi cheie
        int indexLiber = aloca();
        this->elems[indexLiber] = std::make_pair(c, v);
        this->lg++;
        return NULL_TVALOARE;
    } else { // inseamna ca mai exista element cu aceasi cheie
        auto valoare = this->elems[pozitie].second;
        this->elems[pozitie].second = v;
        return valoare;
    }
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
    auto it = this->iterator();
    while(it.valid()) {
        if (it.element().first == c) {
            return it.element().second;
        }
        it.urmator();
    }
	return NULL_TVALOARE;
}

TValoare Dictionar::sterge(TCheie c){
    int p = -1;
    auto it = this->iterator();
    while (it.valid()) {
        if (it.element().first == c) {
            p = it.curent;
            break;
        }
        it.urmator();
    }

    if (p == -1) return NULL_TVALOARE;
    int val;
    if (this->prim == p) {
        val = this->elems[p].second;
        this->elems[p]= std::make_pair(this->deleted, this->deleted);
        this->prim = this->urm[p];
        dealoca(p);
        this->lg --;
        return val;
    }else{
        auto q = this->prim;
        while (urm[q] != p) {
            q = this->urm[q];
        }
        this->urm[q] = this->urm[p];
        val = this->elems[p].second;
        this->elems[p] = std::make_pair(this->deleted, this->deleted);
        dealoca(p);
        this->lg--;
        return val;
    }
}

int Dictionar::dim() const {
    return this->lg;
}

bool Dictionar::vid() const{
    if (this->lg != 0) return false;
    return true;
}

IteratorDictionar Dictionar::iterator() const {
	return IteratorDictionar(*this);
}

void Dictionar::initSpatiuLiber() {
    for (int i = 0; i < capacitate - 1; i++) {
        this->urm[i] = i + 1;
        this->elems[i] = std::make_pair(this->empty, this->empty);
    }
    this->urm[capacitate - 1] = -1;
    this->primLiber = 0;
}

int Dictionar::aloca() { // daca returneaza -1 inseamna ca nu mai este loc
    int i = this->primLiber;
    this->primLiber = this->urm[this->primLiber];
    return i;
}

void Dictionar::dealoca(int i) {
    this->urm[i] = this->primLiber;
    this->primLiber = i;
}

void Dictionar::redim() {
    int newCapacitate = this->capacitate * 2;
    auto *newElems = new TElem [newCapacitate];
    auto *newUrm = new int [newCapacitate];
    for (int i = 0; i < this->lg; i++) {
        newElems[i] = elems[i];
        if (urm[i] == -1) newUrm[i] = i + 1;
        else newUrm[i] = urm[i];
    }

    // initializam spatiu liber pe care tocmai l-am creat
    for (int i = this->lg; i < newCapacitate - 1; i++) {
        newUrm[i] = i + 1;
        newElems[i] = std::make_pair(empty, empty);
    }
    newUrm[newCapacitate - 1] = -1;

    delete[] this->elems;
    delete[] this->urm;
    this->capacitate = newCapacitate;
    this->elems = newElems;
    this->urm = newUrm;
    this->primLiber = this->lg;
}