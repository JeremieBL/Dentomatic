


#include "MultipleJays.h"

MultipleJays::MultipleJays()
{
	//	Warnings, no initalization here!!!
}

MultipleJays::MultipleJays(string shaderName)
{
	Init(shaderName, gl_type);
	vertices = BuildCircle(0.05f, 12);
	UpdateVecticesIDs();
}

MultipleJays::MultipleJays(vector<glm::vec3> newVertices, string shaderName)
{
	Init(shaderName, gl_type);
	vertices = newVertices;
	UpdateVecticesIDs();
}

MultipleJays::MultipleJays(vector<glm::vec3> newVertices, string vertexName, string fragmentName)
{
	Init(vertexName, fragmentName, gl_type);
	vertices = newVertices;
	UpdateVecticesIDs();
}


MultipleJays::~MultipleJays()
{
//		CleanUp();
}


void MultipleJays::Init(string s, GLuint newGL_Type = GL_TRIANGLES)
{
	gl_type = newGL_Type;

	glGenVertexArrays(1, &ArrayID);
	glGenBuffers(1, &buffer);

	string vertexName = s;
	vertexName += ".vertexshader";

	string fragmentName = s;
	fragmentName += ".fragmentshader";

	// Create and compile our GLSL program from the shaders for isocontour
	programID = LoadShaders(vertexName.c_str(), fragmentName.c_str());

	// Get a handle for our "MVP" uniform
	MVPMatrixID = glGetUniformLocation(programID, "MVP");
	coloID = glGetUniformLocation(programID, "inColor");

}

void MultipleJays::Init(string vertexName, string fragmentName, GLuint newGL_Type = GL_TRIANGLES)
{
	gl_type = newGL_Type;

	glGenVertexArrays(1, &ArrayID);
	glGenBuffers(1, &buffer);

	// Create and compile our GLSL program from the shaders for isocontour
	programID = LoadShaders(vertexName.c_str(), fragmentName.c_str());

	// Get a handle for our "MVP" uniform
	MVPMatrixID = glGetUniformLocation(programID, "MVP");
	coloID = glGetUniformLocation(programID, "inColor");

}

void MultipleJays::UpdateWith(vector<glm::vec3> newvectices)
{
	vertices = newvectices;
	UpdateVecticesIDs();

}

void MultipleJays::PushBackVectices(glm::vec3 newvectices)
{
	vertices.push_back(newvectices);
	UpdateVecticesIDs();

	if (positions.size() == 0)
		positions.push_back(glm::vec3(0, 0, 0));

}

void MultipleJays::UpdatePositions(vector<glm::vec3> newPositions)
{
	positions = newPositions;
}

int MultipleJays::PushBackPoints(glm::vec3 newPt)
{
	positions.push_back(newPt);

	return positions.size();
}

void MultipleJays::EraseVertices()
{
	vertices.resize(0);
	UpdateVecticesIDs();
	ErasePoints();
}

int MultipleJays::ErasePoints()
{
	positions.resize(0);

	return positions.size();
}

void MultipleJays::UpdateVecticesIDs()
{
	if (vertices.size() != 0) {

		glBindVertexArray(ArrayID);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	}
}

void MultipleJays::Draw()
{
	assert(vertices.size() != 0);

	glBindVertexArray(ArrayID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the lines !

	glDrawArrays(gl_type, 0, vertices.size());
	glDisableVertexAttribArray(0);
}

void MultipleJays::Display(CameraJay& camera)
{
	for (size_t i = 0; i < positions.size(); i++)
	{
		glUseProgram(programID);
		glUniform3f(coloID, 0.0, 0.0, 0.0f);

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, positions[i]);
		glm::mat4 MVP = camera.ProjectionMatrix * camera.ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVP[0][0]);

		Draw();

		glUseProgram(0);
	}
}

int MultipleJays::Size()
{
	return positions.size();
}


void MultipleJays::CleanUp()
{
	glDeleteProgram(programID);
	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &ArrayID);
}


