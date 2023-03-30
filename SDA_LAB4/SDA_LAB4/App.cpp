#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;


int main() {
	//1.TAD  Matrice-reprezentare  sub  forma  unei  matrice rare, 
	//folosind  o  LSI  cu  triplete  de  forma <linie, coloana, valoare> (valoare!=0), 
	//memorate in ordine lexicografica dupa (linie, coloana).
	testAll();
	test_sumaDiagonalaPrincipala();
	testAllExtins();

	cout << "End";
}
