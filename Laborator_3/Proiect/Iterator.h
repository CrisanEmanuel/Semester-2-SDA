#pragma once
#include "DO.h"

class Iterator{
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	explicit Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	/* aici e reprezentarea specifica a iteratorului */
    Nod *it;

public:

		// reseteaza pozitia iteratorului la inceputul containerului
        /// Complexitate Θ(1)
		void prim();

		// muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        /// Complexitate Θ(1)
		void urmator();

		// verifica daca iteratorul e valid (indica un element al containerului)
        /// Complexitate Θ(1)
		[[nodiscard]] bool valid() const;

		// returneaza valoarea elementului din container referit de iterator
		// arunca exceptie daca iteratorul nu e valid
        /// Complexitate Θ(1)
		[[nodiscard]] TElem element() const;
};

