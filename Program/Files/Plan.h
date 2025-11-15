#pragma once

#include "Vecteur.h"


class Plan
{
public:
	Vecteur3D PosInit;
	Vecteur3D VectNor;
	Vecteur3D Vect1, Vect2;
	float Somme;

	Plan();
	Plan(Vecteur3D newPt1, Vecteur3D newVectNorm);
	~Plan();

	void getPosInit(Vecteur3D NewPos);
	void getVectNorm(Vecteur3D NewVectNor);
	void NouvPlan(Vecteur3D Pos, Vecteur3D Vect1, Vecteur3D Vect2);
	void NouvPlan(Vecteur3D NewPos, Vecteur3D NewVectNor);
	void CalSommme(void);
	void CalNor(Vecteur3D NewV1, Vecteur3D NewV2);
	void CalNS();
	void GetPlan(Vecteur3D Pt1, Vecteur3D Pt2, Vecteur3D Pt3);
	void GetPlan(Vecteur3D Pt1, Vecteur3D VectNorm);
};
