

#include "JaySpace.h"
#include "Vecteur.h"

#include <fstream>
using namespace std;
#include <iostream>



Vecteur2D& Vecteur2D::_regulate()
{
	JaySpace::_regulate(x);
	JaySpace::_regulate(y);
	return *this;
};



void Vecteur2D::getVector(float X, float Y)
{
	x = X;
	y = Y;
	_regulate();
};

void Vecteur2D::getVector(Vecteur2D Vect) 
{
	x = Vect.x;
	y = Vect.y;
	_regulate();
};

void Vecteur2D::Transcription(fstream* Fic, bool ToDisk)
{
	if (ToDisk)
	{
		Fic->write((char*)&x, sizeof(x));
		Fic->write((char*)&y, sizeof(y));
	}
	else
	{
		Fic->read((char*)&x, sizeof(x));
		Fic->read((char*)&y, sizeof(y));
	}
};
void Vecteur2D::Transcription(ifstream* FicIn)
{
	FicIn->read((char*)&x, sizeof(x));
	FicIn->read((char*)&y, sizeof(y));
};
void Vecteur2D::Transcription(ofstream* FicOut)
{
	FicOut->write((char*)&x, sizeof(x));
	FicOut->write((char*)&y, sizeof(y));
};

Vecteur2D::Vecteur2D()
{
	getVector(0, 0);
}

Vecteur2D::~Vecteur2D()
{
	getVector(0, 0);
}






Vecteur3D Vecteur3D::abs()
{
	x = std::abs(x);
	y = std::abs(y);
	z = std::abs(z);
	isNormalized = false;
	return *this;
};


float Vecteur3D::Average()
{
	return((x + y + z) / 3.0);
}


float Vecteur3D::_regulate(float& x)
{
	JaySpace::_regulate(x);

	return x;
};

//Vecteur3D _regulateVect3D(Vecteur3D& Coord)
//{
//	_regulate(Coord.x);
//	_regulate(Coord.y);
//	_regulate(Coord.z);

//	return Coord;
//};
//Vecteur2D _regulateVect2D(Vecteur2D& Coord)
//{
//	_regulate(Coord.x);
//	_regulate(Coord.y);

//	return Coord;
//};

//Coord2D _regulateCoord2D(Coord2D& Coord)
//{
//	_regulate(Coord.x);
//	_regulate(Coord.y);

//	return Coord;
//};

Vecteur3D::Vecteur3D()
{
};

//	Vecteur3D(float newx = 0.0, float newy = 0.0, float newz = 0.0) : x(newx), y(newy), z(newz) {};
Vecteur3D::Vecteur3D(float var = 0.0) : x(var), y(var), z(var)
{
	isNormalized = false;
	Regulate();
};
Vecteur3D::Vecteur3D(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
	isNormalized = false;
	Regulate();
};
Vecteur3D::Vecteur3D(glm::vec3 NewVect) : x(NewVect.x), y(NewVect.y), z(NewVect.z)
{
	isNormalized = false;
	Regulate();
};
Vecteur3D::~Vecteur3D()
{
	isNormalized = false;
	getVector(0, 0, 0); 
};

Vecteur3D& Vecteur3D::Regulate() 
{
	_regulate(x);
	_regulate(y);
	_regulate(z);

	return *this;
};


Vecteur3D Vecteur3D::_regulate(Vecteur3D& Coord)
{
	_regulate(Coord.x);
	_regulate(Coord.y);
	_regulate(Coord.z);

	return Coord;
};


Vecteur3D Vecteur3D::normalize(void)
{
	float length = sqrt(x * x + y * y + z * z);

	x /= length;
	y /= length;
	z /= length;

	Regulate();

	isNormalized = true;

	return *this;
}
bool Vecteur3D::operator/=(Vecteur3D Vect)
{
	//	renvoi true si les 2 sont parall�les, sans les modifier.
	Vecteur3D This(*this);
	This.normalize();

	Vecteur3D Vect2check(Vect);
	Vect2check.normalize();

	return (This == Vect2check || This.VecteurInverse() == Vect2check);
};


glm::vec3 Vecteur3D::glm()
{
	return glm::vec3(x, y, z);
};

void Vecteur3D::getVector(Vecteur3D Vect)
{
	x = Vect.x;
	y = Vect.y;
	z = Vect.z;
	isNormalized = false;
	Regulate();
};
void Vecteur3D::getVector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	isNormalized = false;
	Regulate();
};
void Vecteur3D::getVector(Vecteur3D Pt1, Vecteur3D Pt2)
{
	x = Pt2.x - Pt1.x;
	y = Pt2.y - Pt1.y;
	z = Pt2.z - Pt1.z;
	isNormalized = false;
	Regulate();
};


