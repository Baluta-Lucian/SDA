#pragma once
#include "DO.h"
#include <stack>

class Iterator {
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	/* aici e reprezentarea specifica a iteratorului */
	std::stack <PNod> st;
	PNod curent;
	PNod radacina;
	PNod parinte;
	PNod copil;
	int ok;
	void fillStack(PNod nod) {
		while (nod != nullptr) {
			st.push(nod);
			nod = nod->stanga();
		}
	}
public:
	
	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	void avanseazaKPasi(int k);
	bool validK(int k);

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;
};
