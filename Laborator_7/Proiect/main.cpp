#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;

int main() {
    testFuncNoua();
    cout << "testFuncNoua()" << endl;
    testAll();
    testAllExtins();
    cout << "That's all!" << endl;
}

//5.TAD Colecție cu elemente de tip TComparabil – reprezentare prin perechi de
//forma (element, frecvență), folosind un ABC reprezentat înlănțuit, cu înlănțuiri reprezentate pe tablou.