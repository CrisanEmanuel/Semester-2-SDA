#pragma once
#include <utility>

#define NULL_TVALOARE (-1)

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie,TValoare> TElem;

class IteratorDictionar;

class Dictionar {
	friend class IteratorDictionar;

	private:
    int capacitate, prim, primLiber, lg, empty, deleted;
    TElem *elems;
    int *urm;

    void redim();
    void initSpatiuLiber();
    int aloca();
    void dealoca(int i);

	public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	// cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	[[nodiscard]] TValoare cauta(TCheie c) const;

	// sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	// returneaza numarul de perechi (cheie, valoare) din dictionar
	[[nodiscard]] int dim() const;

	// verifica daca dictionarul e vid
	[[nodiscard]] bool vid() const;

	// se returneaza iterator pe dictionar
	[[nodiscard]] IteratorDictionar iterator() const;

	// destructorul dictionarului	
	~Dictionar();
};


