#pragma once

#include "Vecteur.h"


class Droite3D
{
public:
	Vecteur3D Pt1, Pt2;
	Vecteur3D Vect;

	void CalculPt2();
	void CalculVect();	
	void InitDroite_2Pt(Vecteur3D NewPt1, Vecteur3D NewPt2);
	void InitDroite_PtVect(Vecteur3D Pt, Vecteur3D NewVect);

	void InitDroite(Vecteur3D NewVect);
	void InitDroite(Vecteur3D NewVect1, Vecteur3D NewVect2);
	void InitDroite(float x, float y, float z);

	Droite3D();
	Droite3D(Vecteur3D NewPt1, Vecteur3D NewPt2);
	~Droite3D();

	void Transcription(fstream* Fic, bool ToDisk);
	void Transcription(ifstream* FicIn);
	void Transcription(ofstream* FicOut);
};

