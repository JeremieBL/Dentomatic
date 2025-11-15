#pragma once
/*****************************************\
 MultipleJays.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 31 mars 2021
\*****************************************/




// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>

#include "JayObjet.h"
#include "CameraJay.h"


#include <iostream>
using namespace std;


class MultipleJays
{
public :
	MultipleJays();
	MultipleJays(string);
	MultipleJays(vector<glm::vec3>, string);
	MultipleJays(vector<glm::vec3>, string, string);
	~MultipleJays();

	void Init(string, GLuint);
	void Init(string , string , GLuint);
	void UpdateWith(vector<glm::vec3>);
	void PushBackVectices(glm::vec3);
	void UpdatePositions(vector<glm::vec3>);
	int PushBackPoints(glm::vec3);
	int ErasePoints();
	void EraseVertices();
	void UpdateVecticesIDs();
	void Draw();	//	Draw the particular partern of vertex
	void Display(CameraJay& camera);	//	Call all the openGL functions to illustrate the multiples vertices inside a 

	int Size();
public:


	vector<glm::vec3> BuildCircle(float, int);
	vector<glm::vec3> BuildEdge(float, float, int);
	vector<glm::vec3> BuildCross(float, int);

	vector<glm::vec3> BuildCube(float);
	vector<glm::vec3> BuildSphere(float, int);
	vector<glm::vec3> BuildSquaredSphere(float, int);
	
private :

	void CleanUp();

	//	Informations on shader
	GLuint programID;
	GLuint coloID;

	GLuint MVPMatrixID;

	glm::mat4 ModelMatrix;
	// Get a handle for our "MVP" uniform

	GLuint buffer;
	GLuint ArrayID;
	GLuint gl_type = GL_TRIANGLES;
	vector<glm::vec3> vertices;
	vector<glm::vec3> positions;

	vector<vector<glm::vec3>> attributes;		//	Va �ventuellement remplacer les vertices/normal/autres sp�cificit� pour les �l�ments qui repr�sentent un objet

};