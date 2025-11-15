
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <fstream>
using namespace std;


#include "JaySpace.h"



//#include "Vecteur.h"
//#include "JaySpaceVecteur.h"
//#include "Coordonnee.h"
//#include "Droite.h"
//#include "Plan.h"


namespace JaySpace {
	float g_Scale = 1.0f;
	float g_diffScale = 0.0f;
	float g_MouseWheelScale = 0.05f;

	int button;
	int action;
	int mods;

	bool button_left;
	bool button_right;
	bool button_middle;

	bool button_left_just_clicked;
	bool button_right_just_clicked;
	bool button_middle_just_clicked;

	bool button_left_just_released;
	bool button_right_just_released;
	bool button_middle_just_released;

	const char** dragNdrop_paths;
	int dragNdrop_count = 0;
	//ProjectTeethJay projet;
}

float& JaySpace::_regulate(float& Num)
{
	if (Num < Max_Min && Num > Min_Min)	Num = 0.0;

	return Num;

};

void JaySpace::_cout(glm::vec3 vect2show)
{
	Vecteur3D(vect2show)._cout();
}

void JaySpace::_cout(glm::mat4 mat4)
{
	cout << "0.x : " << mat4[0][0] << " \t 1.x : " << mat4[0][1] << " \t 2.x : " << mat4[0][2] << " \t 3.x : " << mat4[0][3] << endl;
	cout << "0.y : " << mat4[0][0] << " \t 1.y : " << mat4[0][1] << " \t 2.y : " << mat4[0][2] << " \t 3.y : " << mat4[0][3] << endl;
	cout << "0.z : " << mat4[0][0] << " \t 1.z : " << mat4[0][1] << " \t 2.z : " << mat4[0][2] << " \t 3.z : " << mat4[0][3] << endl;
	cout << "0.w : " << mat4[0][0] << " \t 1.w : " << mat4[0][1] << " \t 2.w : " << mat4[0][2] << " \t 3.w : " << mat4[0][3] << endl;
}

Vecteur3D JaySpace::_regulate(Vecteur3D& Coord)
{
	_regulate(Coord.x);
	_regulate(Coord.y);
	_regulate(Coord.z);

	return Coord;
};
Vecteur2D JaySpace::_regulate(Vecteur2D& Coord)
{
	_regulate(Coord.x);
	_regulate(Coord.y);

	return Coord;
};

Coord2D JaySpace::_regulate(Coord2D& Coord)
{
	_regulate(Coord.x);
	_regulate(Coord.y);

	return Coord;
};





bool JaySpace::_isnan(Vecteur3D PtToEvaluate)
{
	return(std::isnan(PtToEvaluate.x) || std::isnan(PtToEvaluate.y) || std::isnan(PtToEvaluate.z));
}

float JaySpace::Somme(Vecteur3D Pt)
{
	return(Pt.x + Pt.y + Pt.z);
}

float JaySpace::FindY(float X, Coord2D Pt1, Coord2D Pt2)
{
	float A1 = (Pt2.y - Pt1.y) / (Pt2.x - Pt1.x),
		C1 = Pt1.y - Pt1.x * A1;

	return(X * A1 + C1);
}

float JaySpace::FindX(float Y, Coord2D Pt1, Coord2D Pt2)
{
	float B1 = (Pt2.x - Pt1.x) / (Pt2.y - Pt1.y),
		D1 = Pt1.x - Pt1.y * B1;
	return(Y * B1 + D1);
}

bool JaySpace::CroisementDroites(Coord2D& PtCroisement, Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2)
{
	float A1 = (Pt2Dr1.y - Pt1Dr1.y) / (Pt2Dr1.x - Pt1Dr1.x),
		A2 = (Pt2Dr2.y - Pt1Dr2.y) / (Pt2Dr2.x - Pt1Dr2.x),
		C1 = Pt1Dr1.y - Pt2Dr1.x * A1,
		C2 = Pt1Dr2.y - Pt2Dr2.x * A2;
	if (A1 == A2)	//	Sinon, les droites sont parallele et ne se toucheront jamais
	{
		return(false);
	}
	else
	{
		PtCroisement.x = (C2 - C1) / (A1 - A2);
		PtCroisement.y = PtCroisement.x * A1 + C1;
		return(true);
	}
}

