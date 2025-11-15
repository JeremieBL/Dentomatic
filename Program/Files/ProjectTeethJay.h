#pragma once


// Include GLEW
#include <GL/glew.h>
#include <GL/gl.h>

// Include GLFW
#include <GLFW/glfw3.h>

//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>

//#include <zip_file.hpp>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//// In your header or source
////#define MINIZ_NO_STDIO  // If you don't want file I/O in miniz (we'll use memory)
////	#include "miniz.h"  // Your path to miniz.h

#include <fstream>
#include <filesystem>
#include <sstream>
#include <cstdlib>  // For getenv
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <numeric>
#include <cstddef>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "SimpleJay.h"
#include "CameraJay.h"
#include "LightJay.h"
#include "MultipleJays.h"
#include "ViewerJay.h"
#include "SurfaceBezier.h"
#include "KeyControl.h"
#include "JaySpace.h"
#include "StlLoader.h"
#include "emlist.h"
#include "Environnement.h"
#include "Selector.h"

#include "../Eigen/Dense"

#define cimg_display 0

#include "../CImg.h"

using namespace Eigen;
using namespace cimg_library;
using namespace std;

#include "common/text2D.hpp"
#include <list>
#include <chrono>
#include <ctime> 



enum TypeNavigation {
	TN_basic,
	TN_selecting,
	TN_editing,
	TN_painting,
	TN_playmode,
	TN_automatic
};

enum class TypeFunction {
	TF_Neutral = 0,
	TF_SelectObject = 1,
	TF_SelectFace = 2,
	TF_SelectPoint = 3,
	TF_Translate = 4,
	TF_Rotate = 5,
	TF_Scale = 6,
	TF_Paint = 7,
	TF_PlayMode = 8,
	TF_Automatic = 9,
	TF_Exit = 10,
	TF_SpecifierPapilleHaut = 11,
	TF_SpecifierCreteHaut = 12,
	TF_SpecifierCentreBas = 13,
	TF_SpecifierCreteBas = 14,
	TF_ContourCrete = 15,
	TF_EpaisseurLiner = 16,
	TF_EpaisseurBoudin = 17,
	TF_EpaisseurGencive = 18,
	TF_CreerReperes = 19,
	TF_LancerReperes = 20,
	TF_Cachee = 21,
	TF_FonctionOpposee = 22,
	TF_NavCenterOnSelected = 23,
	TF_NavCenterOnAll = 24,
	TF_CleanLineOfCreation = 25
};
//#define _KeyConfig_Up					0
//#define _KeyConfig_Down					1
//#define _KeyConfig_Right				2
//#define _KeyConfig_Left					3
//#define _KeyConfig_ChangeGridUpper		4
//#define _KeyConfig_ChangeGridLower		5
//#define _KeyConfig_ChangeColorMap		6
//#define _KeyConfig_ChangeOrthoMod		7
//#define _KeyConfig_LeftControl			8
//#define _KeyConfig_LeftShift			9
//#define _KeyConfig_Space				10
//#define _KeyConfig_Exit					11
//#define _KeyConfig_NavRotateTarget		12
//#define _KeyConfig_NavRotateCamera		13
//#define _KeyConfig_Etire				14
//#define _KeyConfig_Rotation				15
//#define _KeyConfig_Translation			16
//#define _KeyConfig_SpecifierPapilleHaut	17
//#define _KeyConfig_SpecifierCreteHaut	18
//#define _KeyConfig_SpecifierCentreBas	19
//#define _KeyConfig_SpecifierCretesBas	20
//#define _KeyConfig_ContourCrete			21
//#define _KeyConfig_EpaisseurLiner		22
//#define _KeyConfig_EpaisseurBoudin		23
//#define _KeyConfig_EpaiseureGencive		24
//#define _KeyConfig_CreerReperes			25
//#define _KeyConfig_LancerReperes		26
//#define _KeyConfig_Cachee				27
//#define _KeyConfig_FonctionOpposee		28
//#define _KeyConfig_NavCenterOnSelected	29
//#define _KeyConfig_NavCenterOnAll		30

//	Blender ont différentes façon d'approcher l'édition des objects, comme option de 3Dcursor, translation, rotation, scale...mais ça charge le programme
//	inutilement et ça mêle un peut quand on accroche des hotkey dont ont ne savait pas l'existence.

