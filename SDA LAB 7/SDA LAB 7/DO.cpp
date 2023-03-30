#include "Iterator.h"
#include "DO.h"
#include <iostream>
/*
* [MADE BY] BALUTA IUSTINIAN-LUCIAN
*/
#include <exception>
using namespace std;

//Theta(1)
DO::DO(Relatie r) {
	/* de adaugat */
	rel = r;
	rad = nullptr;
}

//Theta(1)
Nod::Nod(TElem e, PNod st, PNod dr) {
	this->e.first = e.first;
	this->e.second = e.second;
	this->st = st;
	this->dr = dr;
}

//Theta(1)
TElem Nod::element() {
	return e;
}

//Theta(1)
PNod Nod::stanga() {
	return st;
}
//Theta(1)
PNod Nod::dreapta() {
	return dr;
}

//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
TValoare DO::adauga_rec(PNod& rad, TElem e) {
	// Cazul 1: arbore vid
	if (rad == nullptr)
	{

		rad = new Nod(e, nullptr, nullptr);
		return NULL_TVALOARE;

	}

	if (e.first == rad->e.first)
	{
		TValoare val = rad->e.second;
		rad->e.second = e.second;
		return val;
	}
	// Cazul 2: arbore nevid

	if (!rel(rad->e.first, e.first))
		// daca exista subarborele stang
		if (rad->st != nullptr)
			// inseram in subarbore
			return adauga_rec(rad->st, e);

		else
			// cream subarborele stang
		{
			rad->st = new Nod(e, nullptr, nullptr);
			//return NULL_TVALOARE;
		}

	if (rel(rad->e.first, e.first))
		// daca exista subarborele drept
		if (rad->dr != nullptr)
			// inseram in subarbore
			return adauga_rec(rad->dr, e);

		else
			// cream subarborele drept
		{
			rad->dr = new Nod(e, nullptr, nullptr);
			//return NULL_TVALOARE;
		}
	return NULL_TVALOARE;
}

//PNod DO::adauga_rec(PNod p, TElem e) {
//	if (p == nullptr) {
//		p = new Nod(e, nullptr, nullptr);
//	}
//	else {
//		//if (e.first == p->e.first)
//		//	p->e.second = e.second;
//		if (rel(e.first, p->e.first)) //se adauga in stanga
//			p->st = adauga_rec(p->st, e);
//		else //se adauga in dreapta
//			p->dr = adauga_rec(p->dr, e);
//	}
//	return p;
//}

//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
void DO::dim_rec(PNod p, int& dm) {
	if (p != nullptr) {
		dim_rec(p->st, dm);
		if (p->e.second != NULL_TVALOARE)
			dm++;
		dim_rec(p->dr, dm);
	}
}

//void DO::cauta_rec(PNod p, TCheie c, TValoare& val) {
//	if (p != nullptr) {
//		cauta_rec(p->st, c, val);
//		cauta_rec(p->dr, c, val);
//		if (p->e.first == c) {
//			val = p->e.second;
//			return;
//		}
//	}
//	//return NULL_TVALOARE;
//}

//PNod DO::cauta_adauga(PNod p, TCheie c, TValoare& val, PNod p1) {
//	if (p != nullptr) {
//		cauta_adauga(p->st, c, val, p1);
//		cauta_adauga(p->dr, c, val, p1);
//		if (p->e.first == c) {
//			val = p->e.second;
//			p1 = p;
//			return p1;
//		}
//	}
//}