vector<glm::vec3> MultipleJays::BuildCircle(float radius, int nbrDot)
{
	vector<glm::vec3> vertices;

	float angleVar = 2.f * glm::pi<float>() / (float) nbrDot;
	glm::vec4 it(radius, 0, 0, 1.0f);
	glm::mat4 rotMat = glm::mat4(1.0f);
	rotMat = glm::rotate(rotMat, angleVar, glm::vec3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i < nbrDot; ++i)
	{
		glm::vec4 beforeIt = it;
		it = rotMat * it;

		vertices.push_back(glm::vec3(glm::vec4(0,0,0,0)));
		vertices.push_back(glm::vec3(beforeIt));
		vertices.push_back(glm::vec3(it));
	}	

	return vertices;
}

vector<glm::vec3> MultipleJays::BuildEdge(float radiusin, float radiusout, int nbrDot)
{
	vector<glm::vec3> vertices;

	float angleVar = 2.f * glm::pi<float>() / (float)nbrDot;
	glm::vec4 intit(radiusin, 0, 0, 1.0f);
	glm::vec4 outit(radiusout, 0, 0, 1.0f);

	glm::mat4 rotMat = glm::mat4(1.0f);
	rotMat = glm::rotate(rotMat, angleVar, glm::vec3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i < nbrDot; ++i)
	{
		glm::vec4 beforeoutIt = outit;
		glm::vec4 beforeinIt = intit;
		outit = rotMat * outit;
		intit = rotMat * intit;

		vertices.push_back(glm::vec3(beforeinIt));
		vertices.push_back(glm::vec3(beforeoutIt));
		vertices.push_back(glm::vec3(outit));

		vertices.push_back(glm::vec3(outit));
		vertices.push_back(glm::vec3(intit));
		vertices.push_back(glm::vec3(beforeinIt));
	}

	return vertices;
}


vector<glm::vec3> MultipleJays::BuildCross(float, int) {

	//	The problem with this shit is that it needs to be seperated.

	vector<glm::vec3> vertices2;

	vertices.push_back(glm::vec3(0.125, 0, 0));
	vertices.push_back(glm::vec3(-0.125, 0, 0));
	vertices.push_back(glm::vec3(0, 0.125, 0));
	vertices.push_back(glm::vec3(0, -0.125, 0));
	vertices.push_back(glm::vec3(0, 0, 0.125));
	vertices.push_back(glm::vec3(0, 0, -0.125));

	return vertices2;
};

