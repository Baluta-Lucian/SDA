#pragma once
#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modifica(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEMENT);
}

void test_sumaDiagonalaPrincipala() {
	Matrice m(3, 3);
	m.modifica(0, 0, 10);
	m.modifica(1, 1, 20);
	m.modifica(2, 2, 10);

	TElem sum = m.sumaDiagonalaPrincipala();
	assert(sum == 40);

	m.modifica(1, 1, 5);
	TElem sum2 = m.sumaDiagonalaPrincipala();
	assert(sum2 == 25);

	m.modifica(0, 0, 1);
	TElem sum3 = m.sumaDiagonalaPrincipala();
	assert(sum3 == 16);
}