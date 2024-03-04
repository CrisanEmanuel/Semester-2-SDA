#pragma once
#include <utility>

#define NULL_TVALOARE (-1)

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;
typedef bool(*Relatie)(TCheie, TCheie);

struct Nod {
    TElem info; //informatia
    Nod *next; // adresa catre nodul urmator
    Nod *prev; // adresa catre nodul precedent
};

class  Iterator;

class DO {

	friend class Iterator;

private:
    Nod *head; // adresa catre primul nod
    Nod *tail; // adresa catre ultimul nod
    Relatie R; // relatia care se stabileste intre chei
    int lg; // numarul de noduri

public:
	// constructorul implicit al dictionarului
	explicit DO(Relatie r);

	// adauga o pereche (cheie, valoare) in dictionar
	// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    /// Complexitate Θ(n);
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    /// Complexitate Θ(n);
	[[nodiscard]] TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    /// Complexitate Θ(n);
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
    /// Complexitate Θ(1);
	[[nodiscard]] int dim() const;

	//verifica daca dictionarul e vid
    /// Complexitate Θ(1);
	[[nodiscard]] bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
    /// Complexitate Θ(1);
	[[nodiscard]] Iterator iterator() const;

	// destructorul dictionarului
    /// Complexitate Θ(n);
	~DO();

    // functionalitate data in timpul labului
    /// Complexitate Θ(1);
    void goleste();
};
