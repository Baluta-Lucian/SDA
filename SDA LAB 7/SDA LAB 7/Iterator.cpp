#include "DO.h"
#include "Iterator.h"
using namespace std;
/*
* [MADE BY] BALUTA IUSTINIAN-LUCIAN
*/
Iterator::Iterator(const DO& d) : dict(d) {
	/* de adaugat */
	//O(n)
	copil = d.rad;
	curent = nullptr;
	radacina = d.rad;
	while (copil != nullptr) {
		st.push(copil);
		copil = copil->stanga();
	}
}

void Iterator::prim() {
	/* de adaugat */
	//O(n)
	while (!st.empty())
		st.pop();
	copil = radacina;
	while (copil != nullptr) {
		st.push(copil);
		copil = copil->stanga();
	}
	//fillStack(d.rad);
	if (!st.empty())
		curent = st.top();
	else
		curent = nullptr;
}

void Iterator::urmator() {
	/* de adaugat */
	//O(n)
	if (valid())
	{

		curent = st.top();
		st.pop();
		copil = curent->dreapta();
		while (copil != nullptr) {
			st.push(copil);
			copil = copil->stanga();
		}
	}

}
bool Iterator::validK(int k) {
	//Theta(1)
	if (k <= 0)
		return false;
	if (st.size() < k)
		return false;
	return true;
}

void Iterator::avanseazaKPasi(int k) {
	/*Theta(n) 
	* Subalgoritm avanseazaKPasi:
	* daca validK(k) = false atunci
	*	@arunca exceptie;
	* pentru i <- 1, k executa
	*	curent <- top(st)
	*	pop(st)
	*	copil <- dreapta(curent)
	*	cat timp copil != nullptr executa
	*		push(st, copil)
	*		copil <- stanga(copil)
	*	sf cat timp
	* sf pentru
	* sf subalgoritm
	*/
	if (!validK(k))
		throw exception();
	for (int i = 1; i <= k; i++) {
		curent = st.top();
		st.pop();
		copil = curent->dreapta();
		while (copil != nullptr) {
			st.push(copil);
			copil = copil->stanga();
		}
	}
}


bool Iterator::valid() const {
	/* de adaugat */
	//STL function -> O(1) 
	return !st.empty();
}

TElem Iterator::element() const {
	/* de adaugat */
	//Theta(1)
	TElem e = curent->element();

	return pair <TCheie, TValoare>(e.first, e.second);
}


