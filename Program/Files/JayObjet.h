#pragma once

//#include "GraphicCard.h"


//#include "Shader.h"
#include "structures.h"
#include "MateriauxJay.h"
#include "emlist.h"
#include <unordered_map>
#include <vector>
#include "Shader.h"

#include <iostream>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

using namespace std;

enum class TypeData {
	vertices = 0,
	normals = 1,
	uvs = 2,
	Utangents = 3,
	Vtangents = 4,
	indices = 5
};

enum class TypeObjetVar {
	neutral = 0,
	typeCouleur = 1,
	typeCentre = 2,
	typeMatrixTransformation4x4 = 3,
};

class JayObjet {
public:
	unsigned int id = 0;

	JayObjet();
	JayObjet(vector<glm::vec3> newPoints);
	JayObjet(GLenum newmode, vector<glm::vec3> newPoints);
	~JayObjet();

	emlist<unordered_map<string, ShaderJay>::iterator> shaderIDList; // List of shaders for materials
	emlist<unordered_map<string, ShaderJay>::iterator>::iterator itshaderID;

	ShaderJay* ptrShader = nullptr;

	unordered_map<string, ShaderJay>::iterator Bind(unordered_map<string, ShaderJay>::iterator newShaderID);
	unordered_map<string, ShaderJay>::iterator itShaderLinked;

	void Init();
	void DeclareObjet();
	void Update();
	void Clean();


//private:
	void UpdateIDs();

	void BuildCloudOfPoints(std::vector<float> cloud);
	void BuildPlane();
	void BuildSphere();
	void BuildCylinder();
	void CalculateSmoothShading();
	void CalculateFlatShading();

public:
	std::vector<glm::vec3> getSphereVertices(float rad, int meridian, int latitude);
	std::vector<glm::vec3> getSphereNormals(int meridian, int latitude, glm::vec3 vectInit);
	std::vector<glm::vec3> getSphereNormals(int meridian, int latitude);
	std::vector<glm::vec3> getSphereTu(int meridian, int latitude);
	std::vector<glm::vec3> getSphereTv(int meridian, int latitude);
	std::vector<glm::vec2> getSphereUVs(int meridian, int latitude);

	std::vector<glm::vec3> getCylinderVertices(float rad, float height, int meridian, int latitude);
	std::vector<glm::vec3> getCylinderNormals(int meridian, int latitude, glm::vec3 vectInit);
	std::vector<glm::vec3> getCylinderNormals(int meridian, int latitude);
	std::vector<glm::vec3> getCylinderTu(int meridian, int latitude);
	std::vector<glm::vec3> getCylinderTv(int meridian, int latitude);
	std::vector<glm::vec2> getCylinderUVs(int meridian, int latitude);

	std::vector<glm::vec3> getNormalPerVertex(std::vector<glm::vec3> base, std::vector<glm::vec3> toAdd, float multiplier);

	void BuildQuadForGraphicCalculations();


	void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
	void Draw();
	void DumpTheseDatasIntoBufferForGPU(vector<glm::vec3> newData, GLenum newmode, TypeData pos, GLint newAttPos);
	void DumpTheseDatasIntoBufferForGPU(vector<glm::vec2> newData, GLenum newmode, TypeData pos, GLint newAttPos);
	void DumpTheseDatasIntoBufferForGPU(vector<unsigned short> newData, GLenum newmode, TypeData pos);
	void Display();

	void BuildCloudOfPoints(int newshader, int newResolution, float newScale, vector<float> cloud) { SetShader(newshader); BuildCloudOfPoints(cloud); UpdateResolution(newResolution); UpdateScale(newScale); SetType(0); };
	void BuildPlane(int newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildPlane(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(1); };
	void BuildSphere(int newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildSphere(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(2); };
	void BuildCylinder(int newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildCylinder(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(3); };

	void UpdateNormals();
	void DrawNormals(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	void UpdateResolution(int newResolution) { ObjectResolution = newResolution; };
	void UpdateScale(float newScale) { Scale = newScale; };
	void ToggleActivation() { active = !active; };
	void Activate() { active = true; };
	bool IsActive() { return active; };

public:
	int SetType(int newType) { return type = newType; };
	int type;

	//   To make lines or striplines, use GL_LINE_STRIP or GL_LINES
	//	There are 11 different mode given for the function drawarrays
	GLint mode = GL_TRIANGLES;

	bool active = true;
	float Scale = 200;
	int ObjectResolution = 50;

	bool selected = false;
	bool ToggleSelection(bool) { return selected = !selected; };
	bool SetSelection(bool newsel) { return selected = newsel; };

	bool mouseOver = false;
	bool ToggleMouseOver(bool) { return mouseOver = !mouseOver; };
	bool SetmouseOver(bool newmouseOver) { return mouseOver = newmouseOver; };

	int maxAttributeToEnable = 0;
	int attributePos = 0;

	GLenum verticesMode = GL_TRIANGLES;
	GLenum normalsMode = GL_TRIANGLES;
	GLenum uvsMode = GL_2D;
	GLenum tusMode = GL_TRIANGLES;
	GLenum tvsMode = GL_TRIANGLES;
	GLenum indsMode = GL_TRIANGLES;

	GLint vertatt;
	GLint normatt;
	GLint uvsatt;
	GLint indatt;
	GLint tanUatt;
	GLint tanVatt;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned short> _indices;
	std::vector<glm::vec3> tus;
	std::vector<glm::vec3> tvs;
	std::vector<glm::vec2> texCoords;

	glm::vec3 objColor = glm::vec3(0.3f, 0.3f, 0.3f);

	glm::vec3 center;
	glm::vec3 mins;
	glm::vec3 maxs;

	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec3 tu;
	glm::vec3 tv;

	glm::mat4x4 transformMatrix;
	
	Material materials;

	string name;

	unsigned int textureColorID;
	unsigned int textureHeightID;
	unsigned int textureBumpID;

	//// Matrices
	//glm::mat4 projectionMatrix;
	//glm::mat4 viewMatrix;
	//glm::mat4 planMatrix;
	//glm::mat4 coneMatrix;

	glm::mat4 modelMatrix;
	glm::mat4 modelView;
	glm::mat3 normalMatrix;

	bool isMaterial = false;
	bool isColorTexture = false;
	bool heightTexture = false;
	bool bumpTexture = false;

	bool isInit = false;
	bool isvbo = false;
	bool isnbo = false;
	bool isuvbo = false;
	bool istubo = false;
	bool istvbo = false;
	bool isindbo = false;

	bool isNormals = false;

	unsigned int vertexArrayID = 0;

	unsigned int vertexBufferID = 0;
	unsigned int normalBufferID = 0;
	unsigned int uvBufferID = 0;
	unsigned int tangentU_BufferID = 0;
	unsigned int tangentV_BufferID = 0;
	unsigned int indicesBufferID = 0;

	unsigned int vaoNormalLinesID;
	unsigned int vboNormalLinesID;

	int shader;
	int SetShader(int newshader = 0) { return shader = newshader; };
	int GetShader() { return shader; };

	void Init(int newShader);




};


class ToolObjet : public JayObjet {
	ToolObjet();
	~ToolObjet();
};