bool JaySpace::CroisementSegments(Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2)
{
	Coord2D PtCroisement;

	float A1 = (Pt2Dr1.y - Pt1Dr1.y) / (Pt2Dr1.x - Pt1Dr1.x),
		A2 = (Pt2Dr2.y - Pt1Dr2.y) / (Pt2Dr2.x - Pt1Dr2.x),
		C1 = Pt1Dr1.y - Pt2Dr1.x * A1,
		C2 = Pt1Dr2.y - Pt2Dr2.x * A2;

	if (A1 == A2	//	Sinon, les segments sont parallele et ne se toucheront jamais
		|| Pt1Dr1 == Pt2Dr1 || Pt1Dr2 == Pt2Dr2)	//	Les segments n'existent pas
	{
		return(false);
	}
	else
	{
		PtCroisement.x = (C2 - C1) / (A1 - A2);
		PtCroisement.y = PtCroisement.x * A1 + C1;

		if (((PtCroisement.x >= Pt1Dr1.x && PtCroisement.x <= Pt2Dr1.x) ||
			(PtCroisement.x >= Pt2Dr1.x && PtCroisement.x <= Pt1Dr1.x)) &&
			((PtCroisement.x >= Pt1Dr2.x && PtCroisement.x <= Pt2Dr2.x) ||
				(PtCroisement.x >= Pt2Dr2.x && PtCroisement.x <= Pt1Dr2.x)))

		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
}

bool JaySpace::CroisementSegments(Coord2D& PtCroisement, Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2)
{
	float A1 = (Pt2Dr1.y - Pt1Dr1.y) / (Pt2Dr1.x - Pt1Dr1.x),
		A2 = (Pt2Dr2.y - Pt1Dr2.y) / (Pt2Dr2.x - Pt1Dr2.x),
		C1 = Pt1Dr1.y - Pt2Dr1.x * A1,
		C2 = Pt1Dr2.y - Pt2Dr2.x * A2;

	if (A1 == A2	//	Sinon, les segments sont parallele et ne se toucheront jamais
		|| Pt1Dr1 == Pt2Dr1 || Pt1Dr2 == Pt2Dr2)	//	Les segments n'existent pas
	{
		return(false);
	}
	else
	{
		PtCroisement.x = (C2 - C1) / (A1 - A2);
		PtCroisement.y = PtCroisement.x * A1 + C1;

		if (((PtCroisement.x >= Pt1Dr1.x && PtCroisement.x <= Pt2Dr1.x) ||
			(PtCroisement.x >= Pt2Dr1.x && PtCroisement.x <= Pt1Dr1.x)) &&
			((PtCroisement.x >= Pt1Dr2.x && PtCroisement.x <= Pt2Dr2.x) ||
				(PtCroisement.x >= Pt2Dr2.x && PtCroisement.x <= Pt1Dr2.x)))

		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
}
bool JaySpace::Equals(Vecteur3D Pt1, Vecteur3D Pt2)
{
	if (Pt1.x == Pt2.x &&
		Pt1.y == Pt2.y &&
		Pt1.z == Pt2.z)
		return(true);
	else
		return(false);
}

bool JaySpace::IsParallele(Vecteur3D VectRot, Vecteur3D VectQ)
{
	if (Dot(VectRot, VectQ) == 0)
	{
		return false;
	}
	else
		return(true);
}

Vecteur3D JaySpace::Adds_Point(Vecteur3D Pt1, Vecteur3D Pt2)
{
	Vecteur3D NewPt;
	NewPt.getVector(Pt2.x + Pt1.x, Pt2.y + Pt1.y, Pt2.z + Pt1.z);
	return (NewPt);
}

Vecteur3D JaySpace::Souss_Point(Vecteur3D Pt, Vecteur3D Pt2)
{
	Vecteur3D NewPt;
	NewPt.getVector(Pt.x - Pt2.x, Pt.y - Pt2.y, Pt.z - Pt2.z);
	return (NewPt);
}


Vecteur3D JaySpace::Multip(Vecteur3D Pt, float Multiplicator)
{
	Vecteur3D NewPt;
	NewPt.getVector(Pt.x * Multiplicator, Pt.y * Multiplicator, Pt.z * Multiplicator);
	return (NewPt);
}

Vecteur3D JaySpace::Contact_Droite_Plan(Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtPl, Vecteur3D VectPl)
{
	float Somme = VectPl.x * PtPl.x + VectPl.y * PtPl.y + VectPl.z * PtPl.z;
	float VarT = (Somme - (VectPl.x * PtDr.x + VectPl.y * PtDr.y + VectPl.z * PtDr.z))
		/ (VectPl.x * VectDr.x + VectPl.y * VectDr.y + VectPl.z * VectDr.z);

	Vecteur3D PointContact;
	PointContact.getVector(
		VectDr.x * VarT + PtDr.x,
		VectDr.y * VarT + PtDr.y,
		VectDr.z * VarT + PtDr.z);

	return (PointContact);
}

glm::vec3 JaySpace::Contact_Droite_Plan(glm::vec3 PtDr, glm::vec3 VectDr, glm::vec3 PtPl, glm::vec3 VectPl)
{
	Vecteur3D result = Contact_Droite_Plan(Vecteur3D(PtDr), Vecteur3D(VectDr), Vecteur3D(PtPl), Vecteur3D(VectPl));

	return glm::vec3(result.x, result.y, result.z);
}


Vecteur3D JaySpace::Contact_Droite_Plan(Vecteur3D Point1, Vecteur3D Pt2_VDrt, Plan PLAN)
{
	float VarT;
	Vecteur3D PointContact;
	//	Vecteur3D Point2 = Point1;
	//	Vecteur3D Pt2_VDrt2 = Pt2_VDrt;
	//	Plan PLAN2 = PLAN;
	//	Point2 = Point2;
	//	Pt2_VDrt2 = Pt2_VDrt2;
	//	PLAN2 = PLAN2;

	Pt2_VDrt = Pt2_VDrt - Point1;

	VarT = (PLAN.Somme - (PLAN.VectNor.x * Point1.x + PLAN.VectNor.y * Point1.y + PLAN.VectNor.z * Point1.z))
		/ (PLAN.VectNor.x * Pt2_VDrt.x + PLAN.VectNor.y * Pt2_VDrt.y + PLAN.VectNor.z * Pt2_VDrt.z);

	PointContact = Pt2_VDrt * VarT + Point1;

	//	cout<<PointContact.x<<"\t"<<PointContact.y<<"\t"<<PointContact.z<<endl;
	return (PointContact);
}

Vecteur3D JaySpace::Contact_Droite_Plan(Droite3D Dr1, Plan PLAN)
{
	float VarT;
	Vecteur3D Point1 = Dr1.Pt1, Pt2_VDrt = Dr1.Pt2;
	Vecteur3D PointContact;

	Pt2_VDrt = Pt2_VDrt - Point1;

	VarT = (PLAN.Somme - (PLAN.VectNor.x * Point1.x + PLAN.VectNor.y * Point1.y + PLAN.VectNor.z * Point1.z))
		/ (PLAN.VectNor.x * Pt2_VDrt.x + PLAN.VectNor.y * Pt2_VDrt.y + PLAN.VectNor.z * Pt2_VDrt.z);

	PointContact = Pt2_VDrt * VarT + Point1;

	//	cout<<PointContact.x<<"\t"<<PointContact.y<<"\t"<<PointContact.z<<endl;
	return (PointContact);
}



int JaySpace::Contact_Droite_Sphere(Vecteur3D& PtCte1, Vecteur3D& PtCte2, Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtCentreSphere, float Rayon)
{
	//	Retourne 0 si aucun point ne touchent
	//	Retourne 1 si un point touche
	//	Retourne 2 si deux points touchent

	float N, M, O, Q1, Q2, Q3;
	N = VectDr.x * VectDr.x + VectDr.y * VectDr.y + VectDr.z * VectDr.z;
	M = (2.0) * (
		(PtDr.x * VectDr.x + PtDr.y * VectDr.y + PtDr.z * VectDr.z)
		-
		(PtCentreSphere.x * VectDr.x + PtCentreSphere.y * VectDr.y + PtCentreSphere.z * VectDr.z)
		);
	Q1 = PtDr.x - PtCentreSphere.x;
	Q2 = PtDr.y - PtCentreSphere.y;
	Q3 = PtDr.z - PtCentreSphere.z;
	O = Q1 * Q1 + Q2 * Q2 + Q3 * Q3;

	float T1, T2;
	if (N <= 0.0)	//	Alors c'est que le vecteur est nullptr.
	{
		return(0);	//	Aucun point ne peuvent toucher la sphere
	}
	else
	{
		T1 = Rayon * Rayon - O + (M * M / (4.0 * N));
		N = sqrt(N);
		if (T1 < 0.0)	//	Alors la droite ne passe pas � travers la sphere ni ne la touche. Elle passe juste � c�t�.
		{
			return(0);
		}
		else
			if (T1 == 0.0)	//	Alors un seul point touche la sph�re
			{
				T1 = -M / (2.0 * N) / N;
				PtCte1 = PtCte2 = Vecteur3D(VectDr.x * T1 + PtDr.x, VectDr.y * T1 + PtDr.y, VectDr.z * T1 + PtDr.z);

				return(1);
			}
			else			//	Alors deux points touchent la sph�re
			{
				T2 = T1 = sqrt(T1);
				T2 *= (-1.0);

				T1 = (T1 - M / (2.0 * N)) / N;
				T2 = (T2 - M / (2.0 * N)) / N;

				PtCte1 = Vecteur3D(VectDr.x * T1 + PtDr.x, VectDr.y * T1 + PtDr.y, VectDr.z * T1 + PtDr.z);
				PtCte2 = Vecteur3D(VectDr.x * T2 + PtDr.x, VectDr.y * T2 + PtDr.y, VectDr.z * T2 + PtDr.z);

				return(2);
			}
	}
}

float JaySpace::Determinant(Vecteur3D Vect1, Vecteur3D Vect2, Vecteur3D Vect3)
{
	return(Vect1.x * Vect2.y * Vect3.z + Vect2.x * Vect3.y * Vect1.z + Vect3.x * Vect1.y * Vect2.z
		- (Vect1.x * Vect3.y * Vect2.z + Vect2.x * Vect1.y * Vect3.z + Vect3.x * Vect2.y * Vect1.z));
}

float JaySpace::Determinant(Matrice3D MatO)
{
	float Det = MatO.Vect1.x * MatO.Vect2.y * MatO.Vect3.z
		+ MatO.Vect2.x * MatO.Vect3.y * MatO.Vect1.z
		+ MatO.Vect3.x * MatO.Vect1.y * MatO.Vect2.z
		- (MatO.Vect1.x * MatO.Vect3.y * MatO.Vect2.z
			+ MatO.Vect2.x * MatO.Vect1.y * MatO.Vect3.z
			+ MatO.Vect3.x * MatO.Vect2.y * MatO.Vect1.z);

	return(Det);
}

Matrice3D JaySpace::MatriceTransformee(Matrice3D MatO)
{
	Matrice3D NouvMatrice;

	NouvMatrice.Vect1.x = MatO.Vect2.y * MatO.Vect3.z - MatO.Vect2.z * MatO.Vect3.y;
	NouvMatrice.Vect1.y = MatO.Vect2.z * MatO.Vect3.x - MatO.Vect2.x * MatO.Vect3.z;
	NouvMatrice.Vect1.z = MatO.Vect2.x * MatO.Vect3.y - MatO.Vect2.y * MatO.Vect3.x;
	NouvMatrice.Vect2.x = MatO.Vect1.z * MatO.Vect3.y - MatO.Vect1.y * MatO.Vect3.z;
	NouvMatrice.Vect2.y = MatO.Vect1.x * MatO.Vect3.z - MatO.Vect1.z * MatO.Vect3.x;
	NouvMatrice.Vect2.z = MatO.Vect1.y * MatO.Vect3.x - MatO.Vect1.x * MatO.Vect3.y;
	NouvMatrice.Vect3.x = MatO.Vect1.y * MatO.Vect2.z - MatO.Vect1.z * MatO.Vect2.y;
	NouvMatrice.Vect3.y = MatO.Vect1.z * MatO.Vect2.x - MatO.Vect1.x * MatO.Vect2.z;
	NouvMatrice.Vect3.z = MatO.Vect1.x * MatO.Vect2.y - MatO.Vect1.y * MatO.Vect2.x;

	return (NouvMatrice);
}

/*void VoirMatrice(Matrice3D MatO)
{
	cout<<MatO.Vect1.x<<"\t"<<MatO.Vect1.y<<"\t"<<MatO.Vect1.z<<"\t"
	<<MatO.Vect2.x<<"\t"<<MatO.Vect2.y<<"\t"<<MatO.Vect2.z<<"\t"
	<<MatO.Vect3.x<<"\t"<<MatO.Vect3.y<<"\t"<<MatO.Vect3.z<<endl;
}*/


Matrice3D JaySpace::MatriceInverse(Matrice3D MatO)
{
	float Det;
	Matrice3D MatTrans;

	Det = Determinant(MatO);
	MatTrans = MatriceTransformee(MatO);

	MatO.Vect1.x = MatTrans.Vect1.x / Det;
	MatO.Vect1.y = MatTrans.Vect2.x / Det;
	MatO.Vect1.z = MatTrans.Vect3.x / Det;
	MatO.Vect2.x = MatTrans.Vect1.y / Det;
	MatO.Vect2.y = MatTrans.Vect2.y / Det;
	MatO.Vect2.z = MatTrans.Vect3.y / Det;
	MatO.Vect3.x = MatTrans.Vect1.z / Det;
	MatO.Vect3.y = MatTrans.Vect2.z / Det;
	MatO.Vect3.z = MatTrans.Vect3.z / Det;

	//	VoirMatrice(MatO);

	return(MatO);
}

Vecteur3D JaySpace::MulMat(Matrice3D Mat, Vecteur3D Vect)
{
	Vecteur3D VectFinal;

	VectFinal.x = Mat.Vect1.x * Vect.x + Mat.Vect2.x * Vect.y + Mat.Vect3.x * Vect.z;
	VectFinal.y = Mat.Vect1.y * Vect.x + Mat.Vect2.y * Vect.y + Mat.Vect3.y * Vect.z;
	VectFinal.z = Mat.Vect1.z * Vect.x + Mat.Vect2.z * Vect.y + Mat.Vect3.z * Vect.z;

	return VectFinal;
}

Matrice3D JaySpace::MulMat(Matrice3D Mat1, Matrice3D Mat2)
{
	Matrice3D MatFinale;

	MatFinale.Vect1 = MulMat(Mat1, Mat2.Vect1);
	MatFinale.Vect2 = MulMat(Mat1, Mat2.Vect2);
	MatFinale.Vect3 = MulMat(Mat1, Mat2.Vect3);

	return MatFinale;
}


Vecteur2D JaySpace::MakeVecteur(float x, float y)
{
	Vecteur2D Vect;
	Vect.getVector(x, y);
	return(Vect);
}

Vecteur2D JaySpace::MakeVecteur(Coord2D Pt)
{
	Vecteur2D Vect;
	Vect.getVector(Pt.x, Pt.y);
	return(Vect);
}

Coord2Ds JaySpace::MakePointS(float x, float y)
{
	Coord2Ds Pt;
	Pt.getVector(x, y);
	return(Pt);
}

Coord2D JaySpace::MakePoint(float x, float y)
{
	Coord2D Pt;
	Pt.getVector(x, y);
	return(Pt);
}

void JaySpace::Translation(Coord2D& Pt, Vecteur2D Vect)
{
	Pt.getVector(Pt.x + Vect.x, Pt.y + Vect.y);
}

void JaySpace::Translation(Coord2D& Pt, float x, float y)
{
	Pt.getVector(Pt.x + x, Pt.y + y);
}

Coord2D JaySpace::Rotation(Coord2D Pt0Rot, Coord2D PtToRot, float AngleDeg)	//	L'angle est en degr�
{
	if (AngleDeg != 0)
	{
		AngleDeg /= Degree_Rad;
		float COS1, SIN1, COS2, SIN2;
		Coord2D PointRotated;

		PointRotated.getVector(PtToRot.x - Pt0Rot.x, PtToRot.y - Pt0Rot.y);

		float AngleDeg1 = atan(PointRotated.y / PointRotated.x);

		AngleDeg += AngleDeg1;

		COS1 = cos(AngleDeg1);
		SIN1 = sin(AngleDeg1);
		COS2 = cos(AngleDeg);
		SIN2 = sin(AngleDeg);

		PointRotated.getVector((PointRotated.x * COS2 / COS1) + Pt0Rot.x, (PointRotated.y * SIN2 / SIN1) + Pt0Rot.y);

		PtToRot = PointRotated;
	}
	return PtToRot;
}

Coord2D JaySpace::Rotation(Coord2D Pt0Rot, float x, float y, float AngleDeg)	//	L'angle est en degr�
{
	if (AngleDeg != 0)
	{
		Coord2D Pt;
		Pt.getVector(x, y);
		Pt0Rot = Rotation(Pt0Rot, Pt, AngleDeg);
		x = Pt.x;
		y = Pt.y;
	}

	return Coord2D(x, y);
}


Vecteur3D JaySpace::BadScaling3D(Vecteur3D PtToScale, Vecteur3D ief, Vecteur3D VectRatio, float Mvt)
{
	Mvt += 1.0;
	Vecteur3D Vect, VectDiff;
	Vect.getVector(PtToScale.x - ief.x, PtToScale.y - ief.y, PtToScale.z - ief.z);
	VectDiff = Vect * Mvt;
	Vect = VectDiff - Vect;

	PtToScale = Vect + ief;

	return(PtToScale);
}

Vecteur3D JaySpace::Scaling(Vecteur3D PtToScale, Vecteur3D ief, Vecteur3D VectRatio)
{
	PtToScale = PtToScale - ief;
	PtToScale.getVector(PtToScale.x * VectRatio.x, PtToScale.y * VectRatio.y, PtToScale.z * VectRatio.z);
	PtToScale = PtToScale + ief;
	return(PtToScale);
}

Vecteur3D JaySpace::Scaling(Vecteur3D PtToScale, Vecteur3D ief, float Ratio)
{
	PtToScale = PtToScale - ief;
	PtToScale.getVector(PtToScale.x * Ratio, PtToScale.y * Ratio, PtToScale.z * Ratio);
	PtToScale = PtToScale + ief;
	return(PtToScale);
}



Coord2D JaySpace::Scale(Coord2D ief, Coord2D PtToScale, float Mvt)
{
	Mvt += 1.0;
	Vecteur2D Vect;
	Vect.getVector(PtToScale.x - ief.x, PtToScale.y - ief.y);
	float Lenght = sqrt(Vect.x * Vect.x + Vect.y * Vect.y);
	Lenght = Lenght * Mvt;
	Vect = VectNorm(Vect);

	PtToScale.getVector(Lenght * Vect.x + ief.x, Lenght * Vect.y + ief.y);

	return PtToScale;
}


Vecteur3D JaySpace::Rotation(Vecteur3D Vect, Vecteur3D VectRot, float Angle)
{
	assert(Vect != 0);
	assert(VectRot != 0);
	assert(!isnan(Vect.x));

	if (Angle != 0)
	{
		Vecteur3D VectP, VectQ;
		Matrice3D MatTC, MatTB;
		Matrice3D CMatB, BMatC;

		Angle /= Degree_Rad;
		float COS = glm::cos(Angle), SIN = glm::sin(Angle);

		VectRot.normalize();

		VectQ.getVector(0, 0, 1);

		if (VectRot /= VectQ) VectQ.getVector(1, 0, 0);

		VectP = ProduitVectoriel(VectRot, VectQ);
		normalize(VectP);
		VectQ = ProduitVectoriel(VectRot, VectP);
		normalize(VectQ);

		//VectP = ProduitVectoriel(VectQ, VectRot);
		//normalize(VectP);
		//VectQ = ProduitVectoriel(VectRot, VectP);
		//normalize(VectQ);

		CMatB.getVectors(VectP, VectQ, VectRot);
		BMatC = MatriceInverse(CMatB);
		MatTB.getVectors(Vecteur3D(COS, SIN, 0), Vecteur3D(-SIN, COS, 0), Vecteur3D(0, 0, 1));

		MatTC = MulMat(CMatB, MatTB);
		MatTC = MulMat(MulMat(CMatB, MatTB), BMatC);
		Vect.getVector(MulMat(MatTC, Vect));
	}
	assert(!isnan(Vect.x));

	return Vect;
}


glm::vec3 JaySpace::Rotation(glm::vec3 Vect, glm::vec3 VectRot, float Angle)
{
	Vecteur3D Vect2Rotate(Vect.x, Vect.y, Vect.z);
	Vecteur3D Vect2Use4Rotation(VectRot.x, VectRot.y, VectRot.z);

	Vect2Rotate = Rotation(Vect2Rotate, Vect2Use4Rotation, Angle);

	Vect = glm::vec3(Vect2Rotate.x, Vect2Rotate.y, Vect2Rotate.z);

	return Vect;
}


Vecteur3D JaySpace::RotationWithMax(Vecteur3D Point, Vecteur3D P0_VectRot, Vecteur3D VectRot, float Angle, Vecteur3D VectMax)
{
	if (Angle != 0)
	{
		Vecteur3D Vect;

		Vect.getVector(Point.x - P0_VectRot.x, Point.y - P0_VectRot.y, Point.z - P0_VectRot.z);
		/*
				float ABV = AngleBetweenVectors(Vect, VectMax);

				if (ABV < abs(Angle))
					if (IsSameSideVector(ProduitVectoriel(Vect,VectRot), VectRot))
				{
					Angle = ABV;
				}
		*/
		Vect = Rotation(Vect, VectRot, Angle);

		Point.getVector(Vect.x + P0_VectRot.x, Vect.y + P0_VectRot.y, Vect.z + P0_VectRot.z);

	}

	return Point;
}

Vecteur3D JaySpace::Rotation(Vecteur3D VectToRotate, Vecteur3D P0_VectRot, Vecteur3D VectRot, float Angle)
{
	if (Angle != 0)
	{
		Vecteur3D Pt = VectToRotate - P0_VectRot;

		assert(!isnan(Pt.x));
		VectToRotate = Rotation(Pt, VectRot, Angle) + P0_VectRot;
	}

	assert(!isnan(VectToRotate.x));
	return VectToRotate;
}

glm::vec3 JaySpace::Rotation(glm::vec3 VectToRotate, glm::vec3 P0_VectRot, glm::vec3 VectRot, float Angle)
{
	if (Angle != 0)
	{
		glm::vec3 Pt = VectToRotate - P0_VectRot;

		assert(!isnan(Pt.x));
		VectToRotate = Rotation(Pt, VectRot, Angle) + P0_VectRot;
	}

	assert(!isnan(VectToRotate.x));
	return VectToRotate;
}

Droite3D JaySpace::Rotation(Droite3D Dr1, Vecteur3D VectRot, float Angle)
{
	if (Angle != 0)
	{
		Vecteur3D Vect;

		Vect.getVector(Dr1.Pt1.x, Dr1.Pt1.y, Dr1.Pt1.z);
		Vect = Rotation(Vect, VectRot, Angle);
		Dr1.Pt1.getVector(Vect.x, Vect.y, Vect.z);

		Vect.getVector(Dr1.Pt2.x, Dr1.Pt2.y, Dr1.Pt2.z);
		Vect = Rotation(Vect, VectRot, Angle);
		Dr1.Pt2.getVector(Vect.x, Vect.y, Vect.z);

		Dr1.CalculVect();
	}
	return Dr1;
}


Vecteur3D JaySpace::Rotation(Vecteur3D Point, float P0_X, float P0_Y, float P0_Z, float VR_X, float VR_Y, float VR_Z, float Angle)
{
	if (Angle != 0)
	{
		Vecteur3D Vect, VectRot;
		Vecteur3D P0_VectRot;

		P0_VectRot.getVector(P0_X, P0_Y, P0_Z);

		Vect.getVector(Point.x - P0_VectRot.x, Point.y - P0_VectRot.y, Point.z - P0_VectRot.z);

		VectRot.getVector(VR_X, VR_Y, VR_Z);

		Vect = Rotation(Vect, VectRot, Angle);

		Point.getVector(Vect.x + P0_VectRot.x, Vect.y + P0_VectRot.y, Vect.z + P0_VectRot.z);
	}
	return Point;
}



void JaySpace::Translation(Vecteur3D& Point1, Vecteur3D Point2)
{
	Point1 += Point2;
}



Vecteur3D JaySpace::Translation(Vecteur3D& Point, Vecteur3D PtTrans, Vecteur3D VectTrans, float Distance)
{
	Point.x += PtTrans.x;
	Point.y += PtTrans.y;
	Point.z += PtTrans.z;

	return(Point);
}

Vecteur3D JaySpace::Translation(Vecteur3D& Point, Vecteur3D VectTrans, float Distance)
{
	normalize(VectTrans);
	Point.x += VectTrans.x * Distance;
	Point.y += VectTrans.y * Distance;
	Point.z += VectTrans.z * Distance;

	return(Point);
}

Vecteur3D JaySpace::Translation(Vecteur3D& Point, float x, float y, float z, float Distance)
{
	Vecteur3D VectTrans;
	VectTrans.getVector(x, y, z);
	return Translation(Point, VectTrans, Distance);
}

Droite3D JaySpace::CalculerDroite(Vecteur3D Vect)
{
	Droite3D NewDr;
	NewDr.InitDroite(Vect);
	return(NewDr);
}

Droite3D JaySpace::CalculerDroite(Vecteur3D Pt, Vecteur3D Vect)
{
	Droite3D NewDr;
	NewDr.InitDroite(Pt, Vect);
	return(NewDr);
}


Droite3D JaySpace::CalculerDroite(float x, float y, float z)
{
	Droite3D NewDr;
	NewDr.InitDroite(x, y, z);
	return(NewDr);
}

Plan JaySpace::calculerPlan(Droite3D Dr1, Vecteur3D Vect1)
{
	Plan NewP;

	NewP.getPosInit(Dr1.Pt1);
	NewP.Vect1 = Dr1.Vect;
	NewP.Vect2 = Vect1;
	NewP.CalNS();

	return(NewP);
}

Plan JaySpace::calculerPlan(Droite3D Dr1, Droite3D Dr2)
{
	Plan NewP;

	NewP.getPosInit(Dr1.Pt1);
	NewP.Vect1 = Dr1.Vect;
	NewP.Vect2 = Dr2.Vect;
	NewP.CalNS();

	return(NewP);
}

Plan JaySpace::calculerPlan(Vecteur3D Vect1, Vecteur3D Vect2)
{
	Plan NewP;

	NewP.Vect1 = Vect1;
	NewP.Vect2 = Vect2;
	NewP.CalNS();

	return(NewP);
}


Plan JaySpace::calculerPlan_pt_norm(Vecteur3D Pt1, Vecteur3D VectN)
{
	Plan NewP;

	NewP.getPosInit(Pt1);
	NewP.VectNor = VectN;
	NewP.CalSommme();

	return(NewP);
}


Vecteur3D JaySpace::Projection(Vecteur3D Pt, Plan PLAN)
{
	return(Contact_Droite_Plan(CalculerDroite(Pt, PLAN.VectNor), PLAN));
}

Droite3D JaySpace::Projection(Droite3D Dr1, Plan PLAN)
{
	Droite3D NewDr;
	NewDr.InitDroite(Projection(Dr1.Pt1, PLAN), Projection(Dr1.Pt2, PLAN));
	return(NewDr);
}

Droite3D JaySpace::CalculerPerp(Droite3D Dr1, Plan PLAN)
{
	Dr1 = Rotation(Dr1, PLAN.VectNor, 90);
	return(Dr1);
}

Vecteur3D JaySpace::EcrirePoint(float x, float y, float z)
{
	Vecteur3D Pt;
	Pt.getVector(x, y, z);
	return(Pt);
}

Vecteur3D JaySpace::EcrireVector(float x, float y, float z)
{
	Vecteur3D Vect;
	Vect.getVector(x, y, z);
	return(Vect);
}

float JaySpace::CalculerYCercle(float PosX, float Ray, bool Up, float XToGive)
{
	float ReturnY;
	float Ray2 = Ray * Ray, XDown2 = (PosX - XToGive) * (PosX - XToGive);

	ReturnY = sqrt(Ray2 - XDown2);

	if (Up)
	{
		return(ReturnY);
	}
	else
	{
		return(-ReturnY);
	}
}


float JaySpace::ReturnLenght(Vecteur3D PtToCalculate)
{
	return(PtToCalculate.x * PtToCalculate.x + PtToCalculate.y * PtToCalculate.y + PtToCalculate.z * PtToCalculate.z);
}




void JaySpace::DivVectbyNumber(Vecteur3D& Vect, float Number)
{
	Vect.getVector((float)Vect.x / Number, (float)Vect.y / Number, (float)Vect.z / Number);
}

Vecteur3D JaySpace::Add(Vecteur3D& Point1, Vecteur3D Vect, float Frac)
{
	return(Point1 = Point1 + Vect * Frac);
}

Vecteur3D JaySpace::Sous(Vecteur3D& Point1, Vecteur3D Vect, float Frac)
{
	return(Point1 = Point1 - Vect * Frac);
}


Vecteur3D JaySpace::MakeVecteur(Vecteur3D Vect1, Vecteur3D Vect2)
{
	return(Vect2 - Vect1);
}



Vecteur3D JaySpace::MakePoint(Vecteur3D Vect)
{
	Vecteur3D Pt;
	Pt.getVector(Vect.x, Vect.y, Vect.z);
	return(Pt);
}

Vecteur3D JaySpace::VecteurInverse(Vecteur3D Vect)
{
	return(Vecteur3D(-Vect.x, -Vect.y, -Vect.z));
}

Vecteur3D JaySpace::Div(Vecteur3D Vect, float Number)
{
	return(Vecteur3D((float)Vect.x / Number, (float)Vect.y / Number, (float)Vect.z / Number));
}

Vecteur3D JaySpace::Multi(Vecteur3D Vect, float Number)
{
	return(Vect * Number);
}
void JaySpace::MultiVoid(Vecteur3D& Vect, float Number)
{
	Vect = Vect * Number;
}



float JaySpace::dot(Vecteur3D Vect1, Vecteur3D Vect2)
{
	return (Vect1.x * Vect2.x + Vect1.y * Vect2.y + Vect1.z * Vect2.z);
}

float JaySpace::dot(Vecteur2D Vect1, Vecteur2D Vect2)
{
	return (Vect1.x * Vect2.x + Vect1.y * Vect2.y);
}

Vecteur3D JaySpace::ProduitVectoriel(Vecteur3D Vect1, Vecteur3D Vect2)
{
	Vecteur3D VectFinal;

	VectFinal.x = Vect1.y * Vect2.z - Vect1.z * Vect2.y;
	VectFinal.y = Vect1.z * Vect2.x - Vect1.x * Vect2.z;
	VectFinal.z = Vect1.x * Vect2.y - Vect1.y * Vect2.x;

	return (VectFinal);
}

glm::vec3 JaySpace::ProduitVectoriel(glm::vec3 Vect1, glm::vec3 Vect2)
{
	glm::vec3 VectFinal;

	VectFinal.x = Vect1.y * Vect2.z - Vect1.z * Vect2.y;
	VectFinal.y = Vect1.z * Vect2.x - Vect1.x * Vect2.z;
	VectFinal.z = Vect1.x * Vect2.y - Vect1.y * Vect2.x;

	return (VectFinal);
}


Vecteur3D JaySpace::normalize(Vecteur3D& Vect)
{
	float Longueur = (float)sqrt(Vect.x * Vect.x + Vect.y * Vect.y + Vect.z * Vect.z);

	if (Longueur != 0)
	{
		Vect.x /= Longueur;
		Vect.y /= Longueur;
		Vect.z /= Longueur;
		return(Vect);
	}
	else
	{
		assert("Normalize in calcul_math.cpp : division by Zero!!!");
		return Vect;
	}

}


Vecteur2D JaySpace::normalize(Vecteur2D& Vect)
{
	float Longueur;

	Longueur = sqrt(Vect.x * Vect.x + Vect.y * Vect.y);

	if (Longueur != 0)
	{
		Vect.x = (float)Vect.x / (float)Longueur;
		Vect.y = (float)Vect.y / (float)Longueur;
	}

	return(Vect);
}

bool JaySpace::IsVectorParallel(Vecteur3D Vect1, Vecteur3D Vect2)
{
	normalize(Vect1);
	normalize(Vect2);

	if (Vect1.x == Vect2.x &&
		Vect1.y == Vect2.y &&
		Vect1.z == Vect2.z)
		return(true);
	else
		return(false);
}

Vecteur3D JaySpace::VectNorm(Vecteur3D Vect)
{
	float Longueur;

	Longueur = sqrt(Vect.x * Vect.x + Vect.y * Vect.y + Vect.z * Vect.z);

	Vect.x /= Longueur;
	Vect.y /= Longueur;
	Vect.z /= Longueur;

	return(Vect);
}


Vecteur3D JaySpace::norm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd)
{
	//	Fonction qui assume que NewVectToAdd est d�j� normalis�
	//	assert(GetLength(NewVectToAdd) == 1.0);

	CountPt++;
	Vecteur3D newVect = normalize(&((ActualNorm * (CountPt - 1) + NewVectToAdd) / CountPt));
	return newVect;
}

Vecteur3D JaySpace::CalculateNorm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd)
{
	//	Fonction qui assume que NewVectToAdd est d�j� normalis�
	//	assert(GetLength(NewVectToAdd) == 1.0);
	CountPt++;
	ActualNorm.getVector(
		(float)ActualNorm.x * (CountPt - 1) / CountPt + (float)NewVectToAdd.x / CountPt,
		(float)ActualNorm.y * (CountPt - 1) / CountPt + (float)NewVectToAdd.y / CountPt,
		(float)ActualNorm.z * (CountPt - 1) / CountPt + (float)NewVectToAdd.z / CountPt);
	normalize(ActualNorm);
	return ActualNorm;
}

