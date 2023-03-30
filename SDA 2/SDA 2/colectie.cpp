#include "colectie.h"
#include <iostream>

Nod::Nod(TElem e, int frecv, PNod urm, PNod ant)
{
	this->e = e;
	this->frecv = frecv;
	this->urm = urm;
	this->ant = ant;
}

TElem Nod::element()
{
	return e;
}

int Nod::frecventa() const
{
	return frecv;
}

PNod Nod::urmator()
{
	return urm;
}


Colectie::Colectie()
{
	prim = nullptr;
}

bool Colectie::cauta(TElem elem) const
{
	PNod p = prim;
	while (p != nullptr)
	{
		if (elem == p->e)
		{
			return true;
		}
		p = p->urm;
	}
	
	return false;
}

int Colectie::dim() const
{
	int dim = 0;
	PNod p = prim;
	while (p != nullptr)
	{
		dim += p->frecv;
		p = p->urm;
	}
	return dim;

}

void Colectie::adauga(TElem e)
{
	if (cauta(e))
	{
		PNod p = prim;
		while (p != nullptr)
		{
			if (p->e == e)
				p->frecv++;
			p = p->urm;
		}
	}
	else {
		
		PNod q = new Nod(e, 1, nullptr, nullptr);
		if (prim == nullptr)
			prim = q;
		else
		{
			q->urm = prim;
			prim->ant = q;
			prim = q;
		}
	}
}

int Colectie::nrAparitii(TElem e) const
{
	if (cauta(e))
	{
		PNod p = prim;
		while (p != nullptr)
		{
			if (e == p->e)
			{
				return p->frecv;
			}
			p = p->urm;
		}
	}

	return 0;
}

bool Colectie::sterge(TElem elem)
{
	if (cauta(elem))
	{
		PNod p = prim;
		while (p->e != elem)
		{
			p = p->urm;
		}
		p->frecv--;
		if (p->frecv == 0)
		{
			if(prim == p)
				prim = prim->urm;
			if (p->urm != nullptr)
				p->urm->ant = p->ant;
			if (p->ant != nullptr)
				p->ant->urm = p->urm;
			delete p;
		}
		return true;
	}
	return false;
}

int Colectie::eliminaAparitii(int nr, TElem elem)
{

	/*
	* eliminaAparitii(nr, elem)
	* pre:	nr (input)[int] -> numarul de aparitii de trebuiesc eliminate
	*		elem (input)[TElem] -> elementul din colectie de la care dorim sa eliminam nr aparitii
	* post:	Numarul de elemente sterse || exception : in cazul in care numarul este negativ
	* Subalgoritm eliminaAparitii
	*	deleted_elems<-0;
	*	daca nr < 0 atunci
	*		@arunca exceptie
	*	sf daca
	*	daca cauta(elem) = true atunci
	*		Pnod p <- prim
	*		cat timp [p].e != elem executa
	*			p <- [p].urm
	*		sf cat timp
	*		daca [p].frecv > nr atunci
	*			deleted_elems <- nr;
	*			[p].frecv <- [p].frecv - nr;
	*	
	*		altfel 
	*			deleted_elems = [p].frecv;
	*			daca prim = p atunci
	*				prim = [prim].urm;
	*			sf daca
	*			daca [p].urm != NIL atunci
	*				[p.urm].ant = [p].ant
	*			sf daca
	*			daca [p].ant != NILL atunci
	*				[p.ant].urm = [p].urm
	*			sf daca
	*			@dealocam p
	*		sf daca
	*		@returnam deleted_elems
	*	sf daca
	*	@returnam deleted_elems
	* sf subalgoritm
	*/
	//T(n) = (1 + 2 + . . . + n)/n = (n + 1)/2 -> caz mediu
	//T(n) ∈ O(n) (n -> reprezinta numar de elem distincte)
	int deleted_elems = 0;
	if (nr < 0)
		throw std::invalid_argument("received negative value of nr");
	if (cauta(elem))
	{
		PNod p = prim;
		while (p->e != elem)
		{
			p = p->urm;
		}
		if (p->frecv > nr)
		{
			deleted_elems = nr;
			p->frecv -= nr;
		}
		else
		{
			deleted_elems = p->frecv;
			if (prim == p)
				prim = prim->urm;
			if (p->urm != nullptr)
				p->urm->ant = p->ant;
			if (p->ant != nullptr)
				p->ant->urm = p->urm;
			delete p;
		}
		return deleted_elems;
	}
	return deleted_elems;
}

bool Colectie::vida() const
{
	if (prim == nullptr)
		return true;
	return false;
}

IteratorColectie Colectie::iterator() const
{
	return IteratorColectie(*this);
}

Colectie::~Colectie()
{
	while (prim != nullptr)
	{
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}

IteratorColectie::IteratorColectie(const Colectie& col) : colectie(col)
{
	curent = col.prim;
	nr_aparitii = 0;
}

void IteratorColectie::prim()
{
	curent = colectie.prim;
	nr_aparitii = 0;
}

void IteratorColectie::urmator()
{
	nr_aparitii++;
	if (nr_aparitii == curent->frecventa())
	{
		nr_aparitii = 0;
		curent = curent->urmator();
	}
}

bool IteratorColectie::valid() const
{
	return curent != nullptr;
}

TElem IteratorColectie::element() const
{
	return curent->element();
}