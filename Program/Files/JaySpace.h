#pragma once

#include "Vecteur.h"
#include "Coordonnee.h"
#include "Droite.h"
#include "Plan.h"
#include "ProjectTeethJay.h"

//	#include "Head.h"


namespace JaySpace {
#define Max_Min		0.00001
#define Min_Min		-0.00001

#define  GLUT_NONE_BUTTON                   0x0000
	//#define None		0

#define	PI		3.1415926535897932384626433832795f
#define PI180	0.0174532925199432957692369076848861f	// pi / 180

#define Degree_Rad 180/PI

#define EPSILON 1.0e-8

#define ZERO EPSILON

#define t_24 1.0/24
#define t_30 1.0/30

#define ColRadRouge		PI/2
#define ColRadBleu		PI*7/6
#define ColRadVerte		PI*11/6

#define OpenGLWidhtDisplay = 1920;
#define OpenGLHeightDisplay = 1080;


#define LargeurWindowsForms = 1305;
#define HauteurWindowsForms = 766;

#define LARGEUR_ECRAN = LargeurWindowsForms - 225;
#define HAUTEUR_ECRAN = HauteurWindowsForms - 146;

#define initXdisplay = 0;
#define initYdisplay = 97;

//	#define	CurrentPosX;
//	#define	CurrentPosY;

	extern float g_Scale;
	extern float g_diffScale;
	extern float g_MouseWheelScale;

	extern int button;
	extern int action;
	extern int mods;

	extern bool button_left;
	extern bool button_right;
	extern bool button_middle;

	extern bool button_left_just_clicked;
	extern bool button_right_just_clicked;
	extern bool button_middle_just_clicked;

	extern bool button_left_just_released;
	extern bool button_right_just_released;
	extern bool button_middle_just_released;

	extern const char** dragNdrop_paths;
	extern int dragNdrop_count;

	//extern ProjectTeethJay projet;

	float& _regulate(float& Num);
	void _cout(glm::vec3);
	void _cout(glm::mat4);
	Vecteur3D _regulate(Vecteur3D& Coord);
	Vecteur2D _regulate(Vecteur2D& Coord);
	Coord2D _regulate(Coord2D& Coord);
	bool _isnan(Vecteur3D PtToEvaluate);
	float Somme(Vecteur3D Pt);
	float FindY(float X, Coord2D Pt1, Coord2D Pt2);
	float FindX(float Y, Coord2D Pt1, Coord2D Pt2);
	bool CroisementDroites(Coord2D& PtCroisement, Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2);
	bool CroisementSegments(Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2);
	bool CroisementSegments(Coord2D& PtCroisement, Coord2D Pt1Dr1, Coord2D Pt2Dr1, Coord2D Pt1Dr2, Coord2D Pt2Dr2);
	bool Equals(Vecteur3D Pt1, Vecteur3D Pt2);
	bool IsParallele(Vecteur3D VectRot, Vecteur3D VectQ);
	Vecteur3D Adds_Point(Vecteur3D Pt1, Vecteur3D Pt2);
	Vecteur3D Souss_Point(Vecteur3D Pt, Vecteur3D Pt2);
	Vecteur3D Multip(Vecteur3D Pt, float Multiplicator);

	Vecteur3D Contact_Droite_Plan(Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtPl, Vecteur3D VectPl);
	Vecteur3D Contact_Droite_Plan(Vecteur3D Point1, Vecteur3D Pt2_VDrt, Plan PLAN);
	Vecteur3D Contact_Droite_Plan(Droite3D Dr1, Plan PLAN);
	Vecteur3D Contact_Droite_Plan(Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtPl, Vecteur3D VectPl);
	glm::vec3 Contact_Droite_Plan(glm::vec3 PtDr, glm::vec3 VectDr, glm::vec3 PtPl, glm::vec3 VectPl);

