

#include "Vecteur.h"	
#include "Droite.h"

Droite3D::Droite3D()
{
}

Droite3D::Droite3D(Vecteur3D NewPt1, Vecteur3D NewPt2) : Pt1(NewPt1), Pt2(NewPt2)
{
	InitDroite_2Pt(NewPt1, NewPt2);
}

Droite3D::~Droite3D()
{
}

void Droite3D::CalculPt2()
{
	Pt2.getVector(Pt1.x + Vect.x, Pt1.y + Vect.y, Pt1.z + Vect.z); 
};

void Droite3D::CalculVect()
{
	Vect = Pt2 - Pt1;
};

void Droite3D::InitDroite_2Pt(Vecteur3D NewPt1, Vecteur3D NewPt2)
{
	Pt1 = NewPt1;
	Pt2 = NewPt2;
	CalculVect();
};

void Droite3D::InitDroite_PtVect(Vecteur3D Pt, Vecteur3D NewVect)
{
	Pt1 = Pt; Vect = NewVect; CalculPt2();
};

void Droite3D::InitDroite(Vecteur3D NewVect)
{
	Pt1.getVector(0, 0, 0);
	Pt2.getVector(NewVect.x, NewVect.y, NewVect.z);
	Vect = NewVect;
};

void Droite3D::InitDroite(Vecteur3D NewVect1, Vecteur3D NewVect2)
{
	Pt1.getVector(NewVect1);
	Pt2.getVector(NewVect2);
	CalculVect();
};

void Droite3D::InitDroite(float x, float y, float z)
{
	Pt1.getVector(0, 0, 0);
	Pt2.getVector(x, y, z); 
	Vect.getVector(x, y, z);
};


void Droite3D::Transcription(fstream* Fic, bool ToDisk)
{
	Pt1.Transcription(Fic, ToDisk);
	Pt2.Transcription(Fic, ToDisk);
	Vect.Transcription(Fic, ToDisk);
};
void Droite3D::Transcription(ifstream* FicIn)
{
	Pt1.Transcription(FicIn);
	Pt2.Transcription(FicIn);
	Vect.Transcription(FicIn);
};
void Droite3D::Transcription(ofstream* FicOut)
{
	Pt1.Transcription(FicOut);
	Pt2.Transcription(FicOut);
	Vect.Transcription(FicOut);
};