Vecteur3D Vecteur3D::operator=(float a)
{
	x = y = z = _regulate(a);
	isNormalized = false;
	return *this;
}

Vecteur3D Vecteur3D::operator=(Vecteur3D a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	Regulate();
	isNormalized = false;
	return *this;
}

// Here we overload the + operator so we can add vectors together 
Vecteur3D Vecteur3D::operator+(Vecteur3D vVector)
{
	vVector.Regulate();

	// Return the added vectors result.
	return Vecteur3D(vVector.x + x, vVector.y + y, vVector.z + z);
}

// Here we overload the - operator so we can subtract vectors 
Vecteur3D Vecteur3D::operator-(Vecteur3D vVector)
{
	vVector.Regulate();
	// Return the subtracted vectors result
	return Vecteur3D(x - vVector.x, y - vVector.y, z - vVector.z);
}

// Here we overload the * operator so we can multiply by scalars
Vecteur3D Vecteur3D::operator*(float num)
{
	_regulate(num);
	// Return the scaled vector
	return Vecteur3D(x * num, y * num, z * num);
}
Vecteur3D Vecteur3D::operator*=(float num)
{
	_regulate(num);
	// Return the scaled vector
	x = x * num;
	y = y * num;
	z = z * num;
	isNormalized = false;
	return *this;
}
Vecteur3D Vecteur3D::operator/=(float num)
{
	_regulate(num);
	// Return the scaled vector
	x = x / num;
	y = y / num;
	z = z / num;
	isNormalized = false;
	return *this;
}

Vecteur3D Vecteur3D::operator-=(Vecteur3D vVector)
{
	vVector.Regulate();
	x -= vVector.x;
	y -= vVector.y;
	z -= vVector.z;
	isNormalized = false;
	return *this;
}
Vecteur3D Vecteur3D::operator+=(Vecteur3D vVector)
{
	//	vVector.Regulate();
	x += vVector.x;
	y += vVector.y;
	z += vVector.z;
	isNormalized = false;
	return *this;
}


// Here we overload the / operator so we can divide by a scalar
Vecteur3D Vecteur3D::operator/(float num)
{
	_regulate(num);
	// Return the scale vector
	return Vecteur3D(x / num, y / num, z / num);
}

Vecteur3D Vecteur3D::operator/(Vecteur3D Vect)
{
	_regulate(Vect);
	// Return the scale vector
	return Vecteur3D(x / Vect.x, y / Vect.y, z / Vect.z);
}

Vecteur3D Vecteur3D::operator*(Vecteur3D Vect)
{
	//	Retourne un produit vectoriel
	return Vecteur3D(y * Vect.z - z * Vect.y, z * Vect.x - x * Vect.z, x * Vect.y - y * Vect.x);
}

bool Vecteur3D::operator==(Vecteur3D Vect)
{
	Vect.Regulate();
	return(Vect.x == x && Vect.y == y && Vect.z == z);
}

bool Vecteur3D::operator!=(Vecteur3D Vect)
{
	return(Vect.x != x || Vect.y != y || Vect.z != z);
}

bool Vecteur3D::operator==(float Num)
{
	_regulate(Num);
	return(x == Num && y == Num && z == Num);
}

bool Vecteur3D::operator!=(float Num)
{
	_regulate(Num);
	return(x != Num || y != Num || z != Num);
}

Vecteur3D Vecteur3D::VecteurInverse()
{
	return(Vecteur3D(-x, -y, -z));
};

void Vecteur3D::Transcription(fstream* Fic, bool ToDisk)
{
	if (ToDisk)
	{
		Fic->write((char*)&x, sizeof(x));
		Fic->write((char*)&y, sizeof(y));
		Fic->write((char*)&z, sizeof(z));
	}
	else
	{
		Fic->read((char*)&x, sizeof(x));
		Fic->read((char*)&y, sizeof(y));
		Fic->read((char*)&z, sizeof(z));
	}
};
void Vecteur3D::Transcription(ifstream* FicIn)
{
	FicIn->read((char*)&x, sizeof(x));
	FicIn->read((char*)&y, sizeof(y));
	FicIn->read((char*)&z, sizeof(z));
};
void Vecteur3D::Transcription(ofstream* FicOut)
{
	FicOut->write((char*)&x, sizeof(x));
	FicOut->write((char*)&y, sizeof(y));
	FicOut->write((char*)&z, sizeof(z));
};

void Vecteur3D::_cout()
{
	cout << "x : " << x << " \ty : " << y << " \t z : " << z << endl;
}