	int Contact_Droite_Sphere(Vecteur3D& PtCte1, Vecteur3D& PtCte2, Vecteur3D PtDr, Vecteur3D VectDr, Vecteur3D PtCentreSphere, float Rayon);
	float Determinant(Vecteur3D Vect1, Vecteur3D Vect2, Vecteur3D Vect3);
	float Determinant(Matrice3D MatO);
	Matrice3D MatriceTransformee(Matrice3D MatO);
	Matrice3D MatriceInverse(Matrice3D MatO);
	Vecteur3D MulMat(Matrice3D Mat, Vecteur3D Vect);
	Matrice3D MulMat(Matrice3D Mat1, Matrice3D Mat2);
	Vecteur2D MakeVecteur(float x, float y);
	Vecteur2D MakeVecteur(Coord2D Pt);
	Coord2Ds MakePointS(float x, float y);
	Coord2D MakePoint(float x, float y);
	void Translation(Coord2D& Pt, Vecteur2D Vect);
	void Translation(Coord2D& Pt, float x, float y);
	Coord2D Rotation(Coord2D Pt0Rot, Coord2D PtToRot, float AngleDeg);	//	L'angle est en degr�;
	Coord2D Rotation(Coord2D Pt0Rot, float x, float y, float AngleDeg);	//	L'angle est en degr�;
	Vecteur3D BadScaling3D(Vecteur3D PtToScale, Vecteur3D ief, Vecteur3D VectRatio, float Mvt);
	Vecteur3D Scaling(Vecteur3D PtToScale, Vecteur3D ief, Vecteur3D VectRatio);
	Vecteur3D Scaling(Vecteur3D PtToScale, Vecteur3D ief, float Ratio);
	Coord2D Scale(Coord2D ief, Coord2D PtToScale, float Mvt);
	Vecteur3D Rotation(Vecteur3D Vect, Vecteur3D VectRot, float Angle);
	Vecteur3D RotationWithMax(Vecteur3D Point, Vecteur3D P0_VectRot, Vecteur3D VectRot, float Angle, Vecteur3D VectMax);
	Vecteur3D Rotation(Vecteur3D VectToRotate, Vecteur3D P0_VectRot, Vecteur3D VectRot, float Angle);
	glm::vec3 Rotation(glm::vec3 VectToRotate, glm::vec3 P0_VectRot, glm::vec3 VectRot, float Angle);
	Droite3D Rotation(Droite3D Dr1, Vecteur3D VectRot, float Angle);
	Vecteur3D Rotation(Vecteur3D Point, float P0_X, float P0_Y, float P0_Z, float VR_X, float VR_Y, float VR_Z, float Angle);
	glm::vec3 Rotation(glm::vec3 Vect, glm::vec3 VectRot, float Angle);
	void Translation(Vecteur3D& Point1, Vecteur3D Point2);
	Vecteur3D Translation(Vecteur3D& Point, Vecteur3D PtTrans, Vecteur3D VectTrans, float Distance);
	Vecteur3D Translation(Vecteur3D& Point, Vecteur3D VectTrans, float Distance);
	Vecteur3D Translation(Vecteur3D& Point, float x, float y, float z, float Distance);
	Droite3D CalculerDroite(Vecteur3D Vect);
	Droite3D CalculerDroite(Vecteur3D Pt, Vecteur3D Vect);
	Droite3D CalculerDroite(float x, float y, float z);
	Plan calculerPlan(Droite3D Dr1, Vecteur3D Vect1);
	Plan calculerPlan(Droite3D Dr1, Droite3D Dr2);
	Plan calculerPlan(Vecteur3D Vect1, Vecteur3D Vect2);
	Plan calculerPlan_pt_norm(Vecteur3D Pt1, Vecteur3D VectN);
	Vecteur3D Projection(Vecteur3D Pt, Plan PLAN);
	Droite3D Projection(Droite3D Dr1, Plan PLAN);
	Droite3D CalculerPerp(Droite3D Dr1, Plan PLAN);
	Vecteur3D EcrirePoint(float x, float y, float z);
	Vecteur3D EcrireVector(float x, float y, float z);
	float CalculerYCercle(float PosX, float Ray, bool Up, float XToGive);
	float ReturnLenght(Vecteur3D PtToCalculate);

