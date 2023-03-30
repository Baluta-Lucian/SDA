
#include "Colectie.h"
#include <iostream>
#include "TestScurt.h"
#include "TestExtins.h"
using namespace std;

void creeazaColectie(Colectie& c) {
	c.adauga(2);
	c.adauga(4);
	c.adauga(2);
	c.adauga(5);
	c.adauga(4);
}

void tiparesteColectie(Colectie& c) {
	IteratorColectie it = c.iterator();
	while (it.valid()) {
		cout << it.element() << ' ';
		it.urmator();
	}
}

int main() {
	//4.TAD Colecție–reprezentare folosind o LDI  cu perechi de forma (element, frecvență)

	Colectie c;
	creeazaColectie(c);
	tiparesteColectie(c);
	testAll();
	testAllExtins();
	cout << "END";
	return 0;
}
