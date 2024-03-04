#include "Coada.h"
#include <exception>

using namespace std;

Coada::Coada(int cp) {
    this->capacity = cp;
    this->rear = 0;
    this->front = 0;
    this->elems = new TElem[this->capacity];
}

void Coada::adauga(TElem elem) {
    if (this->rear == this->capacity){
        int k = 0;
        auto * NewQ = new TElem[this->capacity * 2];
        for (int i = this->front; i < this->rear; i++){
            NewQ[k++] = this->elems[i];
        }
        this->capacity *= 2;
        delete[] this->elems;
        this->elems = NewQ;
        this->elems[this->rear] = elem;
        this->rear++;
    }else{
        this->elems[this->rear] = elem;
        this->rear++;
    }
}

//arunca exceptie daca coada e vida
TElem Coada::element() const {
    if (this->front == this->rear) throw exception();
    return this->elems[this->front];
}

//arunca exceptie daca coada e vida
TElem Coada::sterge() {
    if (this->front == this->rear) throw exception();

	TElem elemDel = this->elems[this->front];
    if (this->front == this->capacity){
        this->front = 0;
    }else{
        this->front += 1;
    }
    return elemDel;
}

bool Coada::vida() const {
    if (this->rear == this->front) return true;
    return false;
}

bool Coada::plina() const{
    if (this->rear == this->capacity) return true;
    return false;
}

Coada::~Coada() {
	delete[] this->elems;
}