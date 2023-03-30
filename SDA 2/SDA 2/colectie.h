#pragma once

typedef int TElem;

class IteratorColecte;

class Nod;

typedef Nod *PNod;

class Nod

	{
	public:
		friend class Colectie;

		Nod(TElem e, int frecv, PNod urm, PNod ant);

		TElem element();

		int frecventa() const;

		PNod urmator();

	private:
		TElem e;

		int frecv;

		PNod urm;

		PNod ant;
	};

class Colectie {

private:
	
	PNod prim;

public:

	friend class IteratorColectie;

	Colectie();

	int dim() const;

	bool cauta(TElem elem) const;

	bool vida() const;

	int nrAparitii(TElem elem) const;

	void adauga(TElem elem);

	bool sterge(TElem elem);

	int eliminaAparitii(int nr, TElem elem);

	IteratorColectie iterator() const;

	~Colectie();

};


class IteratorColectie {

private:

	IteratorColectie(const Colectie& col);

	const Colectie& colectie;

	PNod curent;
	
	int nr_aparitii;

public:

	friend class Colectie;

	void prim();

	/*Colecție*/

		// elimină nr apariții ale elementului elem. În cazul în care elementul apare mai puțin de nr ori, toate aparițiile sale vor fi eliminate.
		// returnează numărul de apariții eliminate ale elementului.
		// aruncă excepție în cazul în care este nr este negativ.

	//int eliminaAparitii(int nr, TElem elem) const;

	void urmator();

	bool valid() const;

	TElem element() const;
};