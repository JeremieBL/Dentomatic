#pragma once



#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2


#include <iostream>
#include <fstream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Vecteur2D
{
public:
	float x, y;

	Vecteur2D(void);
	~Vecteur2D(void);
	Vecteur2D& _regulate();
	void getVector(float X, float Y);
	void getVector(Vecteur2D Vect);
	void Transcription(fstream* Fic, bool ToDisk);
	void Transcription(ifstream* FicIn);
	void Transcription(ofstream* FicOut);
};


class Vecteur3D
{
public:
	float x, y, z;

private :
	bool isNormalized = false;
public:
	//	Vecteur3D(float newx = 0.0, float newy = 0.0, float newz = 0.0) : x(newx), y(newy), z(newz) {};
	Vecteur3D();
	Vecteur3D(float);
	Vecteur3D(float X, float Y, float Z);
	Vecteur3D(glm::vec3);
	~Vecteur3D();

	glm::vec3 glm();
	void getVector(Vecteur3D Vect);
	void getVector(float X, float Y, float Z);
	void getVector(Vecteur3D Pt1, Vecteur3D Pt2);
	//void SayPoint() { glVertex3f(x, y, z); };
	//void SayPoint(Vecteur3D PointCenter);
	//void SayNormal() { glNormal3f(x, y, z); };
	//void TranslateTo() {glTranslatef(x, y, z);};

	Vecteur3D abs();
	float Average();
	float _regulate(float& x);
	Vecteur3D _regulate(Vecteur3D& Coord);
	Vecteur3D& Regulate();
	//Vecteur3D _regulate();
	Vecteur3D normalize();
	//Vecteur3D _regulateVect3D(Vecteur3D& Coord);
	//Vecteur2D _regulateVect2D(Vecteur2D& Coord);
	//Coord2D _regulateCoord2D(Coord2D& Coord);
	Vecteur3D operator=(float a);
	Vecteur3D operator=(Vecteur3D a);

	// Here we overload the + operator so we can add vectors together 
	Vecteur3D operator+(Vecteur3D vVector);

	// Here we overload the - operator so we can subtract vectors 
	Vecteur3D operator-(Vecteur3D vVector);

	// Here we overload the * operator so we can multiply by scalars
	Vecteur3D operator*(float num);

	Vecteur3D operator*=(float num);
	Vecteur3D operator/=(float num);
	Vecteur3D operator-=(Vecteur3D vVector);
	Vecteur3D operator+=(Vecteur3D vVector);

	// Here we overload the / operator so we can divide by a scalar
	Vecteur3D operator/(float num);

	Vecteur3D operator/(Vecteur3D Vect);
	Vecteur3D operator*(Vecteur3D Vect);
	bool operator==(Vecteur3D Vect);
	bool operator!=(Vecteur3D Vect);
	bool operator==(float Num);
	bool operator!=(float Num);
	Vecteur3D VecteurInverse();
	bool operator/=(Vecteur3D Vect);
	void Transcription(fstream* Fic, bool ToDisk);
	void Transcription(ifstream* FicIn);
	void Transcription(ofstream* FicOut);

	void _cout();
};





class Matrice3D
{
public:
	Vecteur3D Vect1, Vect2, Vect3;

	Matrice3D() {};
	~Matrice3D() {};

	void _cout();
	void getVectors(Vecteur3D Vect_1, Vecteur3D Vect_2, Vecteur3D Vect_3);
	void NewMatr(float Vect1X, float Vect1Y, float Vect1Z, float Vect2X, float Vect2Y, float Vect2Z, float Vect3X, float Vect3Y, float Vect3Z);

};


//Plane structure
struct PlaneDyn {
	Vecteur3D _Position;
	Vecteur3D _Normal;
};
//Cylinder structure
struct CylinderDyn {
	Vecteur3D _Position;
	Vecteur3D _Axis;
	double _Radius;
};
//Explosion structure
struct ExplosionDyn {
	Vecteur3D _Position;
	float   _Alpha;
	float   _Scale;
};


