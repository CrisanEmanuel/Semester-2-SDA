#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

DO::DO(Relatie r) {
    R = r;
    head = nullptr;
    tail = nullptr;
    lg = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	Nod *n = this->head;
    Nod *newNode = new Nod;
    newNode->info = make_pair(c, v);

    //daca lista este gola
    if (vid()) {
        newNode->prev = nullptr;
        newNode->next = nullptr;
        this->head = newNode;
        this->tail = newNode;
        this->lg++;
        return NULL_TVALOARE;
    }

    // adauga nodul la inceputul listei, in cazul in care primul nod are aceasi cheie, inlocuieste doar valoarea
    if(this->R(c, n->info.first)) {
        if(c == n->info.first) {
            auto value = n->info.second;
            n->info.second = newNode->info.second;
            return value;
        }else {
            this->head->prev = newNode;
            newNode->next = head;
            newNode->prev = nullptr;
            this->head = newNode;
            this->lg++;
            return NULL_TVALOARE;
        }
    }

    while(n->next && !this->R(c, n->next->info.first))
        n = n->next;

    // adauga nodul la final sau daca nu verifica daca mai exista cheia daca nu adauga unde apuca
    if (n->next == nullptr) {
        n->next = newNode;
        newNode->prev = n;
        newNode->next = nullptr;
        this->tail = newNode;
    }else if (n->next->info.first == c) {
        auto value = n->next->info.second;
        n->next->info.second = newNode->info.second;
        return value;
    }else {
        n->next->prev = newNode;
        newNode->next = n->next;
        n->next = newNode;
        newNode->prev = n;
    }
    this->lg++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    Nod *n = head;
    while (n) {
        if (n->info.first == c)
            return n->info.second;
        n = n->next;
    }
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    Nod *n = this->head;

    // daca lista este goala
    if (this->vid()){
        return NULL_TVALOARE;
    }

    // daca nodul cautat este primul si este singurul din lista sau daca este primul si nu este singurul din lista
    if (c == n->info.first) {
        if (this->dim() == 1) {
            auto key = n->info.second;
            this->head = nullptr;
            this->tail = nullptr;
            delete n;
            this->lg = 0;
            return key;
        }
        else {
            auto key = n->info.second;
            this->head = n->next;
            this->head->prev = nullptr;
            delete n;
            this->lg--;
            return key;
        }
    }

    // daca nodul cautat nu este primul nici ultimul
    while (n != this->tail) {
        if (n->info.first == c){
            auto key = n->info.first;
            n->prev->next = n->next;
            n->next->prev = n->prev;
            delete n;
            this->lg--;
            return key;
        }
        n = n->next;
    }

    // daca nodul cautat este ultimul
    if(n->info.first == c) {
        auto key = n->info.first;
        this->tail = n->prev;
        n->prev->next = nullptr;
        delete n;
        this->lg--;
        return key;
    }
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return this->lg;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
    while (this->head) {
        Nod *aux = this->head;
        this->head = this->head->next;
        delete aux;
    }
}

void DO::goleste() {
    this->lg = 0;
}