Vecteur3D JaySpace::CalculateVectNorm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd)
{
	normalize(NewVectToAdd);
	CountPt++;
	ActualNorm.getVector(
		(float)ActualNorm.x * (CountPt - 1) / CountPt + (float)NewVectToAdd.x / CountPt,
		(float)ActualNorm.y * (CountPt - 1) / CountPt + (float)NewVectToAdd.y / CountPt,
		(float)ActualNorm.z * (CountPt - 1) / CountPt + (float)NewVectToAdd.z / CountPt);
	normalize(ActualNorm);
	return ActualNorm;
}

Vecteur3D JaySpace::CalculateVectNorm_WithoutNormalizing(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd)
{
	CountPt++;
	ActualNorm.getVector(
		(float)ActualNorm.x * (CountPt - 1) / CountPt + (float)NewVectToAdd.x / CountPt,
		(float)ActualNorm.y * (CountPt - 1) / CountPt + (float)NewVectToAdd.y / CountPt,
		(float)ActualNorm.z * (CountPt - 1) / CountPt + (float)NewVectToAdd.z / CountPt);
	return ActualNorm;
}

glm::vec2 JaySpace::Coord3DToScreen2DVect(glm::vec3 coord, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect)
{
	//   The FOV (field of view) has to be the complete vertical one, not 1/2.
	//	We also assume rightVect and vertVect have been normalised.
	glm::vec3 dir = target - campos;
	coord = Contact_Droite_Plan(coord, dir, target, dir);
	glm::vec3 xcoord = Contact_Droite_Plan(target, rightVect, coord, rightVect);

	return glm::vec2(Magnitude(target-xcoord), Magnitude(coord - xcoord));
}