//	Donc quand on ne fait rien, les mouvements de la sourie bougent en 3D, non pe pas. Pe que pour faire ça, il faudrait cliquer 2x sur le bouton droit.
//	Quand on utiliser une sorte d'édition, ça change la manière dont on se déplace.

//	Ex: en mode object edition [point par point...ce que j'aimerais ne jamais avoir à dealer avec], on peut sélectionner les points, mais pour bouger,
//	Il faut maintenir le clic droit.

//	Si on fait un clic droit sans bouger, alors là ça ouvre des options.
//	On va faire le logiciel comme si on pouvait l'éditer avec un écran touch screen seulement. Donc de grandes icones et peu d'option.
//	Faut vrm que je trouve un module speach-to-text pour ne pas avoir à utilier de clavier du tout.

//	Donc en premier, détecter les clics de sourie et appeler des fonctions.


struct SimplifiedMesh {
	std::vector<glm::vec3> vertices;
	std::vector<unsigned short> indices;
};


// Hash function for glm::vec3 to use in unordered_map
struct Vec3Hash {
	size_t operator()(const glm::vec3& v) const {
		return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z);
	}
};

// Equality comparison for glm::vec3 with epsilon
struct Vec3Equal {
	float epsilon;
	Vec3Equal(float eps) : epsilon(eps) {}

	bool operator()(const glm::vec3& a, const glm::vec3& b) const {
		return glm::distance(a, b) < epsilon;
	}
};

class ProjectTeethJay
{
public :
	ProjectTeethJay();
	~ProjectTeethJay();

private:
	TypeNavigation tempoldnav, mTypeNav = TN_basic;

public:
	GLFWwindow* window;

	void InitiateBindingFunction();
	TypeNavigation getTypeNav();
	void setTypeNav(TypeNavigation);
	void CheckInforFromOpenGL();

	void ContextInitialisation();
	void ShaderInitialisation();
	void BuildTools();
	void BuildGrid();
	emlist<JayObjet>::iterator AddTool(JayObjet newObject);
	vector<glm::vec3> pointerPoints;

	void BuildPointer();
	void UpdatePointer(glm::vec3 newCoord);
	void ConstructionAndUpdate();
	void HighwayToGPU();
	bool SetupForDisplay();
	void Display_Loop();
	void DisplayObjet();
	void DisplayObjectAsSelected(emlist<JayObjet>::iterator itObj, glm::vec3 color2use);
	void DisplayTools();

	void CleanUp();

	GLuint pickingShader;
	int selectedId;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;


	bool LoopConditions();
	bool ComputeMatricesFromInputs();
	void GatherInputs();
	void RegulateInputs();

	void ChangeTypeNavTo(TypeNavigation);
	void MoveCamToSeletingObject_KeepParallelism();
	bool CheckOnKeyFunction(GLint keyfunction2Check, std::function<void()> func2Launch);

	float Height(float x, float y);

	vector<glm::vec3> MakeCurveSurface();

	glm::vec2 SetNewScreenPos(glm::vec2);

	//	Ok, les prochaines déclarations sont pour la construction physique des scenes avec les objects, shader, caméra dans l'environnement.

	emlist<Environnement> environnementList;
	emlist<Environnement>::iterator itEnv;

	ShaderJay* ptrShad;

	unordered_map<string, ShaderJay>::iterator CreateNewShader(string, const char*, const char*);
	GLint NewUniformTexture(string, const char*, GLint);
	unordered_map<string, ShaderJay>::iterator AddThisPrePassToThisShader(const char*, const char*, const char*, const char*);
	GLint OutputShaderToNewTexture(const char* shaderName);

	void EmptySelector();
	void FreeAllShaders();
//	Camera camera;

//	MultipleJays nuagePoints;
//	MultipleJays arretes;


	vector<SimpleJay> isoContoursGL;


	//	Ouain, c'était pas vm compliqué les déclarations. Là y faudra penser à les construire et faire des fonctions de construction.


private:
	//	Variables for the drag n drop functions
	const char* pathforallfolders = "C:/Users/jerem/Desktop/Clinique/Lab";

