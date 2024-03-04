#pragma once
#include "IteratorColectie.h"
#include <exception>
#include <cmath>

#define maxCapacity 13
#define NULL_TELEM (-1)
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	int lg, capacitate;
    TElem *hashTable;
    TElem gol, sters;

    static int hCode(int k);
    [[nodiscard]] int h1(TElem k) const;
    [[nodiscard]] int h2(TElem k) const;
    [[nodiscard]] int h(TElem k, int i) const;
    static int urmPrimMaiMareCa(int x);
    static bool prim(int x);

public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		[[nodiscard]] bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		[[nodiscard]] int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		[[nodiscard]] int dim() const;

		//verifica daca colectia e vida;
		[[nodiscard]] bool vida() const;

		//returneaza un iterator pe colectie
		[[nodiscard]] IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();

        ///functionalitate noua
        // returnează elementul cu cea mai mare frecvență din colecție
        // (în cazul în care există mai multe elemente cu aceeași frecvență maximă, oricare dintre ele poate fi returnat)
        // daca colecția este vidă, se returnează NULL_TELEM
        [[nodiscard]] TElem celMaiFrecvent() const;
};