	void DivVectbyNumber(Vecteur3D& Vect, float Number);
	Vecteur3D Add(Vecteur3D& Point1, Vecteur3D Vect, float Frac);
	Vecteur3D Sous(Vecteur3D& Point1, Vecteur3D Vect, float Frac);
	Vecteur3D MakeVecteur(Vecteur3D Vect1, Vecteur3D Vect2);
	Vecteur3D MakePoint(Vecteur3D Vect);
	Vecteur3D VecteurInverse(Vecteur3D Vect);
	Vecteur3D Div(Vecteur3D Vect, float Number);
	Vecteur3D Multi(Vecteur3D Vect, float Number);
	void MultiVoid(Vecteur3D& Vect, float Number);
	float dot(Vecteur3D Vect1, Vecteur3D Vect2);
	float dot(Vecteur2D Vect1, Vecteur2D Vect2);
	Vecteur3D ProduitVectoriel(Vecteur3D Vect1, Vecteur3D Vect2);
	glm::vec3 ProduitVectoriel(glm::vec3 Vect1, glm::vec3 Vect2);
	Vecteur3D normalize(Vecteur3D& Vect);
	Vecteur2D normalize(Vecteur2D& Vect);
	Vecteur3D normalize(Vecteur3D vPolygon[]);
	bool IsVectorParallel(Vecteur3D Vect1, Vecteur3D Vect2);
	Vecteur3D VectNorm(Vecteur3D Vect);
	Vecteur3D norm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd);
	Vecteur3D CalculateNorm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd);
	Vecteur3D CalculateVectNorm(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd);
	Vecteur3D CalculateVectNorm_WithoutNormalizing(Vecteur3D& ActualNorm, int& CountPt, Vecteur3D NewVectToAdd);

	glm::vec2 Coord3DToScreen2DVect(glm::vec3, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect);
	glm::vec2 Coord3DToScreenFov(glm::vec3 coord, float fov, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect);
	glm::vec2 Coord3DToScreen2DCoord(glm::vec3, float fov, glm::vec3 campos, glm::vec3 target, glm::vec3 rightVect, int windowWidth, int windowHeight);
	//
	//template <typename ptlist>
	//void CalculateVectNorm(Vecteur3D &ActualNorm, int &CountPt, ptlist *PTList)
	//{	
	//	ptlist::iterator it, beg = PTList->begin();
	//	it = beg;
	//
	//	for (int n = 3; n < 0 && it != PTList->end(); --n, ++beg) {}
	//	for (; it != PTList->end(); ++i)
	//	{
	//		it = beg;
	//		CountPt++;
	//		//	ActualNorm = ActualNorm*(CountPt - 1) / CountPt + VectToUse / CountPt
	//		ActualNorm = ActualNorm*(CountPt - 1) / CountPt + normalize(ProduitVectoriel(MakeVecteur(*it, *(++it)), MakeVecteur(*it, *(++it)))) / CountPt;
	//	}
	//	normalize(ActualNorm);
	//	return ActualNorm;
	//}

	Vecteur2D VectNorm(Vecteur2D Vect);
	float GetLength(Vecteur2D Vect);
	float GetLength(Vecteur3D Vect);
	float Distance(Vecteur3D Pt1, Vecteur3D Pt2);
	bool CheckEquals(Vecteur3D Vect1, Vecteur3D Vect2);
	Vecteur3D MakeAverageVector(Vecteur3D Vect1, Vecteur3D Vect2);
	bool IsSideWiseVector(Vecteur3D Vect1, Vecteur3D Vect2);
	bool IsSameSideVector(Vecteur3D Vect1, Vecteur3D Vect2);
	float Absolute(float num);
	Vecteur3D CrossVecteur(Vecteur3D vVector1, Vecteur3D vVector2);
	float Magnitude(Vecteur3D vNormal);
	Vecteur3D ClosestPointOnLine(Vecteur3D vA, Vecteur3D vB, Vecteur3D vPoint);
	float Dot(Vecteur3D vVector1, Vecteur3D vVector2);
	float PlaneDistance(Vecteur3D Normal, Vecteur3D Point);
	bool IntersectedPlane(Vecteur3D vPoly[], Vecteur3D vLine[], Vecteur3D& vNormal, float& originDistance);

	float AngleBetweenVectors(Vecteur3D Vector1, Vecteur3D Vector2);
	Vecteur3D IntersectionPoint(Vecteur3D vNormal, Vecteur3D vLine[], double distance);
	bool InsidePolygon(Vecteur3D vIntersection, Vecteur3D Poly[], long verticeCount);
	bool IntersectedPolygon(Vecteur3D vPoly[], Vecteur3D vLine[], int verticeCount);
	int ClassifySphere(Vecteur3D& vCenter,
		Vecteur3D& vNormal, Vecteur3D& vPoint, float radius, float& distance);
	bool EdgeSphereCollision(Vecteur3D& vCenter,
		Vecteur3D vPolygon[], int vertexCount, float radius);
	bool SpherePolygonCollision(Vecteur3D vPolygon[],
		Vecteur3D& vCenter, int vertexCount, float radius);
	Vecteur3D GetCollisionOffset(Vecteur3D& vNormal, float radius, float distance);


	void computeTriangleNormals(const std::vector<glm::vec3>& vertices,
		const std::vector<unsigned int>& indices,
		std::vector<glm::vec3>& normals);
};



