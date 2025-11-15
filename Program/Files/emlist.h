
//	emlist.h	//	Jeremie Beliveau-Lefebvre 2017


#ifndef __emlist
#define __emlist

#include <iostream>
using namespace std;
#include <fstream>

#include <assert.h>

template <typename TYPE>
class emlist {
public:
	class iterator;
private:
	struct cellule {
		TYPE CONTENU;
		cellule *nx, *prev;
		cellule(const TYPE& C = TYPE(), cellule *N = nullptr, cellule *P = nullptr) :CONTENU(C), nx(N), prev(P) { if (nx != nullptr)nx->prev = this; }
	};
	cellule *AVANT_DEBUT;
	uint64_t nbr;
	string stringTypeName;
	int typeEM;
	iterator iLast;
public:
	iterator iEdit, iSelect, iNouv, iAff, iTemp, iptr;
	emlist();
	emlist(const emlist& source);
	emlist(string newStringTypeName, int newTypeEM);
	~emlist();
	emlist& operator=(const emlist& source);
	iterator before_begin() { return iterator(AVANT_DEBUT); }
	iterator begin() { return iterator(AVANT_DEBUT->nx); }
	iterator end() { return iterator(); }
	iterator last() { return iterator(iLast); }
	bool empty()const {/*	return AVANT_DEBUT->nx == nullptr;*/return nbr == 0 || AVANT_DEBUT->nx == nullptr || iNouv.PTR == AVANT_DEBUT; }
	bool notempty()const {/*	return AVANT_DEBUT->nx != nullptr;*/return nbr != 0 && AVANT_DEBUT->nx != nullptr && iNouv.PTR != AVANT_DEBUT; }
	void clear();
	void swap(emlist&);
	void resize(size_t, const TYPE& = TYPE());
	uint64_t size()const { return(nbr); };
	//acces insertion elimination
	TYPE& front();
	iterator push_front(const TYPE&);
	iterator push_back(const TYPE&);
	void pop_front();
private:
	iterator addone(iterator, const TYPE& = TYPE());
	iterator addone(iterator, size_t, const TYPE& = TYPE());
	iterator addone(const TYPE& = TYPE());
	iterator addone(size_t, const TYPE& = TYPE());
	iterator addone(string newName, string parentNodeName);
public:
	iterator askone();
	iterator askone(const TYPE&);
	iterator askone(const iterator);

	void allEvenOnNew() { iAff = iTemp = iptr = iSelect = iEdit = iNouv; };
	iterator focuson(iterator i) { return iEdit = iSelect = i; };

	iterator StartOver() { return focuson(iNouv = before_begin()); };
	iterator Flush() { for (; iNouv != iLast; erase_after(iNouv)) {} return iNouv; };

	iterator insert_after(iterator, const TYPE&);
	iterator erase_after(iterator);
	iterator erase_last();
	iterator erase_iNouv();
	iterator erase(iterator);

	//algorithmes
	void splice_after(iterator, emlist&);
	void reverse();
	void unique();
	//code jetable
	void afficher(string Msg)const;

	void liberateptr() { iAff = iTemp = iptr = end(); focuson(iNouv); };
	bool doesNameExist_(string NameToCheck);
	iterator iterator_int_name_if_exist(int intNameToCheck);
private:
	bool doesSelectedExist_() { return(iSelect != end()); };
	bool doesEditedExist_() { return(iEdit != end()); };
	bool doesCreationExist_() { return(iNouv != end()); };

	int SetType(int newType) { if (iLast != before_begin()) { iLast->SetType(newType); } };
public:
	void Transcription(fstream *Fic, bool ToDisk, iterator iGen = iterator());
	void Transcription(ifstream *FicIn, iterator iGen = iterator());
	void Transcription(ofstream *FicOut);

	void TranscriptionObjectInfoOnly(fstream *Fic, bool ToDisk, iterator iGen = iterator());
	void TranscriptionObjectInfoOnly(ifstream *FicIn, iterator iGen = iterator());
	void TranscriptionObjectInfoOnly(ofstream *FicOut);

	bool Notnullptr();

	iterator operator[](int index);

