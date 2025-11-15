
#include "Plan.h"

#include "JaySpace.h"	


void Plan::getPosInit(Vecteur3D NewPos)
{
	PosInit = NewPos;
};

void Plan::getVectNorm(Vecteur3D NewVectNor)
{
	VectNor = NewVectNor;
};

void Plan::NouvPlan(Vecteur3D Pos, Vecteur3D Vect1, Vecteur3D Vect2)
{
	VectNor = JaySpace::ProduitVectoriel(Vect1, Vect2);
	JaySpace::normalize(VectNor);
	getPosInit(Pos);
	CalSommme();
}

void Plan::NouvPlan(Vecteur3D NewPos, Vecteur3D NewVectNor)
{
	getPosInit(NewPos); 
	getVectNorm(NewVectNor);
	CalSommme();
};
void Plan::CalSommme(void)
{
	Somme = VectNor.x * PosInit.x + VectNor.y * PosInit.y + VectNor.z * PosInit.z; 
};

void Plan::CalNor(Vecteur3D NewV1, Vecteur3D NewV2) 
{
	VectNor = JaySpace::ProduitVectoriel(NewV1, NewV2);
};
void Plan::CalNS() 
{
	VectNor = Vect1 * Vect2; CalSommme();
};
void Plan::GetPlan(Vecteur3D Pt1, Vecteur3D Pt2, Vecteur3D Pt3)
{
	NouvPlan(Pt1, JaySpace::MakeVecteur(Pt1, Pt2), JaySpace::MakeVecteur(Pt1, Pt3));
};
void Plan::GetPlan(Vecteur3D Pt1, Vecteur3D VectNorm)
{
	NouvPlan(Pt1, VectNorm);
};




Plan::Plan()
{
	VectNor.getVector(0, 1, 0);
	Vect1.getVector(1, 0, 0);
	Vect2.getVector(0, 0, 1);
	CalSommme();

	//	GetPlan(Vecteur3D(0, 0, 0), Vecteur3D(0, 1, 0));
}
Plan::Plan(Vecteur3D newPt1, Vecteur3D newVectNorm) :
	PosInit(newPt1), VectNor(newVectNorm)
{
	//	Vect1.getVector(1, 0, 0);
	//	Vect2.getVector(0, 0, 1);
	CalSommme();
	//	GetPlan(newPt1, newVectNorm);
}

Plan::~Plan()
{
}



Plan MakePlan(Vecteur3D Pt1, Vecteur3D Pt2, Vecteur3D Pt3)
{
	Plan NewPlan;
	NewPlan.GetPlan(Pt1, Pt2, Pt3);

	return(NewPlan);
}

Plan MakePlan(Vecteur3D Pt1, Vecteur3D VectNorm)
{
	Plan NewPlan;
	NewPlan.GetPlan(Pt1, VectNorm);

	return(NewPlan);
}

Plan* MakeiPlan(Vecteur3D Pt1, Vecteur3D Pt2, Vecteur3D Pt3)
{
	Plan* NewPlan;
	NewPlan = new Plan;
	NewPlan->GetPlan(Pt1, Pt2, Pt3);

	return(NewPlan);
}



Plan* MakeiPlan(Vecteur3D Pt1, Vecteur3D VectNorm)
{
	Plan* NewPlan = new Plan;
	NewPlan->GetPlan(Pt1, VectNorm);

	return(NewPlan);
}