	//	The following are variables used to find the cursor's 3D position.
	glm::vec2 screenDim;
	glm::vec2 screenDimHalf;
	glm::vec2 coordScalar;
	float distLength;
	float xFoV;

	glm::vec3 clickdir;
	float ratiox;
	float ratioy;

	//	Agles here are in degrees
	float angley;
	float anglex;
	glm::vec3 ptaimOnPlan;

	//////////////	End of variables for cursor's position

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction;
	glm::vec3 rightvect;
	glm::vec3 forwardVect;

	glm::vec3 camerapos;
	glm::vec3 cameraposPerspective;
	glm::vec3 target;
	glm::vec3 dir;
	glm::vec3 vert;
	glm::vec3 camvert;

	glm::vec3 up;

	SurfaceBezier mbezier;

	glm::vec2 mScreenCoord;
	glm::vec2 mdiffCoord;
	double xpos, ypos;
	glm::vec2 Pos;

	GLuint windowWidth = 1024;
	GLuint windowHeight = 768;

	//	Parameters for the grid
	int division = 100;
	int size = 10;
	float increment;

	glm::mat4 MVP;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

	TypeFunction typeOfFunctionSelected = TypeFunction::TF_Neutral;
	emlist<glm::vec3> lineOfCreation;


	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint isocontoursbuffer;

	GLuint programID;
	GLuint iso_programID;
	glm::vec3 isoColor = glm::vec3(1.0f, 0.5f, 0.5f);
		
	GLuint FramebufferName = 0;

	glm::vec3 lightPos = glm::vec3(4, 4, 4);
	glm::vec3 lightdir = glm::vec3(-1,-1,-3);
	glm::vec3 lightCol = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 toothCol = glm::vec3(0.95, 0.78, 0.78);
	float lightIntensity = 10.0f;
	glm::vec3 subsurfaceColor = glm::vec3(0.8, 0.2, 0.2);
	float shaddensity = 10.0f;
	glm::vec2 screenSize = glm::vec2(windowWidth, windowHeight);
	
	float outlineThickness = 1.05f;
	glm::vec3 outlineColor = glm::vec3(0.95f, 0.52f, 0.0f); // Tangerine outline color
	glm::vec3 outlineMouseOverColor = glm::vec3(0.975f, 0.75f, 0.52f); // Lighter tangerine outline color

	glm::vec3 objectBasicColor = glm::vec3(0.95f, 0.52f, 0.0f);
// SSS color (e.g., vec3(0.8, 0.2, 0.2)
//uniform vec3 subsurfaceColor;   // SSS color (e.g., vec3(0.8, 0.2, 0.2) for reddish skin-like scattering).
//uniform float lightIntensity;   // Overall light intensity scalar.
//uniform vec3 objectColor;       // Base color of the model (diffuse albedo).

	GLuint programR2T_ID;
	GLuint TextureR2T;
	GLuint TextureR2T_ID;
	GLuint LightID;

	GLuint renderedTexture;
	GLuint depthrenderbuffer;
	GLuint SelectingFrameBuffer;
	GLuint colorBuffer;
	GLuint depthBuffer;

	SelectionFramebuffer selectFrameBuffer;

	bool SearchForItemWithID_(int selectedId);
	bool SearchForItemWithID_ForMosueOver(int selectedId);
	void EmptySelection();
	void EmptyMouseOverSelection();

	vector<glm::vec3> g_quad_vertex_buffer_data;

	GLuint quad_vertexbuffer;
	GLuint quad_programID;
	GLuint texID;
	GLuint timeID;

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };

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

	//	Isocontours		//	La gestion de �a va �tre quelque chose

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
	float horizontalAngle = 3.14159f;
	// Initial vertical angle : none
	float verticalAngle = 3.14159f/5.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.001f;

	float m_Scale = 1.0f;

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

	bool isShowGrid = true;
	bool ToggleGrid();
	bool colormapModeReleased = true;
	bool OrthoModReleased = true;
	bool OrthoMod = true;

	GLuint colorMapID;
	GLuint minID;
	GLuint maxID;

	KeyControl m_KeyListing;

	float sensibilityControl = 3.0f;
	float precisionControler = 0.1f;

	SimplifiedMesh simplifyVertices(const std::vector<glm::vec3>& inputVertices, float epsilon);
};
