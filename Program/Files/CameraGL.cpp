// Include standard headers


#include "CameraJay.h"

CameraJay::CameraJay() {

};


CameraJay::~CameraJay() {

};

void CameraJay::Update(glm::mat4 newProjectionMatrix, glm::mat4 newViewMatrix)
{
	ProjectionMatrix = newProjectionMatrix;
	ViewMatrix = newViewMatrix;
}
