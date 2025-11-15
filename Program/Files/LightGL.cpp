#include "LightJay.h"

LightJay::LightJay() {
	// Initialize OpenGL light properties
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}

LightJay::~LightJay()
{

}

void LightJay::Init()
{
	// Initialize OpenGL light properties
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}
// 	// Set the light position
void LightJay::SetPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	//GLfloat position[] = { x, y, z, 1.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
}


// 	// Set the light color
void LightJay::SetColor(float r, float g, float b, float a)
{
	color = glm::vec4(r, g, b, a); // Store color as vec4 for OpenGL compatibility
	//GLfloat color[] = { r, g, b, 1.0f };
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, color);
}
void LightJay::Enable()
{
//	glEnable(GL_LIGHT0);
}
void LightJay::Disable()
{
//	glDisable(GL_LIGHT0);
}


// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

// 	glLightfv(GL_LIGHT0, GL_SPECULAR, color);


void LightJay::SetDirection(float x, float y, float z) {
	dir = glm::vec3(x, y, z);
}
glm::vec3 LightJay::GetDirection() const {
	return dir;
}
glm::vec3 LightJay::GetPosition() const {
	return position;
}
bool LightJay::IsEnabled() const {
	return enabled;
}

glm::vec3 LightJay::GetColor() const {
	return glm::vec3(1.0f, 1.0f, 1.0f); // Default color, can be modified
}
void LightJay::SetEnabled(bool enable) {
	enabled = enable;
	if (enable) {
		//glEnable(GL_LIGHT0);
	}
	else {
		//glDisable(GL_LIGHT0);
	}
}
void LightJay::SetDirectional(bool isDirectional) {
	directional = isDirectional;
	if (isDirectional) {
		//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f); // Directional light
	}
	else {
		//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 0.0f); // Point light
	}
}
bool LightJay::IsDirectional() const {
	return directional;
}