	//// Non-const version for read/write access
	//T& operator[](int index) {
	//	// Add bounds checking for safety (e.g., if (index < 0 || index >= Size) throw std::out_of_range("Index out of bounds");)
	//	return data[index];
	//}

	//// Const version for read-only access
	//const T& operator[](int index) const {
	//	// Add bounds checking for safety
	//	return data[index];
	//}
};

//////////////////////////////////////////////////////////////////
//class iterator
template <typename TYPE>
class emlist<TYPE>::iterator {
private:
	cellule* PTR;
public:
	friend class emlist<TYPE>;
	iterator(cellule* P = nullptr) :PTR(P) {}
	TYPE& operator*() { assert(PTR != nullptr); return PTR->CONTENU; }
	TYPE* operator->() { assert(PTR != nullptr); return &(PTR->CONTENU); }
	TYPE* operator&() { assert(PTR != nullptr); return &(PTR->CONTENU); }
	iterator& operator=(cellule *P) { PTR = P; return(*this); }
	iterator& operator++() {
		PTR = PTR->nx;
		return *this;
	}
	iterator operator++(int) { //i++
		iterator copie(*this);
		PTR = PTR->nx;
		return copie;
	}
	iterator& operator--() {
		PTR = PTR->prev;
		return *this;
	}
	iterator operator--(int) { //i--
		iterator copie(*this);
		PTR = PTR->prev;
		return copie;
	}
	bool operator==(const iterator& droite)const {
		return PTR == droite.PTR;
	}
	bool operator!=(const iterator& droite)const {
		return PTR != droite.PTR;
	}
	iterator New(TYPE NT = TYPE()) { PTR = new cellule; PTR->CONTENU = NT; return(*this); };
	iterator Delete() { if (PTR != nullptr) { delete PTR; PTR = nullptr; }  return(*this); };

	void Transcription(fstream *Fic, bool ToDisk);
	void Transcription(ifstream *FicIn);
	void Transcription(ofstream *FicOut);

	void afficher() { assert(PTR != nullptr); cout << PTR->CONTENU << endl; };
};


#include "emlist.h"


