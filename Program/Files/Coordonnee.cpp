

#include "Coordonnee.h"
#include "JaySpace.h"
#include "Global.h"


void Coord2D::Erase()
{
	x = 0;
	y = 0;
};

void Coord2D::getVector(float X, float Y)
{ 
	x = X; 
	y = Y;
	Regulate();
};


void Coord2D::Getx(float Newx)
{
	x = Newx;
};
void Coord2D::Gety(float Newy)
{
	y = Newy;
};
void Coord2D::Regulate()
{
	JaySpace::_regulate(x);
	JaySpace::_regulate(y);
};

bool Coord2D::operator==(Coord2D CoordToCompage)
{
	// Return the scaled vector
	if (CoordToCompage.x == x && CoordToCompage.y == y)
	{
		return(true);
	}
	else
	{
		return(false);
	}
};

bool Coord2D::operator!=(Coord2D CoordToCompage)
{
	// Return the scaled vector
	if (CoordToCompage.x != x || CoordToCompage.y != y)
	{
		return(true);
	}
	else
	{
		return(false);
	}
};


void Coord2D::Transcription(fstream *Fic, bool ToDisk)
{
	if(ToDisk)
	{
		int TypeClass;
		Global::AskCodeName(TypeClass);
		Fic->write((char *) &TypeClass, sizeof(TypeClass));
	}
	else
	{
		int TypeClass = 0;
		Fic->read((char *) &TypeClass, sizeof(TypeClass));
	}
	
	if(ToDisk)
	{
		Fic->write((char *) &x, sizeof(x));
	}
	else
	{
		Fic->read((char *) &x, sizeof(x));
	}
	
	if(ToDisk)
	{
		Fic->write((char *) &y, sizeof(y));
	}
	else
	{
		Fic->read((char *) &y, sizeof(y));
	}
	
}

void Coord2D::Transcription(ifstream *FicIn)
{
	int TypeClass;
	FicIn->read((char *) &TypeClass, sizeof(TypeClass));
	
	FicIn->read((char *) &x, sizeof(x));
	
	FicIn->read((char *) &y, sizeof(y));
	
}

void Coord2D::Transcription(ofstream *FicOut)
{
	int TypeClass;
	Global::AskCodeName(TypeClass);
	FicOut->write((char *) &TypeClass, sizeof(TypeClass));
	
	FicOut->write((char *) &x, sizeof(x));
	
	FicOut->write((char *) &y, sizeof(y));
	
}





Coord2Ds::Coord2Ds()
{
	getVector(0, 0);
}

Coord2Ds::~Coord2Ds()
{
	getVector(0, 0);
}

void Coord2Ds::Erase()
{
	x = 0;
	y = 0;
	
}


void Coord2Ds::getVector(float X, float Y)
{
	JaySpace::_regulate(X);
	JaySpace::_regulate(Y);
	x = X;
	y = Y;
};



void Coord2Ds::Transcription(fstream *Fic, bool ToDisk)
{
	if(ToDisk)
	{
		int TypeClass;
		Global::AskCodeName(TypeClass);
		Fic->write((char *) &TypeClass, sizeof(TypeClass));
	}
	else
	{
		int TypeClass = 0;
		Fic->read((char *) &TypeClass, sizeof(TypeClass));
	}
	
	if(ToDisk)
	{
		Fic->write((char *) &x, sizeof(x));
	}
	else
	{
		Fic->read((char *) &x, sizeof(x));
	}
	
	if(ToDisk)
	{
		Fic->write((char *) &y, sizeof(y));
	}
	else
	{
		Fic->read((char *) &y, sizeof(y));
	}
	
}

void Coord2Ds::Transcription(ifstream *FicIn)
{
	int TypeClass;
	FicIn->read((char *) &TypeClass, sizeof(TypeClass));
	
	FicIn->read((char *) &x, sizeof(x));
	
	FicIn->read((char *) &y, sizeof(y));
	
}

void Coord2Ds::Transcription(ofstream *FicOut)
{
	int TypeClass;
	Global::AskCodeName(TypeClass);
	FicOut->write((char *) &TypeClass, sizeof(TypeClass));
	
	FicOut->write((char *) &x, sizeof(x));
	
	FicOut->write((char *) &y, sizeof(y));
	
}



//
//void SayPoint(Vecteur3D PointToCall)
//{
//	//	glVertex3f(PointToCall.x, PointToCall.y, PointToCall.z);
//}
//
//
//
//Coord3D Coord3D::operator+(Vecteur3D vVector)
//{
//	 Return the added vectors result.
//	return Coord3D(vVector.x + x, vVector.y + y, vVector.z + z);
//}
//Coord3D Coord3D::operator-(Vecteur3D vVector)
//{
//	return Coord3D(x - vVector.x, y - vVector.y, z - vVector.z);
//}
//Coord3D Coord3D::operator=(Vecteur3D vVector)
//{
//	return Coord3D(vVector.x, vVector.y, vVector.z);
//}
//Coord3D Coord3D::operator+=(Vecteur3D vVector)
//{
//	return Coord3D(x+=vVector.x, y+=vVector.y, z+=vVector.z);
//}
//Coord3D Coord3D::operator-=(Vecteur3D vVector)
//{
//	return Coord3D(x-=vVector.x, y-=vVector.y, z-=vVector.z);
//}
//
//
//