vector<glm::vec3> MultipleJays::BuildCube(float size) {
	vector<glm::vec3> vertices;

	std::vector<glm::vec3> normals;

	vertices.clear();
	normals.clear();

	float h = size / 2.0f; // Half-size for centering the cube

	// Define the 8 vertices of the cube
	std::vector<glm::vec3> cubeVertices = {
		{-h, -h,  h}, // 0
		{ h, -h,  h}, // 1
		{ h,  h,  h}, // 2
		{-h,  h,  h}, // 3
		{-h, -h, -h}, // 4
		{ h, -h, -h}, // 5
		{ h,  h, -h}, // 6
		{-h,  h, -h}  // 7
	};

	// Define normals for each face
	std::vector<glm::vec3> cubeNormals = {
		{ 0,  0,  1}, // Front
		{ 0,  0, -1}, // Back
		{ 0,  1,  0}, // Top
		{ 0, -1,  0}, // Bottom
		{ 1,  0,  0}, // Right
		{-1,  0,  0}  // Left
	};

	// Define indices for triangle faces (6 faces, 2 triangles per face, 3 vertices per triangle)
	std::vector<int> indices = {
		// Front
		0, 1, 2,  0, 2, 3,
		// Back
		5, 4, 7,  5, 7, 6,
		// Top
		3, 2, 6,  3, 6, 7,
		// Bottom
		4, 5, 1,  4, 1, 0,
		// Right
		1, 5, 6,  1, 6, 2,
		// Left
		4, 0, 3,  4, 3, 7
	};

	// Assign normals to each face (6 vertices per face)
	std::vector<int> normalIndices = {
		0, 0, 0, 0, 0, 0, // Front
		1, 1, 1, 1, 1, 1, // Back
		2, 2, 2, 2, 2, 2, // Top
		3, 3, 3, 3, 3, 3, // Bottom
		4, 4, 4, 4, 4, 4, // Right
		5, 5, 5, 5, 5, 5  // Left
	};

	// Add vertices and normals based on indices
	for (size_t i = 0; i < indices.size(); ++i) {
		vertices.push_back(cubeVertices[indices[i]]);
		normals.push_back(cubeNormals[normalIndices[i]]);
	}

	return vertices;

	//Vecteur3D Pt1, Pt2, Pt3, Pt4;
	//iBuild->iCrPt = iBuild->CreationLine.begin();
	//Pt2 = Pt1 = iBuild->iCrPt->Coord;
	//++iBuild->iCrPt;
	//if (iBuild->iCrPt != iBuild->CreationLine.end())
	//{
	//	Pt2 = iBuild->iCrPt->Coord;

	//	++iBuild->iCrPt;
	//	if (iBuild->iCrPt != iBuild->CreationLine.end())
	//		Pt3 = iBuild->iCrPt->Coord;
	//}

	//int NbSide1 = 1, NbSide2 = 1, NbSide3 = 1;
	//StringIntList* iIndList = iBuild->TeteInd;
	//if (iIndList != nullptr)	//	Ca conserve combien il y a de face
	//{
	//	NbSide1 = iIndList->Valeur;

	//	iIndList = iIndList->Nx;
	//	if (iIndList != nullptr)	//	Sinon on va consid�rer qu'il n'y a qu'une seule face.
	//	{
	//		NbSide2 = iIndList->Valeur;

	//		iIndList = iIndList->Nx;
	//		if (iIndList != nullptr)	//	Sinon on va consid�rer qu'il n'y a qu'une seule face.
	//			NbSide3 = iIndList->Valeur;
	//	}
	//}

	//iBuild->Center = (Pt1 + Pt2) / 2.0;
	//iBuild->Center.y = Pt3.y / 2.0;

	//iBuild->HaveCenter = true;

	//if (!iBuild->Shaped) {
	//	iBuild->Shaped = true;
	//	iBuild->StartOver();

	//	MakeBox(iBuild, Vecteur3D(1.0), Vecteur3D(NbSide1, NbSide2, NbSide3));

	//	iBuild->Flush_MainLine_Forme();
	//	iBuild->CalculateEveryNormalVertex();
	//	iBuild->GetSelectBox();
	//}

	//iBuild->ScaleRatios = Pt2 - Pt1;
	//iBuild->ScaleRatios.y = (Pt3 == 0.0) ? 0.25 : GetLength(Pt3 - Pt2);
	//iBuild->ScaleRatios.abs();
};
vector<glm::vec3> MultipleJays::BuildSphere(float, int) {
	vector<glm::vec3> vertices;
	return vertices;
};
vector<glm::vec3> MultipleJays::BuildSquaredSphere(float, int) {
	vector<glm::vec3> vertices;
	return vertices;
};