//////////////////////////////////////////////////////////////////
// constructeur, destructeur, copieur, affectateur
template <typename TYPE>
emlist<TYPE>::emlist() :
	AVANT_DEBUT(new cellule)
{
	nbr = 0;
	iNouv = iLast = before_begin();
	liberateptr();
}
template <typename TYPE>
emlist<TYPE>::~emlist() {
	clear();
	delete AVANT_DEBUT;
	AVANT_DEBUT = nullptr;
	--nbr;
}
template <typename TYPE>
emlist<TYPE>::emlist(const emlist& source) :emlist() {
	iterator i = before_begin();
	for (cellule* p = source.AVANT_DEBUT->nx; p != nullptr; p = p->nx) {
		i = addone(i, p->CONTENU);
	}
}
template <typename TYPE>
emlist<TYPE>::emlist(string newStringTypeName, int newTypeEM) :emlist() {
	stringTypeName = newStringTypeName;
	typeEM = newTypeEM;
}
template <typename TYPE>
emlist<TYPE>& emlist<TYPE>::operator=(const
	emlist& source) {
	if (this != &source) {
		emlist copie(source);
		swap(copie);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////
// acces, insertion, elimination
template <typename TYPE>
TYPE& emlist<TYPE>::front() {
	return *begin();
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::push_front(const TYPE& VAL) {
	return addone(before_begin(), VAL);
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::push_back(const TYPE& VAL) {
	return addone(iLast, VAL);
}


template <typename TYPE>
void emlist<TYPE>::pop_front() {
	erase_after(before_begin());
}

//////////////////////////////////////////////////////////////////
// fonctions utilitaires

template <typename TYPE>
bool emlist<TYPE>::doesNameExist_(string NameToCheck)
{
	for (iptr = begin(); iptr != end(); ++iptr)
	{
		if (NameToCheck == iptr->Name)
			return(true);
	}
	return(false);
};

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::iterator_int_name_if_exist(int intNameToCheck)
{
	for (iptr = begin(); iptr != end(); ++iptr)
	{
		if (intNameToCheck == iptr->intName)
			return(iptr);
	}
	return(end());
};

template <typename TYPE>
void emlist<TYPE>::clear() {
	resize(0);
}
template <typename TYPE>
void emlist<TYPE>::swap(emlist& deux) {
	std::swap(AVANT_DEBUT, deux.AVANT_DEBUT);
}
//////////////////////////////////////////////////////////////////
// algorithmes
template <typename TYPE>
void emlist<TYPE>::reverse() {
	cellule* SWAP, * p = AVANT_DEBUT->nx;

	for (AVANT_DEBUT->nx = nullptr; p != nullptr;) {
		SWAP = p->nx;
		p->nx = AVANT_DEBUT->nx;
		AVANT_DEBUT->nx = p;
		p = SWAP;
	}

	AVANT_DEBUT->prev = nullptr;
	p = AVANT_DEBUT;
	SWAP = AVANT_DEBUT->nx;
	for (SWAP = AVANT_DEBUT->nx; SWAP != nullptr;) {
		SWAP->prev = p;
		p = SWAP;
		SWAP = SWAP->nx;
	}
}
//////////////////////////////////////////////////////////////////
// code jetable
template <typename TYPE>
void emlist<TYPE>::afficher(string Msg)const {
	using namespace std;
	cout << "/////////////////////////////////////" << endl;
	cout << "emlist a: " << this << endl;
	cout << "\t" << Msg << endl;
	cellule* p = AVANT_DEBUT->nx;
	int i;
	cout << ":iEdit:\t" << ":iSel:\t" << ":iNouv:\t" << ":iAff:\t" << ":iTemp:\t" << ":iptr:\t" << ":iLast:\t" << endl;
	if (iEdit == AVANT_DEBUT)cout << "iEdit->\t"; else cout << "\t";
	if (iSelect == AVANT_DEBUT)cout << "iSel->\t"; else cout << "\t";
	if (iNouv == AVANT_DEBUT)cout << "iNouv->\t"; else cout << "\t";
	if (iAff == AVANT_DEBUT)cout << "iAff->\t"; else cout << "\t";
	if (iTemp == AVANT_DEBUT)cout << "iTemp->\t"; else cout << "\t";
	if (iptr == AVANT_DEBUT)cout << "iptr->\t"; else cout << "\t";
	if (iLast == AVANT_DEBUT)cout << "iLast->\t"; else cout << "\t";
	cout << "\t" << "Av_Deb" << endl;

	for (i = 0; p != nullptr; ++i) {

		if (iEdit == p)cout << "iEdit->\t"; else cout << "\t";
		if (iSelect == p)cout << "iSel->\t"; else cout << "\t";
		if (iNouv == p)cout << "iNouv->\t"; else cout << "\t";
		if (iAff == p)cout << "iAff->\t"; else cout << "\t";
		if (iTemp == p)cout << "iTemp->\t"; else cout << "\t";
		if (iptr == p)cout << "iptr->\t"; else cout << "\t";
		if (iLast == p)cout << "iLast->\t"; else cout << "\t";

		if (p->prev == nullptr) cout << " end<-\t"; else if (p->prev == AVANT_DEBUT)cout << "AvDeb<-\t"; else cout << p->prev->CONTENU.d << "  <-\t";

		cout << " " << i << ":" << p->CONTENU.d << " ";

		if (p->nx == nullptr) cout << " ->end\t"; else cout << " ->" << p->nx->CONTENU.d << "\t";
		cout << endl;
		p = p->nx;
	}
	if (iEdit == nullptr)cout << "iEdit->\t"; else cout << "\t";
	if (iSelect == nullptr)cout << "iSel->\t"; else cout << "\t";
	if (iNouv == nullptr)cout << "iNouv->\t"; else cout << "\t";
	if (iAff == nullptr)cout << "iAff->\t"; else cout << "\t";
	if (iTemp == nullptr)cout << "iTemp->\t"; else cout << "\t";
	if (iptr == nullptr)cout << "iptr->\t"; else cout << "\t";
	if (iLast == nullptr)cout << "iLast->\t"; else cout << "\t";
	cout << "\t" << "end()" << endl << endl;

	if (i == 0)cout << "[liste vide]";
	else if (i == 1)cout << "[1 element]";
	else cout << "[" << i << " elements]";

	cout << endl << "[nbr : " << nbr << " elements]";
	cout << endl << "/////////////////////////////////////" << endl;
	cout << endl;
}
//////////////////////////////////////////////////////////////////


// fonctions generatrices de base
// addone et erase_after


template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::askone() {
	iterator next = iNouv;	if (next != end() && ++next != end()) { *next = TYPE(); focuson(next); return ++iNouv; }
	return (iNouv = addone(iNouv, TYPE()));
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::askone(const iterator it) {
	assert(it != end());
	iterator next = iNouv;	if (next != end() && ++next != end()) { *next = TYPE(it.PTR->CONTENU); focuson(next); return ++iNouv; }
	return (iNouv = addone(iNouv, it.PTR->CONTENU));
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::askone(const TYPE& VAL) {
	iterator next = iNouv;	if (next != end() && ++next != end()) { *next = TYPE(VAL); focuson(next); return ++iNouv; }
	return (iNouv = addone(VAL));
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::addone(iterator i, size_t N, const TYPE& VAL) {
	for (int j = 0; j < N; ++j)i = addone(i, VAL);
	return focuson(i);
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::addone(size_t N, const TYPE& VAL) {
	iterator i = addone(VAL);
	for (int j = 0; j < N; ++j) i = addone(VAL);
	return focuson(i);
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::addone(string newName, string parentNodeName) {
	addone();
	iLast->NumbName(newName, nbr);
	iLast->ParentNode = parentNodeName;
};


template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::addone(const TYPE& VAL) {
	iLast.PTR->nx = new cellule(VAL, iLast.PTR->nx, iLast.PTR);
	nbr++;
	iSelect = iEdit = (++iLast);
	return focuson(iLast);
}
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::addone(iterator i, const TYPE& VAL) {
	if (i == iLast || i == end()) return(addone(VAL));

	i.PTR->nx = new cellule(VAL, i.PTR->nx, i.PTR);
	nbr++;
	iEdit = (++i);
	return focuson(i);
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::erase_iNouv() {
	if (iNouv != before_begin())
	{
		iterator i = iNouv;
		--iNouv;
		erase(i);
	}

	focuson(iNouv);
	return iNouv;
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::erase_last() {
	assert(iLast != before_begin());

	if (iEdit == iLast) iEdit = end();
	if (iSelect == iLast) iSelect = end();
	if (iNouv == iLast) --iNouv;
	if (iAff == iLast) iAff = end();
	if (iTemp == iLast) iTemp = end();
	if (iptr == iLast) iptr = end();

	--iLast;
	delete iLast.PTR->nx;
	iLast.PTR->nx = nullptr;
	--nbr;
	focuson(iNouv);
	return(iLast);
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::erase(iterator i) {
	assert(i != end() && i != before_begin());
	--i;
	return(erase_after(i));
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::erase_after(iterator i) {
	assert(i != end());
	assert(i.PTR->nx != nullptr);

	iterator e = i;
	e++;

	if (e == iNouv) { --iNouv; focuson(iNouv); }
	if (e == iLast) return(erase_last());

	i.PTR->nx = e.PTR->nx;
	e.PTR->nx = nullptr;
	delete e.PTR;
	if (i.PTR->nx != nullptr) { i.PTR->nx->prev = i.PTR; }
	--nbr;
	return(++i);
}
//
//template <typename TYPE>
//typename emlist<TYPE>::iterator emlist<TYPE>::erase_after(iterator i) {
//	if (i.PTR->nx != NULL) {
//		iterator e = i;
//		e++;
//		i.PTR->nx = e.PTR->nx;
//		e.PTR->nx = NULL;
//		delete e.PTR;
//		return(++i);
//	}
//	else return(end());
//}
//////////////////////////////////////////////////////////////////
// fonctions diverses
template <typename TYPE>
void emlist<TYPE>::unique() {
	iterator i, n;
	i = n = begin();
	if (i != end())
		for (n++; n.PTR != nullptr; i++) {
			for (; i.PTR->CONTENU == n.PTR->CONTENU; ) {
				n = erase_after(i);
				if (n.PTR == nullptr)	break;
			}
			if (n.PTR != nullptr)	n++;
		}
}

template <typename TYPE>
void emlist<TYPE>::splice_after(typename emlist<TYPE>::iterator i, emlist<TYPE>& L2) {
	if (L2.begin() != nullptr)
	{
		iterator p = L2.before_begin(), n;
		for (; p.PTR->nx != nullptr; ++p) {}	//	Va � la fin de la liste 2.

		(n = i)++;	//	Clang-format

		i.PTR->nx = L2.AVANT_DEBUT->nx;
		p.PTR->nx = n.i;
		L2.AVANT_DEBUT->nx = nullptr;
		if (i == iLast) iLast = L2.iNouv;
		L2.iNouv.PTR = L2.AVANT_DEBUT;
		nbr = nbr + L2.nbr;
		L2.nbr = 0;
	}
}
template <typename TYPE>
void emlist<TYPE>::resize(size_t NOUV, const TYPE& VAL) {
	iterator p = before_begin(), q;
	size_t n = 0;

	//	Va � travers la liste existante
	for (; p.PTR->nx != nullptr; ++n) {
		if (n >= NOUV) {	//	Si plus que le nbr demand�	//	Doit effacer le prochain et le i p reste � l'item point� (on va effacer le reste de la liste � revers).
			++(q = p);
			if (q == iNouv)
				iNouv = p;
			erase_after(p);
		}
		else ++p;				//	Sinon, passe au nx.
	}
	//	Tant qu'on n'a pas atteint la fin du nbr demand�, on ajoute un item apr�s le dernier item point�. 
	for (; n < NOUV; ++n)addone(p, VAL);

	iAff = iTemp = iptr = end();
	focuson(iNouv);
}


template <typename TYPE>
void emlist<TYPE>::iterator::Transcription(fstream* Fic, bool ToDisk) {
	PTR->CONTENU.Transcription(Fic, ToDisk);
}

template <typename TYPE>
void emlist<TYPE>::iterator::Transcription(ifstream* FicIn) {
	PTR->CONTENU.Transcription(FicIn);
}

template <typename TYPE>
void emlist<TYPE>::iterator::Transcription(ofstream* FicOut) {
	PTR->CONTENU.Transcription(FicOut);
}

template <typename TYPE>
void emlist<TYPE>::TranscriptionObjectInfoOnly(fstream* Fic, bool ToDisk, iterator iGen) {
	if (ToDisk)
	{
		bool Indice;
		for (iptr = begin(); iptr != end(); ++iptr)
		{
			Indice = true;
			Fic->write((char*)&Indice, sizeof(Indice));

			iptr->TranscriptionObjectInfoOnly(Fic, ToDisk);
		}
		Indice = false;
		Fic->write((char*)&Indice, sizeof(Indice));

	}
	else
	{
		bool Indice;
		for (Fic->read((char*)&Indice, sizeof(Indice)); Indice; Fic->read((char*)&Indice, sizeof(Indice)))
		{
			iGen = iptr = addone();
			iptr->TranscriptionObjectInfoOnly(Fic, ToDisk);
		}
	}
}
template <typename TYPE>
void emlist<TYPE>::TranscriptionObjectInfoOnly(ifstream* FicIn, iterator iGen) {
	bool Indice;
	for (FicIn->read((char*)&Indice, sizeof(Indice)); Indice; FicIn->read((char*)&Indice, sizeof(Indice)))
	{
		iGen = iptr = addone();
		iptr->TranscriptionObjectInfoOnly(FicIn);
	}
	iNouv = iptr;
	focuson(begin());
}

template <typename TYPE>
void emlist<TYPE>::TranscriptionObjectInfoOnly(ofstream* FicOut) {
	bool Indice;
	for (iptr = begin(); iptr != end(); ++iptr)
	{
		Indice = true;
		FicOut->write((char*)&Indice, sizeof(Indice));

		iptr->TranscriptionObjectInfoOnly(FicOut);
	}
	Indice = false;
	FicOut->write((char*)&Indice, sizeof(Indice));
}

template <typename TYPE>
bool emlist<TYPE>::Notnullptr(void) {
	return iptr != nullptr;
}


template <typename TYPE>
void emlist<TYPE>::Transcription(fstream* Fic, bool ToDisk, iterator iGen) {
	if (ToDisk)
	{
		bool Indice;
		for (iptr = begin(); iptr != end(); ++iptr)
		{
			Indice = true;
			Fic->write((char*)&Indice, sizeof(Indice));

			iptr->Transcription(Fic, ToDisk);
		}
		Indice = false;
		Fic->write((char*)&Indice, sizeof(Indice));

	}
	else
	{
		bool Indice;
		for (Fic->read((char*)&Indice, sizeof(Indice)); Indice; Fic->read((char*)&Indice, sizeof(Indice)))
		{
			iGen = iptr = askone();
			iptr->Transcription(Fic, ToDisk);
		}
	}
}

template <typename TYPE>
void emlist<TYPE>::Transcription(ifstream* FicIn, iterator iGen) {
	bool Indice;
	for (FicIn->read((char*)&Indice, sizeof(Indice)); Indice; FicIn->read((char*)&Indice, sizeof(Indice)))
	{
		iGen = iptr = askone();
		iptr->Transcription(FicIn);
	}
	iNouv = iptr;
	focuson(begin());
}
template <typename TYPE>
void emlist<TYPE>::Transcription(ofstream* FicOut) {
	bool Indice;
	for (iptr = begin(); iptr != end(); ++iptr)
	{
		Indice = true;
		FicOut->write((char*)&Indice, sizeof(Indice));

		iptr->Transcription(FicOut);
	}
	Indice = false;
	FicOut->write((char*)&Indice, sizeof(Indice));
}

//////////////////////////////////////////////////////////////////

// fonctions generatrices de base
// insert_after et erase_after
template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::insert_after(iterator i, const TYPE& VAL) {
	i.PTR->nx = new cellule(VAL, i.PTR->nx);
	return(++i);
}

template <typename TYPE>
typename emlist<TYPE>::iterator emlist<TYPE>::operator[](int index)
{
	// Add bounds checking for safety (e.g., if (index < 0 || index >= Size) throw std::out_of_range("Index out of bounds");)
	if (index < 0 || index >= nbr) {
		throw std::out_of_range("Index out of bounds");
	}
	iterator it = begin();
	for (int i = 0; i < index && it != end(); ++i, ++it);
	return it;
}


//
////////////////////////////////////////////////////////////////////
//// fonctions diverses
//template <typename TYPE>
//void emlist<TYPE>::unique() {
//	iterator i, n;
//	i = n = before_begin();
//	for (n++; n.PTR != NULL; i++) {
//		for (; i.PTR->CONTENU == n.PTR->CONTENU; ) {
//			n = erase_after(i);
//			if (n.PTR == NULL)	break;
//		}
//		if (n.PTR != NULL)	n++;
//	}
//}
//
//template <typename TYPE>
//void emlist<TYPE>::splice_after(typename emlist<TYPE>::iterator i, emlist<TYPE>& L2) {
//	if (L2.begin() != NULL)
//	{
//		iterator p = L2.before_begin(), n;
//		for (; p.PTR->nx != NULL; ++p) {}	//	Va � la fin de la liste 2.
//
//		(n = i)++;	//	Clang-format
//
//		i.PTR->nx = L2.AVANT_DEBUT->nx;
//		p.PTR->nx = n.PTR;
//		L2.AVANT_DEBUT->nx = NULL;
//	}
//}
//
//template <typename TYPE>
//void emlist<TYPE>::resize(size_t NOUV, const TYPE& VAL) {
//	iterator p = before_begin();
//	size_t n = 0;
//
//	//	Va � travers la liste existante
//	for (; p.PTR->nx != NULL; ++n) {
//		if (n >= NOUV) erase_after(p);	//	Si plus que le nbr demand�	//	Doit effacer le prochain et le ptr p reste � l'item point� (on va effacer le reste de la liste � revers).
//		else ++p;				//	Sinon, passe au nx.
//	}
//	//	Tant qu'on n'a pas atteint la fin du nbr demand�, on ajoute un item apr�s le dernier item point�. 
//	for (; n < NOUV; ++n)insert_after(p, VAL);
//}

#endif /* defined(__emlist) */