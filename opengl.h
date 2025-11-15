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
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "SimpleGL.h"


#include <iostream>
using namespace std;

class ProjetSession
{
public:
	GLuint windowWidth = 1024;
	GLuint windowHeight = 768;

	vector<SimpleGL> isoContoursGL;


	//	Parameters for the grid
	int division = 100;
	int size = 10;
	float increment;


	glm::vec3 up;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint isocontoursbuffer;

	GLuint programID;
	GLuint iso_programID;



	GLuint FramebufferName = 0;

	GLuint programR2T_ID;
	GLuint TextureR2T;
	GLuint TextureR2T_ID;
	GLuint LightID;

	GLuint renderedTexture;
	GLuint depthrenderbuffer;

	vector<GLfloat> g_quad_vertex_buffer_data;

	GLuint quad_vertexbuffer;
	GLuint quad_programID;
	GLuint texID;
	GLuint timeID;

	GLenum DrawBuffers[1];

	std::vector<glm::vec3> verticesR2T;
	std::vector<glm::vec2> uvsR2T;
	std::vector<glm::vec3> normalsR2T;

	bool res;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbufferR2T;
	GLuint uvbufferR2T;
	GLuint normalbufferR2T;
	GLuint elementbufferR2T;

	GLuint VertexArrayR2TID;
	
	// Get a handle for our "MVP" uniform
	GLuint MatrixR2T_ID;
	GLuint ViewMatrixR2T_ID;
	GLuint ModelMatrixR2T_ID;





	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint isoMatrixID;

	// Load the texture
	GLuint Texture;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;

	GLuint VertexArrayID;
	GLuint IsocontourArrayID;

	GLuint iso_colorID;


	float isolineFreeFloat = 0.5f;
	int selectedIsocontour = -1;
	bool isoIsSelected = false;

	CImg<float> _2DTexture;

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	vector<glm::vec3> vectices;
	vector<glm::vec3> isocontours;

	//	Isocontours		//	La gestion de ça va être quelque chose

	vector<float> isoContoursHeights;

	// Two UV coordinatesfor each vertex. They were created with Blender.
	vector<glm::vec2> uvs;
	

	bool gridUpdated = false;
	bool isocontourUpdated = false;

	//	For movement control

	// Initial position : on +Z
	glm::vec3 aim = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

	//	Distance from view
	float distance = 15;

	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = -0.5f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.001f;

	float m_Scale = 0.f;

	//	Info for view
	float isProjectedView = true;

	//	Modes of colormap
	int colormapMod = 0;	//	0 = rainbow
							//	1 = Grayscale
							//	2 = Two-hue
							//	3 = Heat map
							//	4 = Diverging

	float minToClamp;
	float maxToClamp;
	
	bool E_wasnotpressed = true;
	bool Q_wasnotpressed = true;
	bool R_wasnotpressed = true;
	bool X_wasnotpressed = true;
	bool isTogglingBetweenIsoContours = false;

	bool colormapModeReleased = true;
	bool OrthoModReleased = true;
	bool OrthoMod = false;

	GLuint colorMapID;
	GLuint minID;
	GLuint maxID;




public:
	GLFWwindow* window;

	ProjetSession();
	~ProjetSession();

	void ContextInitialisation();
	void ShaderInitialisation();
	void DeclarationOfObjects();
	void ConstructionAndUpdateOfObjects();
	void HighwayToGPU();
	void SetupForDisplay();
	void Display_Loop();
	void CleanUp();

	bool LoopConditions();
	void ComputeMatricesFromInputs();

	float Height(float x, float y);

	vector<glm::vec3> MakeIsoline(float isolineLevel);
};
