#include "TestScurt.h"
#include <cassert>
#include "Coada.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
	Coada c(5);
	assert(c.vida() == true);
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	assert(c.vida() == false);
	assert(c.element() == 5);
	assert(c.sterge() == 5);
	assert(c.element() == 1);
	assert(c.sterge() == 1);
	assert(c.element() == 10);
	assert(c.sterge() == 10);
	assert(c.vida() == true);
}