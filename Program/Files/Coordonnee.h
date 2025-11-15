#pragma once

#include <fstream>
using namespace std;

class Coord2D
{
public:	
	float x, y;

	Coord2D(float newx = 0.0, float newy = 0.0): x(newx), y(newy) {};
	~Coord2D() {};

	void getVector(float X, float Y);
	void Transcription(fstream *Fic, bool ToDisk);
	void Transcription(ifstream *FicIn);
	void Transcription(ofstream *FicOut);
	void Erase();
	
	void Getx(float Newx);
	void Gety(float Newy);

	void SayTexture() {};
	void Regulate();


	bool operator==(Coord2D CoordToCompage);
	bool operator!=(Coord2D CoordToCompage);

};

class Coord2Ds
{
public:
	int x, y;

	Coord2Ds();
	~Coord2Ds();

	void Transcription(fstream *Fic, bool ToDisk);
	void Transcription(ifstream *FicIn);
	void Transcription(ofstream *FicOut);

	void getVector(float X, float Y);
	void Erase();
//	void Regulate(){ _regulate(x); _regulate(y); };


	void Getx(float Newx) {x = Newx;};
	void Gety(float Newy) {y = Newy;};

	bool operator==(Coord2Ds CoordToCompage)
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
	}	
	bool operator!=(Coord2Ds CoordToCompage)
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
	}

};


