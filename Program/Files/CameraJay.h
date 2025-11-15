#pragma once

//#include "GraphicCard.h"


//	#include "Shader.h"
#include "structures.h"

#include <vector>

using namespace std;

class CameraJay {
public:
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	glm::mat4 MVP;

	CameraJay();
	~CameraJay();

	void Update(glm::mat4 newProjectionMatrix, glm::mat4 newViewMatrix);

public:

};
