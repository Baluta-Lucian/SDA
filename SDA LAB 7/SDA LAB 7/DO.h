#pragma once

typedef int TCheie;
typedef int TValoare;
#define NULL_TVALOARE -10000

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class Nod;

//Arborii de cautare permit regasirea rapida a informatiilor(O(log2n)) 
//atat timp cat arborele este echilibrat.In cazul cel mai defavorabil, 
//timpul de cautare este identic cu cel al unei liste simplu inlantuite.

//se defineste tipul PNod ca fiind adresa unui Nod

typedef Nod* PNod;

class Nod

{

public:

	friend class DO;

	//constructor

	Nod(TElem e, PNod st, PNod dr);

	TElem element();

	PNod stanga();

	PNod dreapta();


private:

	TElem e;

	PNod st, dr;

};


class DO {
	friend class Iterator;
private:
	/* aici e reprezentarea */
	Relatie rel;
	PNod rad;

	TValoare adauga_rec(PNod& rad, TElem e);

	//PNod adauga_rec(PNod p, TElem e);

	void distrug_rec(PNod);

	void dim_rec(PNod p, int& dm) ;

	void cauta_rec(PNod p, TCheie c, TValoare& val);

	PNod cauta_adauga(PNod p, TCheie c, TValoare& val, PNod p1);

	TValoare sterge_rec(PNod p, TCheie c);

	TValoare cautare(PNod p, TCheie c);

	void __ArbStergeNod(PNod& legParinte);
public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v) ;

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) ;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() ;

	//verifica daca dictionarul e vid
	bool vid();

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// destructorul dictionarului
	~DO();

};