glm::vec2 JaySpace::Coord3DToScreenFov(glm::vec3 coord, float fov, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect)
{
	glm::vec2 coord2D = Coord3DToScreen2DVect(coord, campos, target, rightVect);

	// Convert to angles
	float dirLength = Magnitude(target - campos);
	return glm::vec2(atan(coord2D.x / dirLength), atan(coord2D.y / dirLength));
}

glm::vec2 JaySpace::Coord3DToScreen2DCoord(glm::vec3 coord, float fov, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect, int windowWidth, int windowHeight) {
	//  Get the 2D coordonnates invert right and vertVect
	glm::vec2 coord2D = Coord3DToScreenFov(coord, fov, campos, target, rightVect);

	// Convert to screen coordinates
	return glm::vec2(coord2D.x / fov / windowHeight * windowWidth / 2.0f * windowWidth, coord2D.y / fov / 2.0f * windowHeight);
}

//


//template <typename ptlist>
//void CalculateVectNorm(Vecteur3D& ActualNorm, int& CountPt, ptlist* PTList)
//{
//	ptlist::iterator it, beg = PTList->begin();
//	it = beg;

//	for (int n = 3; n < 0 && it != PTList->end(); --n, ++beg) {}
//	for (; it != PTList->end(); ++i)
//	{
//		it = beg;
//		CountPt++;
//		//	ActualNorm = ActualNorm*(CountPt - 1) / CountPt + VectToUse / CountPt
//		ActualNorm = ActualNorm * (CountPt - 1) / CountPt + normalize(ProduitVectoriel(MakeVecteur(*it, *(++it)), MakeVecteur(*it, *(++it)))) / CountPt;
//	}
//	normalize(ActualNorm);
//	return ActualNorm;
//}