/*

// Function to generate a sphere's vertices and normals
void generateSphere(float radius, int sectors, int stacks, std::vector<Vec3>& vertices, std::vector<Vec3>& normals) {
	const float PI = 3.14159265359f;
	float sectorStep = 2.0f * PI / sectors;
	float stackStep = PI / stacks;

	for (int i = 0; i <= stacks; ++i) {
		float stackAngle = PI / 2.0f - i * stackStep; // From +pi/2 to -pi/2
		float xy = radius * std::cos(stackAngle);    // r * cos(u)
		float z = radius * std::sin(stackAngle);     // r * sin(u)

		for (int j = 0; j <= sectors; ++j) {
			float sectorAngle = j * sectorStep;      // From 0 to 2pi

			// Vertex position
			float x = xy * std::cos(sectorAngle);    // r * cos(u) * cos(v)
			float y = xy * std::sin(sectorAngle);    // r * cos(u) * sin(v)

			// Normalized vertex normal (same as position for a sphere, normalized)
			float nx = x / radius;
			float ny = y / radius;
			float nz = z / radius;

			vertices.push_back({x, y, z});
			normals.push_back({nx, ny, nz});
		}
	}
}

// Function to generate a cube's vertices and normals
void generateCube(float size, std::vector<Vec3>& vertices, std::vector<Vec3>& normals) {
	float h = size / 2.0f; // Half-size for centering the cube

	// Define the 8 vertices of the cube
	std::vector<Vec3> cubeVertices = {
		{-h, -h,  h}, // 0
		{ h, -h,  h}, // 1
		{ h,  h,  h}, // 2
		{-h,  h,  h}, // 3
		{-h, -h, -h}, // 4
		{ h, -h, -h}, // 5
		{ h,  h, -h}, // 6
		{-h,  h, -h}  // 7
	};

	// Define normals for each face
	std::vector<Vec3> cubeNormals = {
		{ 0,  0,  1}, // Front
		{ 0,  0, -1}, // Back
		{ 0,  1,  0}, // Top
		{ 0, -1,  0}, // Bottom
		{ 1,  0,  0}, // Right
		{-1,  0,  0}  // Left
	};

	// Define indices for triangle faces (6 faces, 2 triangles per face, 3 vertices per triangle)
	std::vector<int> indices = {
		// Front
		0, 1, 2,  0, 2, 3,
		// Back
		5, 4, 7,  5, 7, 6,
		// Top
		3, 2, 6,  3, 6, 7,
		// Bottom
		4, 5, 1,  4, 1, 0,
		// Right
		1, 5, 6,  1, 6, 2,
		// Left
		4, 0, 3,  4, 3, 7
	};

	// Assign normals to each face (6 vertices per face)
	std::vector<int> normalIndices = {
		0, 0, 0, 0, 0, 0, // Front
		1, 1, 1, 1, 1, 1, // Back
		2, 2, 2, 2, 2, 2, // Top
		3, 3, 3, 3, 3, 3, // Bottom
		4, 4, 4, 4, 4, 4, // Right
		5, 5, 5, 5, 5, 5  // Left
	};

	// Add vertices and normals based on indices
	for (size_t i = 0; i < indices.size(); ++i) {
		vertices.push_back(cubeVertices[indices[i]]);
		normals.push_back(cubeNormals[normalIndices[i]]);
	}



	struct Vec3 {
	float x, y, z;
};

// Function to generate a squared-sphere's vertices and normals
void generateSquaredSphere(float radius, int resolution, std::vector<Vec3>& vertices, std::vector<Vec3>& normals) {
	// Ensure resolution is at least 1
	resolution = std::max(1, resolution);
	float step = 1.0f / resolution;

	// Helper function to normalize a vector to the sphere's radius
	auto normalizeToRadius = [radius](Vec3& v) {
		float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (length > 0) {
			float scale = radius / length;
			v.x *= scale;
			v.y *= scale;
			v.z *= scale;
		}
	};

	// Generate vertices and normals for each face of the cube
	auto generateFace = [&](Vec3 base, Vec3 u, Vec3 v, Vec3 normal) {
		for (int i = 0; i <= resolution; ++i) {
			for (int j = 0; j <= resolution; ++j) {
				// Compute vertex position on the cube face
				float s = i * step;
				float t = j * step;
				Vec3 vertex = {
					base.x + s * u.x + t * v.x,
					base.y + s * u.y + t * v.y,
					base.z + s * u.z + t * v.z
				};

				// Normalize vertex to sphere radius
				normalizeToRadius(vertex);

				// Normal is the normalized vertex position (for a sphere)
				Vec3 vertexNormal = { vertex.x, vertex.y, vertex.z };
				normalizeToRadius(vertexNormal); // Ensure normal is unit length

				vertices.push_back(vertex);
				normals.push_back(vertexNormal);
			}
		}
	};

	// Define cube faces (base vertex, u and v vectors, normal)
	// Cube is centered at origin with half-size 1
	// Front face (z = +1)
	generateFace({-1, -1, 1}, {2, 0, 0}, {0, 2, 0}, {0, 0, 1});
	// Back face (z = -1)
	generateFace({1, -1, -1}, {-2, 0, 0}, {0, 2, 0}, {0, 0, -1});
	// Top face (y = +1)
	generateFace({-1, 1, -1}, {2, 0, 0}, {0, 0, 2}, {0, 1, 0});
	// Bottom face (y = -1)
	generateFace({-1, -1, 1}, {2, 0, 0}, {0, 0, -2}, {0, -1, 0});
	// Right face (x = +1)
	generateFace({1, -1, -1}, {0, 0, 2}, {0, 2, 0}, {1, 0, 0});
	// Left face (x = -1)
	generateFace({-1, -1, 1}, {0, 0, -2}, {0, 2, 0}, {-1, 0, 0});
}

	*/