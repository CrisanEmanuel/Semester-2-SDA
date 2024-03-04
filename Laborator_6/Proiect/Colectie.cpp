#include "Colectie.h"
using namespace std;

///Θ(capacitate)
Colectie::Colectie() {
	this->capacitate = maxCapacity;
    this->lg = 0;
    this->gol = -9999;
    this->sters = -9998;
    this->hashTable = new TElem [maxCapacity];
    for (int i = 0; i < maxCapacity; i++){
        this->hashTable[i] = this->gol;
    }
}

///BC: Θ(1), WC: Θ(nrElements ^ 2), Overall: O(nrElements ^ 2)
void Colectie::adauga(TElem elem) {
    if(this->lg == this->capacitate)
    {
        //redimensoinam si dam rehash daca nu avem suficient spatiu in hashTable
        int prim = urmPrimMaiMareCa(this->capacitate * 2);
        int capVeche = this->capacitate;
        this->capacitate = prim;
        TElem *oldTable = this->hashTable;
        this->hashTable = new TElem [capacitate];
        this->lg = 0;
        for(int j = 0; j < this->capacitate; j++)
        {
            this->hashTable[j] = this->gol;
        }
        for(int j = 0; j < capVeche; j++)
        {
            this->adauga(oldTable[j]);
        }
        delete[] oldTable;
    }

    int i = 0;
    int poz = h(elem, i);
    while (i < this->capacitate && this->hashTable[poz] != this->gol && this->hashTable[poz] != this->sters)
    {
        i++;
        poz = h(elem,i);
    }
    this->hashTable[poz] = elem;
    this->lg++;
}

///BC: Θ(1), WC: Θ(nrElements), Complexitate totala: O(nrElements)
bool Colectie::sterge(TElem elem) {
    int i = 0;
    int pos = h(elem, i);
    while(i < this->capacitate && this->hashTable[pos] != elem && this->hashTable[pos] != this->gol)
    {
        i++;
        pos = h(elem,i);
    }
    if(i == this->capacitate || this->hashTable[pos] == this->gol)
        return false;

    this->hashTable[pos] = this->sters;
    this->lg--;
    return true;
}

///BC: Θ(1), WC: Θ(nrElements), Complexitate totala: O(nrElements)
bool Colectie::cauta(TElem elem) const {
	int i = 0;
    int poz = h(elem, i);
    while(i < this->capacitate && this->hashTable[poz] != elem && this->hashTable[poz] != this->gol)
    {
        i++;
        poz = h(elem, i);
    }
    if(i == this->capacitate || this->hashTable[poz] == this->gol)
        return false;
    return true;
}

///Θ(nrElements)
int Colectie::nrAparitii(TElem elem) const {
	int nrAparitii = 0;
    int i = 0;
    int poz = h(elem, i);
    while (i < this->capacitate && this->hashTable[poz] != this->gol) {
        if (this->hashTable[poz] == elem) {
            nrAparitii++;
        }
        i++;
        poz = h(elem, i);
    }
	return nrAparitii;
}

///Θ(1)
int Colectie::dim() const {
	return this->lg;
}

///Θ(1)
bool Colectie::vida() const {
	if (this->lg != 0) return false;
	return true;
}

///Θ(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

///Θ(1)
Colectie::~Colectie() {
	delete[] this->hashTable;
}

///Θ(1)
int Colectie::hCode(int k) {
    return abs(k);
}

///Θ(1)
int Colectie::h1(TElem k) const {
    return hCode(k) % this->capacitate;
}

///Θ(1)
int Colectie::h2(TElem k) const {
    return 1 + (hCode(k) % (this->capacitate - 1));
}

///Θ(1)
int Colectie::h(TElem k, int i) const {
     return (h1(k) + i * h2(k)) % this->capacitate;
}

///O(n)
int Colectie::urmPrimMaiMareCa(int x) {
    x++;
    while (!prim(x)) x++;
    return x;
}

///O(sqrt(x))
bool Colectie::prim(int x) {
    if (x < 2 || (x > 2 && x % 2 == 0))
        return false;
    for (int d = 3; d * d <= x; d +=2) {
        if (x % d == 0) return false;

    return true;
}

TElem Colectie::celMaiFrecvent() const {
    if (this->vida()) return NULL_TELEM;

    int nrAparitiiMaxima = 0, element;
    IteratorColectie it = this->iterator();
    while (it.valid()) {
        int aux = this->nrAparitii(it.element());
        if (aux > nrAparitiiMaxima) {
            nrAparitiiMaxima = aux;
            element = it.element();
        }
        it.urmator();
    }
    return element;
}