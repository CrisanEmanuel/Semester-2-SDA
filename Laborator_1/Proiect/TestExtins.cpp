#include <cassert>
#include "Coada.h"
#include "TestExtins.h"
//#include <vector>
#include <exception>

using namespace std;

void testCreeaza() {
	Coada c(5);
	assert(c.vida() == true);
	try {
		c.element(); //daca e vida ar trebui sa arunce exceptie
		assert(false); //daca nu a aruncat exceptie, vrem sa avem un assert care da fail
	}
	catch (exception&) {
		assert(true);  
	}
	try {
		c.sterge(); //daca e vida ar trebui sa arunce exceptie
		assert(false); //daca nu a aruncat exceptie, vrem sa avem un assert care da fail
	}
	catch (exception&) {
		assert(true);
	}
}

void testAdauga() {
	Coada c(5);
	for (int i = 0; i < 10; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	assert(c.element() != -9999);
	assert(c.element() == 0);

	assert(c.sterge() == 0);
	assert(c.element() == 1);
}

void testSterge() {
	Coada c(5);
	for (int i = 0; i < 10; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	// acum in aceeasi ordine ar trebui sa fie si sterse
	for (int i = 0; i < 10; i++) {
		assert(c.sterge()==i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == true);
}

void testQuantity() {//scopul e sa adaugam multe date
	Coada c(5);
	for (int i = 1; i <= 10; i++) {
		for (int j = 30000; j >= -3000; j--) {
			c.adauga(i+j);
		}
	}

	for (int i = 1; i <= 10; i++) {
		for (int j = 30000; j >= -3000; j--) {
			assert(c.sterge() == i+j);
		}
	}
}

void testNou(){
    Coada c(3);
    c.adauga(5);
    c.adauga(4);
    c.adauga(56);

    try{
        c.adauga(12);
        assert(false);
    }catch(exception&){
        assert(true);
    }

    assert(c.plina() == true);

    try{
        Coada c2(-3);
        assert(false);
    }catch(exception&){
        assert(true);
    }
}

void testAllExtins() {
    testCreeaza();
    testAdauga();
    testSterge();
    testQuantity();
    //testNou();
}