//
//Matrice3D::Matrice3D()
//{
//}
//
//Matrice3D::~Matrice3D()
//{
//}
void Matrice3D::_cout()
{
	cout << "Vect1.x\t" << Vect1.x << " Vect2.x\t" << Vect2.x << " Vect3.x\t" << Vect3.x << endl;
	cout << "Vect1.y\t" << Vect1.y << " Vect2.y\t" << Vect2.y << " Vect3.y\t" << Vect3.y << endl;
	cout << "Vect1.z\t" << Vect1.z << " Vect2.z\t" << Vect2.z << " Vect3.z\t" << Vect3.z << endl;
};


void Matrice3D::getVectors(Vecteur3D Vect_1, Vecteur3D Vect_2, Vecteur3D Vect_3)
{
	Vect1 = Vect_1;
	Vect2 = Vect_2;
	Vect3 = Vect_3;
};

void Matrice3D::NewMatr(float Vect1X, float Vect1Y, float Vect1Z, float Vect2X, float Vect2Y, float Vect2Z, float Vect3X, float Vect3Y, float Vect3Z)
{
	Vect1.getVector(Vect1X, Vect1Y, Vect1Z);
	Vect2.getVector(Vect2X, Vect2Y, Vect2Z);
	Vect3.getVector(Vect3X, Vect3Y, Vect3Z);
};



// This returns the absolute value of "num"
float Absolute(float num);

//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
Vecteur3D Cross(Vecteur3D vVector1, Vecteur3D vVector2);

//	This returns the magnitude of a normal (or any other vector)
float Magnitude(Vecteur3D vNormal);

//	This returns a normalize vector (A vector exactly of length 1)
//Vecteur3D normalize(Vecteur3D vNormal);

//	This returns the normal of a polygon (The direction the polygon is facing)
Vecteur3D normalize(Vecteur3D vPolygon[]);

// This returns the distance between 2 3D points
float Distance(Vecteur3D vPoint1, Vecteur3D vPoint2);

// This returns the point on the line segment vA_vB that is closest to point vPoint
Vecteur3D ClosestPointOnLine(Vecteur3D vA, Vecteur3D vB, Vecteur3D vPoint);

// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(Vecteur3D Normal, Vecteur3D Point);

// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(Vecteur3D vPoly[], Vecteur3D vLine[], Vecteur3D& vNormal, float& originDistance);

// This returns the dot product between 2 vectors
float Dot(Vecteur3D vVector1, Vecteur3D vVector2);

// This returns the angle between 2 vectors
float AngleBetweenVectors(Vecteur3D Vector1, Vecteur3D Vector2);

// This returns an intersection point of a polygon and a line (assuming intersects the plane)
Vecteur3D IntersectionPoint(Vecteur3D vNormal, Vecteur3D vLine[], double distance);

// This returns true if the intersection point is inside of the polygon
bool InsidePolygon(Vecteur3D vIntersection, Vecteur3D Poly[], long verticeCount);

// Use this function to test collision between a line and polygon
bool IntersectedPolygon(Vecteur3D vPoly[], Vecteur3D vLine[], int verticeCount);

// This function classifies a sphere according to a plane. (BEHIND, in FRONT, or INTERSECTS)
int ClassifySphere(Vecteur3D& vCenter, Vecteur3D& vNormal, Vecteur3D& vPoint, float radius, float& distance);

// This takes in the sphere center, radius, polygon vertices and vertex count.
// This function is only called if the intersection point failed.  The sphere
// could still possibly be intersecting the polygon, but on it's edges.
bool EdgeSphereCollision(Vecteur3D& vCenter,
	Vecteur3D vPolygon[], int vertexCount, float radius);

// This returns true if the sphere is intersecting with the polygon.
bool SpherePolygonCollision(Vecteur3D vPolygon[],
	Vecteur3D& vCenter, int vertexCount, float radius);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

// This returns the offset the sphere needs to move in order to not intersect the plane
Vecteur3D GetCollisionOffset(Vecteur3D& vNormal, float radius, float distance);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


Vecteur3D Souss(Vecteur3D Pt1, Vecteur3D Pt2)
{
	return(Pt1 - Pt2);
}
Vecteur3D Adds(Vecteur3D Pt1, Vecteur3D Pt2)
{
	return(Pt1 + Pt2);
}



void ShowCross(Vecteur3D PointToCall)
{
	//glLineWidth(2);
	//glPushMatrix();
	//glTranslatef(PointToCall.x, PointToCall.y, PointToCall.z);
	//glBegin(GL_LINES);

	////SayPoint(0.125, 0, 0);
	////SayPoint(-0.125, 0, 0);
	////SayPoint(0, 0.125, 0);
	////SayPoint(0, -0.125, 0);
	////SayPoint(0, 0, 0.125);
	////SayPoint(0, 0, -0.125);

	//glEnd();

	//glPopMatrix();
}