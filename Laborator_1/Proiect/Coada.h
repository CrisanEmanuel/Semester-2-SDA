#pragma once
//using namespace std;

typedef int TElem;

class Coada
{
	private:
        int capacity;
        int front;
        int rear;
        TElem* elems;

	public:
		//constructorul implicit
        /// complexitate de timp Θ(1)
		explicit Coada(int);

		//adauga un element in coada
        /// complexitate de timp Θ(n)
		void adauga(TElem e);

		//acceseaza elementul cel mai devreme introdus in coada 
		//arunca exceptie daca coada e vida
        /// complexitate de timp Θ(1)
		TElem element() const;

		//sterge elementul cel mai devreme introdus in coada si returneaza elementul sters (principiul FIFO)
		//arunca exceptie daca coada e vida
        /// complexitate de timp Θ(1)
		TElem sterge();

		//verifica daca coada e vida;
        /// complexitate de timp Θ(1)
		bool vida() const;

        //verifica daca coada e vida; functionalitate data in timpul labului
        /// complexitate de timp Θ(1)
        bool plina() const;

		// destructorul cozii
        /// complexitate de timp Θ(1)
		~Coada();
};