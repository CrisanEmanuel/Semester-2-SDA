#pragma once
#include <utility>
#define MAX_CAP 13

typedef int TElem;
typedef int TFreq;
typedef std::pair<TElem, TFreq> TPereche; // pereche de element cu numarul de aparitii a acestuia
typedef bool(*Relatie)(TElem, TElem);

// in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

    friend class IteratorColectie;

private:
    TPereche *elems;
    int *st, *dr;
    int capacity, length, root, primLiber;
    int empty;
public:
    //constructorul implicit
    Colectie();

    //adauga un element in colectie
    void adauga(TElem e);
    int add_rec(int poz, TElem e);

    //sterge o aparitie a unui element din colectie
    //returneaza adevarat daca s-a putut sterge
    bool sterge(TElem e);
    int sterge_rec(int poz, TElem e);

    //verifica daca un element se afla in colectie
    [[nodiscard]] bool cauta(TElem e);
    bool cauta_rec(int poz, TElem e);

    //returneaza numar de aparitii ale unui element in colectie
    [[nodiscard]] int nrAparitii(TElem e);
    int nrAparitii_rec(int poz, TElem e);

    //intoarce numarul de elemente din colectie;
    [[nodiscard]] int dim() const;

    //verifica daca colectia e vida;
    [[nodiscard]] bool vida() const;

    //returneaza un iterator pe colectie
    [[nodiscard]] IteratorColectie iterator() const;

    // destructorul colectiei
    ~Colectie();

    // marim capacitatea
    void redim();

    // returneaza pozitia elementului minim
    int minim(int poz);

    // afiseaza elementele in ordine crescatoare
    void inordine(int poz);

    // afiseaza elementele si inlantuirea pe tablou
    void afiseaza(); // facuta de mine

    // returnează diferența dintre valoarea maximă și cea minimă (presupunem valori întregi)
    // daca colecția este vidă se returnează -1
    [[nodiscard]] int diferenta() const; ///functionalitate noua
};