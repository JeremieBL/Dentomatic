#ifndef STRUCTURE_H__
#define STRUCTURE_H__

#include <GL/glew.h>
#include <glm/glm.hpp>


/**********************\
 ***** Structures *****
\**********************/

class MouseEvent
{
public:
	int	button;  /* left, middle, right */
	int stateButton; /* pressed or not */
	int	x;
	int	y;
} ;

class CamInfo
{
public:
	GLfloat	theta;	/*  X/Z rotation angle */
	GLfloat	phi;	/*  X/Z elevation angle */
	GLfloat	r;		/* distance to the origin */
	GLfloat fovy;   /* field of view angle */
	GLfloat ratio;  /* height/width angle ratio */
	GLfloat nearCP;   /* near clipping plane */
	GLfloat farCP;    /* far clipping plane */
} ;

class Material
{
public:
	glm::vec4 ambient; 	//ambiant color
	glm::vec4 diffuse;	//diffuse color
	glm::vec4 specular;	//specular color
	GLfloat shininess;	//the exponent 'n' to the cos
} ;

class TextureRGB
{
public:
	unsigned char *texture; //2D RGB image stretch in a 1D buffer
	int XSize; // number of columns
	int YSize; // number of lines
	int ZSize; // number of channels : 3 for color images and 1 for grayscale images
} ;

class Light
{
public:
	glm::vec4	ambient; 	//ambiant component
	glm::vec4	diffuse;	//diffuse component
	glm::vec4	specular;	//specular component
	glm::vec4	position;	//Position

	GLfloat Kc;	//Constant attenuation factor
	GLfloat Kl;	//Linear attenuation factor
	GLfloat Kq;	//Quadratic attenuation factor

	bool	on; // light on or off

};


/**********************\
*******  ENUM  *******
\**********************/

enum
{
	menuPlane,
	menuSphere,
	menuCylinder,
	menuTexture,
	menuLighting,
	menuDisplacement,
	menuBumpmap,
	menuWireframe,
	menuQuit
};


#endif