Vecteur2D JaySpace::VectNorm(Vecteur2D Vect)
{
	float Longueur;

	Longueur = sqrt(Vect.x * Vect.x + Vect.y * Vect.y);

	Vect.x /= Longueur;
	Vect.y /= Longueur;

	return(Vect);
}

float JaySpace::GetLength(Vecteur2D Vect)
{
	return sqrt(Vect.x * Vect.x + Vect.y * Vect.y);
}



float JaySpace::GetLength(Vecteur3D Vect)
{
	return sqrt(Vect.x * Vect.x + Vect.y * Vect.y + Vect.z * Vect.z);
}


float JaySpace::Distance(Vecteur3D Pt1, Vecteur3D Pt2)
{
	return(GetLength(Pt2 - Pt1));
}

bool JaySpace::CheckEquals(Vecteur3D Vect1, Vecteur3D Vect2)
{
	normalize(Vect1);
	normalize(Vect2);

	if ((Vect1.x == Vect2.x &&
		Vect1.y == Vect2.y &&
		Vect1.z == Vect2.z) ||
		(Vect1.x == -Vect2.x &&
			Vect1.y == -Vect2.y &&
			Vect1.z == -Vect2.z))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

Vecteur3D JaySpace::MakeAverageVector(Vecteur3D Vect1, Vecteur3D Vect2)
{
	Vect1.getVector((Vect1.x + Vect2.x) / 2.0, (Vect1.y + Vect2.y) / 2.0, (Vect1.z + Vect2.z) / 2.0);
	return(Vect1);
}

bool JaySpace::IsSideWiseVector(Vecteur3D Vect1, Vecteur3D Vect2)
{
	normalize(Vect1);
	normalize(Vect2);
	return (
		((Vect1.x >= 0 && Vect2.x <= 0) &&
			(Vect1.y >= 0 && Vect2.y <= 0) &&
			(Vect1.z >= 0 && Vect2.z <= 0)) ||
		((Vect2.x >= 0 && Vect1.x <= 0) &&
			(Vect2.y >= 0 && Vect1.y <= 0) &&
			(Vect2.z >= 0 && Vect1.z <= 0)));
}


bool JaySpace::IsSameSideVector(Vecteur3D Vect1, Vecteur3D Vect2)
{
	normalize(Vect1);
	normalize(Vect2);
	return (
		((Vect1.x >= 0 && Vect2.x >= 0) &&
			(Vect1.y >= 0 && Vect2.y >= 0) &&
			(Vect1.z >= 0 && Vect2.z >= 0)) ||
		((Vect2.x <= 0 && Vect1.x <= 0) &&
			(Vect2.y <= 0 && Vect1.y <= 0) &&
			(Vect2.z <= 0 && Vect1.z <= 0)));
}





float JaySpace::Absolute(float num)
{
	// If num is less than zero, we want to return the absolute value of num.
	// This is simple, either we times num by -1 or subtract it from 0.
	if (num < 0)
		return (0 - num);

	// Return the original number because it was already positive
	return num;
}


/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a perpendicular vector from 2 given vectors by taking the cross product.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::CrossVecteur(Vecteur3D vVector1, Vecteur3D vVector2)
{
	Vecteur3D vNormal;									// The vector to hold the cross product

	// The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)													// Get the X value
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

	// The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

	// The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;										// Return the cross product (Direction the polygon is facing - Normal)
}


/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a normal (or any other vector)
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float JaySpace::Magnitude(Vecteur3D vNormal)
{
	// This will give us the magnitude or "Norm" as some say, of our normal.
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector

	return (float)sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}


/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the normal of a polygon (The direction the polygon is facing)
/////
/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::normalize(Vecteur3D vPolygon[])
{														// Get 2 vectors from the polygon (2 sides), Remember the order!
	Vecteur3D vVector1 = vPolygon[2] - vPolygon[0];
	Vecteur3D vVector2 = vPolygon[1] - vPolygon[0];

	Vecteur3D vNormal = CrossVecteur(vVector1, vVector2);		// Take the cross product of our 2 vectors to get a perpendicular vector

	// Now we have a normal, but it's at a strange length, so let's make it length 1.

	vNormal = normalize(vNormal);						// Use our function we created to normalize the normal (Makes it a length of one)

	return vNormal;										// Return our normal at our desired length
}


/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the distance between 2 3D points
/////
/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This computers the dot product of 2 vectors
/////
/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float JaySpace::Dot(Vecteur3D vVector1, Vecteur3D vVector2)
{
	// The dot product is this equation: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
	// In math terms, it looks like this:  V1.V2 = ||V1|| ||V2|| cos(theta)

			 //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
	return ((vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z));
}



////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the point on the line vA_vB that is closest to the point vPoint
/////
////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::ClosestPointOnLine(Vecteur3D vA, Vecteur3D vB, Vecteur3D vPoint)
{
	// Create the vector from end point vA to our point vPoint.
	Vecteur3D vVector1 = vPoint - vA;

	// Create a normalized direction vector from end point vA to end point vB
	Vecteur3D vVector2 = normalize(&(vB - vA));

	// Use the distance formula to find the distance of the line segment (or magnitude)
	float d = Distance(vA, vB);

	// Using the dot product, we project the vVector1 onto the vector vVector2.
	// This essentially gives us the distance from our projected vector from vA.
	float t = Dot(vVector2, vVector1);

	// If our projected distance from vA, "t", is less than or equal to 0, it must
	// be closest to the end point vA.  We want to return this end point.
	if (t <= 0)
		return vA;

	// If our projected distance from vA, "t", is greater than or equal to the magnitude
	// or distance of the line segment, it must be closest to the end point vB.  So, return vB.
	if (t >= d)
		return vB;

	// Here we create a vector that is of length t and in the direction of vVector2
	Vecteur3D vVector3 = vVector2 * t;

	// To find the closest point on the line segment, we just add vVector3 to the original
	// end point vA.  
	Vecteur3D vClosestPoint = vA + vVector3;

	// Return the closest point on the line segment
	return vClosestPoint;
}


/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the distance between a plane and the origin
/////
/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float JaySpace::PlaneDistance(Vecteur3D Normal, Vecteur3D Point)
{
	float distance = 0;									// This variable holds the distance from the plane tot he origin

	// Use the plane equation to find the distance (Ax + By + Cz + D = 0)  We want to find D.
	// So, we come up with D = -(Ax + By + Cz)
														// Basically, the negated dot product of the normal of the plane and the point. (More about the dot product in another tutorial)
	distance = -((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

	return distance;									// Return the distance
}


/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a line intersects a plane
/////
/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool JaySpace::IntersectedPlane(Vecteur3D vPoly[], Vecteur3D vLine[], Vecteur3D& vNormal, float& originDistance)
{
	float distance1 = 0, distance2 = 0;						// The distances from the 2 points of the line from the plane

	vNormal = normalize(vPoly);							// We need to get the normal of our plane to go any further

	// Let's find the distance our plane is from the origin.  We can find this value
	// from the normal to the plane (polygon) and any point that lies on that plane (Any vertex)
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

	distance1 = ((vNormal.x * vLine[0].x) +					// Ax +
		(vNormal.y * vLine[0].y) +					// Bx +
		(vNormal.z * vLine[0].z)) + originDistance;	// Cz + D

	// Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)

	distance2 = ((vNormal.x * vLine[1].x) +					// Ax +
		(vNormal.y * vLine[1].y) +					// Bx +
		(vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	// Now that we have 2 distances from the plane, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

	if (distance1 * distance2 >= 0)			// Check to see if both point's distances are both negative or both positive
		return false;						// Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...

	return true;							// The line intersected the plane, Return TRUE
}



/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::Contact_Droite_Plan(Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtPl, Vecteur3D VectPl);

float JaySpace::AngleBetweenVectors(Vecteur3D Vector1, Vecteur3D Vector2)
{
	//	float angle = asin(GetLength(ProduitVectoriel(Vector1, Vector2)) / (GetLength(Vector1)+GetLength(Vector2)));
	if (Vector1 /= Vector2)
		return(0);

	Vecteur3D Pt1 = Vecteur3D(0, 0, 0), Pt2 = Vector2 + Pt1, Pt3;
	Pt3 = Contact_Droite_Plan(Pt1, Vector1, Pt2, Vector1);
	float Long1 = Distance(Pt1, Pt3), Long2 = Distance(Pt1, Pt2);
	float angle = acos(Long1 / Long2) * Degree_Rad;

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate
	if (_isnan(angle))
		return 0;

	// Return the angle in radians
	return(angle);
}


/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the intersection point of the line that intersects the plane
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::IntersectionPoint(Vecteur3D vNormal, Vecteur3D vLine[], double distance)
{
	Vecteur3D vPoint, vLineDir;					// Variables to hold the point and the line's direction
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = vLine[1] - vLine[0];		// Get the Vector of the line
	vLineDir = normalize(vLineDir);				// normalize the lines vector


	// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the 
	// distance from one of our points to the plane.
	Numerator = -(vNormal.x * vLine[0].x +		// Use the plane equation with the normal and the line
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	Denominator = Dot(vNormal, vLineDir);		// Get the dot product of the line's vector and the normal of the plane

	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).  
	// In this case, we should just return any point on the line.

	if (Denominator == 0.0)						// Check so we don't divide by zero
		return vLine[0];						// Return an arbitrary point on the line

	dist = Numerator / Denominator;				// Divide to get the multiplying (percentage) factor

	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								// Return the intersection point
}



/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool JaySpace::InsidePolygon(Vecteur3D vIntersection, Vecteur3D Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.99;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	Vecteur3D vA, vB;						// Create temp vectors

	for (int i = 0; i < verticeCount; i++)		// Go in a circle to each vertex and get the angle between
	{
		vA = Poly[i] - vIntersection;			// Subtract the intersection point from the current vertex
		// Subtract the point from the next vertex
		vB = Poly[(i + 1) % verticeCount] - vIntersection;

		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}

	if (Angle >= (MATCH_FACTOR * (2.0 * PI)))	// If the angle is greater than 2 PI, (360 degrees)
		return true;							// The point is inside of the polygon

	return false;								// If you get here, it obviously wasn't inside the polygon, so Return FALSE
}


/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks if a line is intersecting a polygon
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool JaySpace::IntersectedPolygon(Vecteur3D vPoly[], Vecteur3D vLine[], int verticeCount)
{
	Vecteur3D vNormal;
	float originDistance = 0;

	// First, make sure our line intersects the plane
									 // Reference   // Reference
	if (!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
		return false;

	// Now that we have our normal and distance passed back from IntersectedPlane(), 
	// we can use it to calculate the intersection point.  
	Vecteur3D vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// Now that we have the intersection point, we need to test if it's inside the polygon.
	if (InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;							// We collided!	  Return success

	return false;								// There was no collision, so return false
}


///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This tells if a sphere is BEHIND, in FRONT, or INTERSECTS a plane, also it's distance
/////
///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int JaySpace::ClassifySphere(Vecteur3D& vCenter,
	Vecteur3D& vNormal, Vecteur3D& vPoint, float radius, float& distance)
{
	// First we need to find the distance our polygon plane is from the origin.
	float d = (float)PlaneDistance(vNormal, vPoint);

	// Here we use the famous distance formula to find the distance the center point
	// of the sphere is from the polygon's plane.  
	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	// If the absolute value of the distance we just found is less than the radius, 
	// the sphere intersected the plane.
	if (Absolute(distance) < radius)
		return INTERSECTS;
	// Else, if the distance is greater than or equal to the radius, the sphere is
	// completely in FRONT of the plane.
	else if (distance >= radius)
		return FRONT;

	// If the sphere isn't intersecting or in FRONT of the plane, it must be BEHIND
	return BEHIND;
}


///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns true if the sphere is intersecting any of the edges of the polygon
/////
///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool JaySpace::EdgeSphereCollision(Vecteur3D& vCenter,
	Vecteur3D vPolygon[], int vertexCount, float radius)
{
	Vecteur3D vPoint;

	// This function takes in the sphere's center, the polygon's vertices, the vertex count
	// and the radius of the sphere.  We will return true from this function if the sphere
	// is intersecting any of the edges of the polygon.  

	// Go through all of the vertices in the polygon
	for (int i = 0; i < vertexCount; i++)
	{
		// This returns the closest point on the current edge to the center of the sphere.
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);

		// Now, we want to calculate the distance between the closest point and the center
		float distance = Distance(vPoint, vCenter);

		// If the distance is less than the radius, there must be a collision so return true
		if (distance < radius)
			return true;
	}

	// The was no intersection of the sphere and the edges of the polygon
	return false;
}


////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns true if our sphere collides with the polygon passed in
/////
////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool JaySpace::SpherePolygonCollision(Vecteur3D vPolygon[],
	Vecteur3D& vCenter, int vertexCount, float radius)
{
	// 1) STEP ONE - Finding the sphere's classification

	// Let's use our Normal() function to return us the normal to this polygon
	Vecteur3D vNormal = normalize(vPolygon);

	// This will store the distance our sphere is from the plane
	float distance = 0.0f;

	// This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the plane
	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);

	// If the sphere intersects the polygon's plane, then we need to check further
	if (classification == INTERSECTS)
	{
		// 2) STEP TWO - Finding the Bnuedo intersection point on the plane

		// Now we want to project the sphere's center onto the polygon's plane
		Vecteur3D vOffset = vNormal * distance;

		// Once we have the offset to the plane, we just subtract it from the center
		// of the sphere.  "vPosition" now a point that lies on the plane of the polygon.
		Vecteur3D vPosition = vCenter - vOffset;

		// 3) STEP THREE - Check if the intersection point is inside the polygons perimeter

		// If the intersection point is inside the perimeter of the polygon, it returns true.
		// We pass in the intersection point, the list of vertices and vertex count of the poly.
		if (InsidePolygon(vPosition, vPolygon, 3))
			return true;	// We collided!
		else
		{
			// 4) STEP FOUR - Check the sphere intersects any of the polygon's edges

			// If we get here, we didn't find an intersection point in the perimeter.
			// We now need to check collision against the edges of the polygon.
			if (EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius))
			{
				return true;	// We collided!
			}
		}
	}

	// If we get here, there is obviously no collision
	return false;
}


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

///////////////////////////////// GET COLLISION OFFSET \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the offset to move the center of the sphere off the collided polygon
/////
///////////////////////////////// GET COLLISION OFFSET \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Vecteur3D JaySpace::GetCollisionOffset(Vecteur3D& vNormal, float radius, float distance)
{
	Vecteur3D vOffset = Vecteur3D(0, 0, 0);

	// Once we find if a collision has taken place, we need make sure the sphere
	// doesn't move into the wall.  In our app, the position will actually move into
	// the wall, but we check our collision detection before we render the scene, which
	// eliminates the bounce back effect it would cause.  The question is, how do we
	// know which direction to move the sphere back?  In our collision detection, we
	// account for collisions on both sides of the polygon.  Usually, you just need
	// to worry about the side with the normal vector and positive distance.  If 
	// you don't want to back face cull and have 2 sided planes, I check for both sides.
	//
	// Let me explain the math that is going on here.  First, we have the normal to
	// the plane, the radius of the sphere, as well as the distance the center of the
	// sphere is from the plane.  In the case of the sphere colliding in the front of
	// the polygon, we can just subtract the distance from the radius, then multiply
	// that new distance by the normal of the plane.  This projects that leftover
	// distance along the normal vector.  For Instance, say we have these values:
	//
	//	vNormal = (1, 0, 0)		radius = 5		distance = 3
	//
	// If we subtract the distance from the radius we get: (5 - 3 = 2)
	// The number 2 tells us that our sphere is over the plane by a distance of 2.
	// So basically, we need to move the sphere back 2 units.  How do we know which
	// direction though?  This part is easy, we have a normal vector that tells us the
	// direction of the plane.  
	// If we multiply the normal by the left over distance we get:  (2, 0, 0)
	// This new offset vectors tells us which direction and how much to move back.
	// We then subtract this offset from the sphere's position, giving is the new
	// position that is lying right on top of the plane.  Ba da bing!
	// If we are colliding from behind the polygon (not usual), we do the opposite
	// signs as seen below:

	// If our distance is greater than zero, we are in front of the polygon
	if (distance > 0)
	{
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else // Else colliding from behind the polygon
	{
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	// There is one problem with check for collisions behind the polygon, and that
	// is if you are moving really fast and your center goes past the front of the
	// polygon, it will then assume you were colliding from behind and not let
	// you back in.  Most likely you will take out the if / else check, but I
	// figured I would show both ways in case someone didn't want to back face cull.

	// Return the offset we need to move back to not be intersecting the polygon.
	return vOffset;
}

void JaySpace::computeTriangleNormals(const std::vector<glm::vec3>& vertices,
	const std::vector<unsigned int>& indices,
	std::vector<glm::vec3>& normals) {
	// Resize normals to match vertices size if needed
	normals.resize(vertices.size(), glm::vec3(0.0f));

	// Process each triangle
	for (size_t i = 0; i < indices.size(); i += 3) {
		unsigned int idx0 = indices[i];
		unsigned int idx1 = indices[i + 1];
		unsigned int idx2 = indices[i + 2];

		glm::vec3 v0 = vertices[idx0];
		glm::vec3 v1 = vertices[idx1];
		glm::vec3 v2 = vertices[idx2];

		// Compute two edges
		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v1;

		// Cross product for normal
		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		// Assign the same normal to all three vertices (flat shading)
		normals[idx0] = normal;
		normals[idx1] = normal;
		normals[idx2] = normal;
	}
}