//TValoare DO::sterge_rec(PNod p, TCheie c) {
//	if(p != nullptr)
//		if (p->e.first == c) {
//			TValoare val = p->e.second;
//			p->e.second = NULL_TVALOARE;
//			return val;
//		}
//	else {
//		sterge_rec(p->st, c);
//		sterge_rec(p->dr, c);
//	}
//	return NULL_TVALOARE;
//}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
TValoare DO::adauga(TCheie c, TValoare v) {
	TElem e{ c,v };
	return adauga_rec(rad, e);
}
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
TValoare DO::cautare(PNod p, TCheie c) {
	if (p == nullptr)
		return NULL_TVALOARE;

	if (p->e.first == c)
	// verificam daca am gasit nodul
		return p->e.second;

	// daca cheia este diferit in raport cu relatia
	if (!rel(p->e.first, c))
		// cautam in subarborele stang
		return cautare(p->st, c);

	else
		// altfel cautam in subarborele drept
		return cautare(p->dr, c);
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
TValoare DO::cauta(TCheie c) {
	///* de adaugat */
	//auto p = rad;
	//TValoare val = NULL_TVALOARE;
	//cauta_rec(rad, c, val);
	//rad = p;
	//return val;
	 // conditia de oprire din recursie
	PNod p = rad;
	return cautare(p, c);
	
}

void DO::__ArbStergeNod(PNod& legParinte)
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
{

	// salvam un pointer la nodul de sters
	PNod nod = legParinte;

	// daca avem un subarbore drept
	if (nod->dr != nullptr)
	{
		// facem legatura
		legParinte = nod->dr;

		// daca avem si un subarbore stang
		if (nod->st)
		{
			// cautam cel mai mic element din subarborele drept
			PNod temp = nod->dr;

			while (temp->st != nullptr)
				temp = temp->st;

			// si adaugam subarborele stang
			temp->st = nod->st;
		}

	}

	else
		// daca avem doar un subarbore stang
		if (nod->st != nullptr)
			// facem legatura la acesta
			legParinte = nod->st;

		else
			// daca nu avem nici un subnod
			legParinte = nullptr;
//	TValoare val = nod->e.second;
	// stergem nodul
	delete nod;
}


//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
TValoare DO::sterge(TCheie c) {

	// Cazul 1: arbore vid
	if (this->vid())
		return NULL_TVALOARE;

	// Cazul 2: stergere radacina
	if (rad->e.first == c)
	{
		// salvam un pointer la radacina
		PNod nod = rad;

		// daca avem un subarbore drept
		if (nod->dr != nullptr)
		{
			// facem legatura
			rad = nod->dr;

			// daca avem si un subarbore stang
			if (nod->st != nullptr)
			{
				// cautam cel mai mic element din subarborele drept
				PNod temp = nod->dr;
				while (temp->st != nullptr)
					temp = temp->st;

				// si adaugam subarborele stang
				temp->st = nod->st;

			}

		}

		else
			// daca avem doar un subarbore stang
			if (nod->st != nullptr)
				// facem legatura la acesta
				rad = nod->st;

			else
				// daca nu avem nici un subnod
			{
				TValoare val = rad->e.second;
				rad = nullptr;
				return val;
			}

		// stergem vechea radacina
		TValoare val = nod->e.second;
		delete nod;
		return val;
	}

	// Cazul 3: stergere nod in arbore nevid

	// cautam legatura la nod in arbore

	// si stergem nodul (daca exista)

	PNod nodCurent = rad;
	while (true)
	{
		if (!rel(nodCurent->e.first, c))
			if (nodCurent->st == nullptr)
			{
				return NULL_TVALOARE;
				break; // nodul nu exista
			}

			else
				if (nodCurent->st->e.first == c)

				{
					TValoare val = nodCurent->st->e.second;
					__ArbStergeNod(nodCurent->st);
					return val;
					// nodul de sters este descendentul stang
				}
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->st;

		else
			if (nodCurent->dr == nullptr)
			{
				return NULL_TVALOARE;
				break; // nodul nu exista
			}

			else
				if (nodCurent->dr->e.first == c)
				{
					// nodul de sters este descendentul drept
					TValoare val = nodCurent->dr->e.second;
					__ArbStergeNod(nodCurent->dr);
					return val;
				}

				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->dr;
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
int DO::dim() {
	/* de adaugat */
	auto p = rad;
	int dm = 0;
	dim_rec(p, dm);
	return dm;
}

//verifica daca dictionarul e vid
//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
bool DO::vid() {
	/* de adaugat */
	if (dim() != 0)
		return false;
	return true;
}

void DO::distrug_rec(PNod p) {
	//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
	if (p != nullptr) {
		distrug_rec(p->stanga());
		distrug_rec(p->dreapta());
		delete p;
	}
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	//O(log2n), unde n=numarul de noduri din DO reprezentat prin ABC (caz favorabil: Theta(1), caz defavorabil: Theta(log2n) )
	distrug_rec(rad);
	
}
