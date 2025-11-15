#pragma once

//#include "GraphicCard.h"


#include "Shader.h"
#include "structures.h"

#include <vector>

using namespace std;

class JayObjet {
public:
	JayObjet();
	JayObjet(vector<glm::vec3> newPoints);
	~JayObjet();

	void Init();
	void Update();
private:

	void UpdateIDs();

	void BuildCloudOfPoints(std::vector<float> cloud);
	void BuildPlane();
	void BuildSphere();
	void BuildCylinder();

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

	void BuildCloudOfPoints(Shader* newshader, int newResolution, float newScale, vector<float> cloud) { SetShader(newshader); BuildCloudOfPoints(cloud); UpdateResolution(newResolution); UpdateScale(newScale); SetType(0); };
	void BuildPlane(Shader* newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildPlane(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(1); };
	void BuildSphere(Shader* newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildSphere(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(2); };
	void BuildCylinder(Shader* newshader, int newResolution, float newDimensions) { SetShader(newshader); BuildCylinder(); UpdateResolution(newResolution); UpdateScale(newDimensions); SetType(3); };

	void UpdateNormals();
	void DrawNormals(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	void UpdateResolution(int newResolution) { ObjectResolution = newResolution; };
	void UpdateScale(float newScale) { Scale = newScale; };

private:
	int SetType(int newType) { return type = newType; };
	int type;

	float Scale = 200;
	int ObjectResolution = 50;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tus;
	std::vector<glm::vec3> tvs;
	std::vector<glm::vec2> texCoords;

	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec3 tu;
	glm::vec3 tv;
	
	Material materials;

	int iname;
	string sname;

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

	bool isnbo = false;
	bool istubo = false;
	bool istvbo = false;
	bool istbo = false;

	bool isNormals = false;

	unsigned int vaoID;
	unsigned int vboID;
	unsigned int nboID;
	unsigned int tuboID;
	unsigned int tvboID;
	unsigned int tboID;

	unsigned int vaoNormalLinesID;
	unsigned int vboNormalLinesID;

	Shader* shader;
	Shader* SetShader(Shader* newshader = nullptr) { return shader = newshader; };
	Shader* GetShader() { return shader; };

	void Init(Shader* newShader);


};
