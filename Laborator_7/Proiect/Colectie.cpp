#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Colectie::Colectie() {
    this->capacity = MAX_CAP;
    this->root = 0;
    this->empty = 999999;
    this->primLiber = 1; // root + 1
    this->length = 0;
    this->elems = new TPereche [this->capacity];
    this->st = new TElem [this->capacity];
    this->dr = new TElem [this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->elems[i].first = this->empty;
        this->elems[i].second = -1;
        this->st[i] = this->empty;
        this->dr[i] = this->empty;
    }
}

int Colectie::add_rec(int poz, TElem e) {
    if (elems[poz].first == empty){
        elems[poz].first = e;
        elems[poz].second++;
        length++;
        primLiber++;
    }
    if (elems[poz].first == e) {
        elems[poz].second++;
    }
    if (e < elems[poz].first && st[poz] != empty) {
        st[poz] = add_rec(st[poz], e);
    } else if (e > elems[poz].first && dr[poz] != empty) {
        dr[poz] = add_rec(dr[poz], e);
    } else if (e < elems[poz].first && st[poz] == empty) {
        st[poz] = add_rec(primLiber, e);
    } else if (e > elems[poz].first && dr[poz] == empty) {
        dr[poz] = add_rec(primLiber, e);
    }
    return poz;
}

void Colectie::adauga(TElem e) {
    if (this->vida()) {
        this->elems[root] = std::make_pair(e, 1);
        this->length++;
        return;
    }

    if (e == this->elems[root].first) { // verificam radacina
        this->elems[root].second++;
        return;
    }

    if (this->length == this->capacity - 2) redim(); // redimensionam

    add_rec(root,e);
}

int Colectie::minim(int poz) {
    if (st[poz] == empty) return poz;
    else return minim(st[poz]);
}

int Colectie::sterge_rec(int poz, TElem e) {
    int aux;
    if (poz == empty) return empty;
    else if (e < elems[poz].first)
        st[poz] = sterge_rec(st[poz], e);
    else if (e > elems[poz].first )
        dr[poz] = sterge_rec(dr[poz], e);
    else if (dr[poz] != empty && st[poz] != empty) {
        if (elems[poz].second == 1) {
            aux = minim(dr[poz]);
            elems[poz].first = elems[aux].first;
            elems[poz].second = elems[aux].second;
            dr[poz] = sterge_rec(dr[poz], elems[aux].first);
            length--;
        } else {
            elems[poz].second--;
        }
    } else {
        aux = poz;
        if (elems[aux].second == 1) {
            if (st[aux] == empty) {
                poz = dr[poz];
                dr[aux] = empty;
            } else if (dr[aux] == empty) {
                poz = st[poz];
                st[aux] = empty;
            }
            elems[aux].first = empty;
            elems[aux].second = -1;
            length--;
        } else elems[aux].second--;
    }
    return poz;
}

bool Colectie::sterge(TElem e) {
    if (vida()) return false;

    int aux;
    if (elems[root].first == e) {
        if (dr[root] != empty && st[root] != empty) {
            if (elems[root].second == 1) {
                aux = minim(dr[root]);
                elems[root].first = elems[aux].first;
                elems[root].second = elems[aux].second;
                dr[root] = sterge_rec(dr[root], elems[aux].first);
                length--;
                return true;
            } else if (elems[root].second > 1){
                elems[root].second--;
                return true;
            }
        } else {
            aux = root;
            if (elems[root].second == 1) {
                if (st[aux] == empty) {
                    root = dr[root];
                    dr[aux] = empty;
                } else if (dr[aux] == empty) {
                    root = st[root];
                    st[aux] = empty;
                }
                elems[aux].first = empty;
                elems[aux].second = -1;
                length--;
                return true;
            } else if (elems[root].second > 1) {
                elems[root].second--;
                return true;
            }
        }
    }
    auto dim_initiala = this->dim();
    sterge_rec(root, e);
    auto dim_ulterioara = this->dim();
    if (dim_initiala > dim_ulterioara) return true;
    else return false;
}

