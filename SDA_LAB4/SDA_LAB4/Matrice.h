#pragma once
#include <iostream>
#include <utility>

typedef int TElem;
typedef std::pair <int, int> RC;
typedef std::pair <RC, int> TValue;

#define NULL_TELEMENT 0

class Nod {
public:
	Nod* urm = nullptr;
	TValue el;
};

class Matrice {
private:
	Nod* prim;
	TValue* e;
	int cap, ln;
	int rows, columns;
	int firstFree;
	int* urm;

	int	allocate();

	void deallocate(int i);

	int creeazaNod(TValue e);

	void adauga(TValue e);
public:
	Matrice(int nrRows, int nrColumns);

	~Matrice() {};

	TElem element(int i, int j) const;

	int nrLinii() const;

	int nrColoane() const;
	
	TElem modifica(int i, int j, TElem e);

	TElem sumaDiagonalaPrincipala();
};