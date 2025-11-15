#pragma once



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


#include <iostream>
using namespace std;


class SimpleJay
{
public :
	SimpleJay(vector<glm::vec3> newVertices);
	~SimpleJay();

	void Init();
	void UpdateWith(vector<glm::vec3> newvectices);
	void UpdateIDs();
	void Draw();

private:
	GLuint buffer;
	GLuint ArrayID;
	vector<glm::vec3> vectices;

};