#include "Matrice.h"
#include <exception>

using namespace std;

Matrice::Matrice(int m, int n)
{
	if (n <= 0 || m <= 0) {
		throw exception();
	}

	this->cap = m * n;
	this->ln = 0;
	this->firstFree = 0;
	this->urm = new int[cap];
	this->e = new TValue[cap];
	for (int i = 0; i < cap; i++)
	{
		this->urm[i] = i + 1;
	}
	this->prim = nullptr;
	this->rows = m;
	this->columns = n;
}

int Matrice::nrLinii() const {
	//O(1)
	return this->rows;
}

int Matrice::nrColoane() const {
	//O(1)
	return this->columns;
}

TElem Matrice::element(int i, int j) const {
	//O(cap)
	if (i < 0 || i >= this->rows || j < 0 || j >= this->columns)
	{
		throw exception();
	}

	if (this->prim == nullptr)
	{
		return NULL_TELEMENT;
	}
	Nod* p = prim;
	while (p != nullptr)
	{
		if (p->el.first.first == i && p->el.first.second == j)
		{
			return p->el.second;
		}
		p = p->urm;
	}
	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	//O(ln)
	if (i < 0 || i >= this->rows || j < 0 || j >= this->columns)
		throw exception();
	int to_modify_value = element(i, j);
	if (to_modify_value != NULL_TELEMENT) // daca gasim elem in lista, il modificam
	{
		Nod* p = prim;
		int poz = 0;
		for(int k = 0; k < this->cap; ++k)
		{
			if (this->e[k].first.first == i && this->e[k].first.second == j)
			{
				poz = k;
				break;
			}
		}
		while (p != nullptr)
		{
			if (p->el.first.first == i && p->el.first.second == j)
			{
				if (e != 0)
				{
					p->el.second = e;
					this->deallocate(poz);
					this->adauga(p->el);
					return to_modify_value;
				}
				else
				{
					this->deallocate(poz);
					Nod* temp = prim;
					while (temp->urm != p) {
						temp = temp->urm;
					}
					temp->urm = p->urm;
					delete p;
					return to_modify_value;
				}
			}
			p = p->urm;
		}
	}
	else // il adaugam
	{
		this->ln++;
		if (this->prim == nullptr) { // adaugam elementul pe prima pozitie
			this->prim = new Nod;
			this->prim->el.first.first = i;
			this->prim->el.first.second = j;
			this->prim->el.second = e;
			adauga(this->prim->el);
			return to_modify_value;
		}
		else
		{
			Nod* p = prim;
			Nod* pp = prim;
			while (p != nullptr)
			{
				if (p->el.first.first > i || (p->el.first.first == i && p->el.first.second > j))
				{
					if (prim == p) //adaugam pe prima pozitie din cauza relatiei
					{
						Nod* temp = new Nod;
						temp->el.first.first = i;
						temp->el.first.second = j;
						temp->el.second = e;
						adauga(temp->el);
						temp->urm = prim;
						prim = temp;
					}
					else
					{//adaugam intre doua elem ale listei
						Nod* temp = new Nod;
						temp->el.first.first = i;
						temp->el.first.second = j;
						temp->el.second = e;
						adauga(temp->el);
						Nod* temp1 = prim;
						while (temp1->urm != p) {
							temp1 = temp1->urm;
						}
						temp1->urm = temp;
						temp->urm = p;
					}
					return to_modify_value;
				}
				pp = p;
				p = p->urm;
			}
			if (p == nullptr)//adaugam la final
			{
				Nod* temp = new Nod;
				temp->el.first.first = i;
				temp->el.first.second = j;
				temp->el.second = e;
				adauga(temp->el);
				pp->urm = temp;
				return to_modify_value;
			}
		}
	}
}

TElem Matrice::sumaDiagonalaPrincipala()
{
	//O(ln)
	//Subalgoritm sumaDiagonalaPrincipala
	/*
	* sum <- 0
	* p <- prim
	* cat timp p != nullptr executa
	* daca [p].el.first.first = [p].el.first.second
	* atunci
	*	sum <- sum + [p].el.second
	* sf daca
	* p <- [p].urm
	* sf cat timp
	* @return sum
	* sf subalgoritm
	*/
	TElem sum = 0;
	Nod* p = prim;
	while (p != nullptr)
	{
		if (p->el.first.first == p->el.first.second)
		{
			sum += p->el.second;
		}
		p = p->urm;
	}
	return sum;
}

int Matrice::allocate()
{
	int i = this->firstFree;
	this->firstFree = this->urm[firstFree];
	return i;
}

void Matrice::deallocate(int i)
{
	this->urm[i] = this->firstFree;
	this->firstFree = i;
}

int Matrice::creeazaNod(TValue e)
{
	int i = allocate();
	if (i != -1)
	{
		this->e[i] = e;
		urm[i] = 0;
	}
	return i;
}

void Matrice::adauga(TValue e)
{
	int i = creeazaNod(e);
	if (i != -1)
	{
		urm[i] = this->firstFree;
		this->firstFree = i;
	}
}