bool Colectie::cauta_rec(int poz, TElem e) {
    if (poz == empty) return false;
    if (elems[poz].first == e) return true;

    if (e < elems[poz].first)
        return cauta_rec(st[poz], e);
    else if (e > elems[poz].first)
        return cauta_rec(dr[poz], e);
    return false;
}

bool Colectie::cauta(TElem e) {
	if (this->vida()) return false;

    if (this->elems[root].first == e) return true; // verificam radacina

    return cauta_rec(root, e);
}

int Colectie::nrAparitii_rec(int poz, TElem e) {
    if (poz == empty) return 0;
    if (elems[poz].first == e) return elems[poz].second;

    if (e < elems[poz].first)
        return nrAparitii_rec(st[poz], e);
    else if (e > elems[poz].first)
        return nrAparitii_rec(dr[poz], e);
    return 0;
}

int Colectie::nrAparitii(TElem e) {
    if (vida()) return 0;

    if (this->elems[root].first == e) return elems[root].second;

    return nrAparitii_rec(root, e);
}

int Colectie::dim() const {
	int dim = 0;
    for (int i = 0; i < capacity;i++)
        if (elems[i].first != empty) {
            dim += elems[i].second;
        }
    return dim;
}

bool Colectie::vida() const {
	return this->length == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

Colectie::~Colectie() {
	delete[] this->elems;
    delete[] this->st;
    delete[] this->dr;
}

void Colectie::redim() {
    int newCapacity = this->capacity * 2;
    auto *newElems = new TPereche [newCapacity];
    auto *newSt = new TElem [newCapacity];
    auto *newDr = new TElem [newCapacity];
    for (int i = 0; i < this->length; i++) {
        newElems[i] = this->elems[i];
        newSt[i] = this->st[i];
        newDr[i] = this->dr[i];
    }

    for (int i = this->length; i < newCapacity; i++) {
        newSt[i] = this->empty;
        newDr[i] = this->empty;
        newElems[i] = std::make_pair(this->empty,-1);
    }

    delete[] elems;
    delete[] st;
    delete[] dr;
    this->capacity = newCapacity;
    this->primLiber = this->length;
    this->elems = newElems;
    this->dr = newDr;
    this->st = newSt;
}

void Colectie::inordine(int poz) {
    if (poz == empty) {
        return;
    }
    inordine(st[poz]);
    cout << '('<< elems[poz].first << ',' << elems[poz].second << ')' <<  ' ';
    inordine(dr[poz]);
}

void Colectie::afiseaza() {
    cout << "EL: ";
    for (int i = 0; i < length; i++){
        if (elems[i].first != empty)
            cout << elems[i].first  <<  ' ';
        else cout << '('<< '-' << ',' << elems[i].second << ')' <<  ' ';
    }
    cout << endl;
    cout << "St: ";
    for (int i = 0; i < length;i++) {
        if (st[i] == empty) cout << "- ";
        else if (elems[i].first >= 10) cout << ' ' << st[i] << ' ';
        else cout << st[i] << ' ';
    }
    cout << endl;
    cout << "Dr: ";
    for (int i = 0; i < length;i++) {
        if (dr[i] == empty) cout << "- ";
        else if (elems[i].first >=10) cout << ' ' << dr[i] << ' ';
        else cout << dr[i] << ' ';
    }
    cout << endl;
    cout << endl;
}

/// Complexitate w:θ(numar_elemente) b:θ(1) totala: O(numar_elemente)
int Colectie::diferenta() const {
    if (this->vida()) return -1;
    auto it = this->iterator();
    int minim = it.element();
    it.urmator();
    int maxim = it.element();
    while (it.valid()) {
        auto aux = it.element();
        if (aux < minim) minim = aux;
        if (aux > maxim) maxim = aux;
        it.urmator();
    }
    return maxim - minim;
}
