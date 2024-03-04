#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;

int main() {
	testAll();
	testAllExtins();

    testFunctionalitateNoua();

    cout << "End";
}

//5. TAD Colecție – reprezentare memorând toate elementele, folosind
//o TD cu rezolvare coliziuni prin adresare deschisă, dispersia dublă.