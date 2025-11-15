

#include "JayObjet.h"

#include <iostream>

using namespace std;

JayObjet::JayObjet() {
	modelMatrix = glm::mat4(1.0f);
	modelView = glm::mat4(1.0f);
	normalMatrix = glm::mat3(1.0f);
}

JayObjet::JayObjet(vector<glm::vec3> newPoints) : vertices(newPoints)
{
	cout << "Am I here once" << endl;
};

JayObjet::~JayObjet()
{
	shader = nullptr;
}

void JayObjet::Init(Shader* newShader) {
	cout << "Thats why is a problem" << endl;
	shader = newShader;
}

void JayObjet::Init() {

	// Object
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);

	if (isnbo) 	glGenBuffers(1, &nboID);
	if (istubo) glGenBuffers(1, &tuboID);
	if (istvbo) glGenBuffers(1, &tvboID);
	if (istbo) glGenBuffers(1, &tboID);

	// Normals
	if (isNormals) {
		glGenVertexArrays(1, &vaoNormalLinesID);
		glGenBuffers(1, &vboNormalLinesID);
	}
}

void JayObjet::Update()
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		BuildPlane();
		break;
	case 2:
		BuildSphere();
		break;
	case 3:
		BuildCylinder();
		break;
	}
	UpdateIDs();
}

void JayObjet::UpdateIDs() {
	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	int in_PositionLocation = glGetAttribLocation(shader->id(), "in_Position");
	glEnableVertexAttribArray(in_PositionLocation);
	glVertexAttribPointer(in_PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


	if (isnbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, nboID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

		int in_NormalLocation = glGetAttribLocation(shader->id(), "in_Normal");
		glEnableVertexAttribArray(in_NormalLocation);
		glVertexAttribPointer(in_NormalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istubo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tuboID);
		glBufferData(GL_ARRAY_BUFFER, tus.size() * sizeof(glm::vec3), &tus[0], GL_STATIC_DRAW);

		int in_TuLocation = glGetAttribLocation(shader->id(), "in_Tv");
		glEnableVertexAttribArray(in_TuLocation);
		glVertexAttribPointer(in_TuLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istvbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tvboID);
		glBufferData(GL_ARRAY_BUFFER, tvs.size() * sizeof(glm::vec3), &tvs[0], GL_STATIC_DRAW);

		int in_TvLocation = glGetAttribLocation(shader->id(), "in_Tv");
		glEnableVertexAttribArray(in_TvLocation);
		glVertexAttribPointer(in_TvLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}


	if (istbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tboID);
		glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

		int in_TexCoordLocation = glGetAttribLocation(shader->id(), "in_TexCoord");
		glEnableVertexAttribArray(in_TexCoordLocation);
		glVertexAttribPointer(in_TexCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

void JayObjet::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	shader->bind(); // bind shader

	//				// Get the locations of uniforms
	//int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix");
	//int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix");
	//int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix");
	//int modelViewLocation = glGetUniformLocation(shader->id(), "modelView");
	//int normalMatrixLocation = glGetUniformLocation(shader->id(), "normalMatrix");

	//// Copy data to the GPU
	//glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	//glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	//modelView = viewMatrix * modelMatrix;
	//glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
	//normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));
	//glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, &normalMatrix[0][0]);

	if (isMaterial)
	{
		int materialKaLocation = glGetUniformLocation(shader->id(), "materialKa");
		int materialKdLocation = glGetUniformLocation(shader->id(), "materialKd");
		int materialKsLocation = glGetUniformLocation(shader->id(), "materialKs");
		int materialShininessLocation = glGetUniformLocation(shader->id(), "materialShininess");
		
		glUniform3f(materialKaLocation, materials.ambient[0], materials.ambient[1], materials.ambient[2]);
		glUniform3f(materialKdLocation, materials.diffuse[0], materials.diffuse[1], materials.diffuse[2]);
		glUniform3f(materialKsLocation, materials.specular[0], materials.specular[1], materials.specular[2]);
		glUniform1f(materialShininessLocation, materials.shininess);
	}

	if (isColorTexture)
	{
		// Draw our object
		GLint colorTex_uniform_loc = glGetUniformLocation(shader->id(), "colorTexture");
		glUniform1i(colorTex_uniform_loc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureColorID);
	}

	if (heightTexture)
	{
		GLint dispTex_uniform_loc = glGetUniformLocation(shader->id(), "heightTexture");
		glUniform1i(dispTex_uniform_loc, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureHeightID);
	}

	if (bumpTexture)
	{
		GLint bumpTex_uniform_loc = glGetUniformLocation(shader->id(), "bumpTexture");
		glUniform1i(bumpTex_uniform_loc, 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureBumpID);
	}

	glBindVertexArray(vaoID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (isnbo)
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, nboID);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	if (istubo)
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, tboID);
		glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istvbo)
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tuboID);
		glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istbo)
	{
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, tvboID);
		glVertexAttribPointer((GLuint)4, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);

	shader->unbind(); // Unbind shader
}

void JayObjet::UpdateNormals() {
	switch (type)
	{
	case 0:
		break;
	case 1:
	{

		float step = Scale * 2 / ObjectResolution;
		float uvStep = 1.0f / ObjectResolution;
		//	ObjectResolution = 7
		//	Plan = 7x7


		normal = glm::vec3(0.f, 1.f, 0.f);
		tu = glm::vec3(1.f, 0.f, 0.f);
		tv = glm::vec3(0.f, 0.f, -1.f);

		for (float i = 0, xpos = -Scale, uvx = 0; i < ObjectResolution; i++, xpos += step, uvx += uvStep)
		{
			for (float j = 0, zpos = -Scale, uvy = 0; j < ObjectResolution; j++, zpos += step, uvy += uvStep)
			{
				// First triangle
				vertex.x = xpos; vertex.y = -0.f; vertex.z = zpos;				vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy));
				vertex.x = xpos; vertex.y = -0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
				vertex.x = xpos + step; vertex.y = -0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));

				// Second triangle
				vertex.x = xpos + step; vertex.y = -0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));
				vertex.x = xpos; vertex.y = -0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
				vertex.x = xpos + step; vertex.y = -0.f; vertex.z = zpos + step;	vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy + uvStep));
			}
		}
	}
	break;
	case 2:
		vertices = getSphereVertices(50, ObjectResolution, ObjectResolution);
		normals = getSphereNormals(ObjectResolution, ObjectResolution);
		tus = getSphereTu(ObjectResolution, ObjectResolution);
		tvs = getSphereTv(ObjectResolution, ObjectResolution);
		texCoords = getSphereUVs(ObjectResolution, ObjectResolution);

		break;
	case 3:
		vertices = getCylinderVertices(50, 150, ObjectResolution, ObjectResolution);
		normals = getCylinderNormals(ObjectResolution, ObjectResolution);
		tus = getCylinderTu(ObjectResolution, ObjectResolution);
		tvs = getCylinderTv(ObjectResolution, ObjectResolution);
		texCoords = getCylinderUVs(ObjectResolution, ObjectResolution);
		break;
	default:
		break;
	}

	std::vector<glm::vec3> vertexes = getNormalPerVertex(vertices, normals, 8);

	//vertices = justchangethebase(vertices, normals, 10);
	//vertexes = addTo(vertexes, getNormalPerVertex(vertices, tus, 8));
	//vertexes = addTo(vertexes, getNormalPerVertex(vertices, tvs, 8));

	glBindVertexArray(vaoNormalLinesID);

	glBindBuffer(GL_ARRAY_BUFFER, vboNormalLinesID);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec3), &vertexes[0], GL_STATIC_DRAW);

	int in_PositionLocation = glGetAttribLocation(shader->id(), "in_Position");
	glEnableVertexAttribArray(in_PositionLocation);
	glVertexAttribPointer(in_PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void JayObjet::DrawNormals(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	shader->bind(); // bind shader
					//int lightPosLocation = glGetUniformLocation(shader->id(), "lightPosition");
					//glUniform4f(lightPosLocation, light.position[0], light.position[1], light.position[2], 0.f);

	glm::mat4 normalMat = glm::mat4(1.0f);

	// Get the locations of uniforms
	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix");
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix");
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix");
	int modelViewLocation = glGetUniformLocation(shader->id(), "modelView");
	int normalMatrixLocation = glGetUniformLocation(shader->id(), "normalMatrix");

	int materialKdLocation = glGetUniformLocation(shader->id(), "materialKd");

	// Copy data to the GPU
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &normalMat[0][0]);
	modelView = viewMatrix * normalMat;
	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
	normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));
	glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, &normalMatrix[0][0]);

	glUniform3f(materialKdLocation, 1.f, 1.f, 1.f);

	glBindVertexArray(vaoNormalLinesID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormalLinesID);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_LINES, 0, vertices.size());

	glBindVertexArray(0);

	shader->unbind(); // Unbind shader}
}

void JayObjet::BuildCloudOfPoints(vector<float> cloud) {
	float step = Scale * 2 / ObjectResolution;
	float uvStep = 1.0f / ObjectResolution;
	//	ObjectResolution = 7
	//	Plan = 7x7

	normal = glm::vec3(0.f, 1.f, 0.f);
	tv = glm::vec3(1.f, 0.f, 0.f);
	tu = glm::vec3(0.f, 0.f, -1.f);

	for (float i = 0, xpos = -Scale, uvx = 0; i < ObjectResolution; i++, xpos += step, uvx += uvStep)
	{
		for (float j = 0, zpos = -Scale, uvy = 0; j < ObjectResolution; j++, zpos += step, uvy += uvStep)
		{
			// First triangle
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos;				vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy));
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));

			// Second triangle
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos + step;	vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy + uvStep));
		}
	}

	UpdateIDs();
}


void JayObjet::BuildPlane() {
	float step = Scale * 2 / ObjectResolution;
	float uvStep = 1.0f / ObjectResolution;
	//	ObjectResolution = 7
	//	Plan = 7x7

	normal = glm::vec3(0.f, 1.f, 0.f);
	tv = glm::vec3(1.f, 0.f, 0.f);
	tu = glm::vec3(0.f, 0.f, -1.f);

	for (float i = 0, xpos = -Scale, uvx = 0; i < ObjectResolution; i++, xpos += step, uvx += uvStep)
	{
		for (float j = 0, zpos = -Scale, uvy = 0; j < ObjectResolution; j++, zpos += step, uvy += uvStep)
		{
			// First triangle
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos;				vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy));
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));

			// Second triangle
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy));
			vertex.x = xpos; vertex.y = 0.f; vertex.z = zpos + step;			vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy + uvStep));
			vertex.x = xpos + step; vertex.y = 0.f; vertex.z = zpos + step;	vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx + uvStep, uvy + uvStep));
		}
	}

	UpdateIDs();
}

void JayObjet::BuildSphere() {
	vertices = getSphereVertices(50, ObjectResolution, ObjectResolution);
	normals = getSphereNormals(ObjectResolution, ObjectResolution);
	tus = getSphereTu(ObjectResolution, ObjectResolution);
	tvs = getSphereTv(ObjectResolution, ObjectResolution);
	texCoords = getSphereUVs(ObjectResolution, ObjectResolution);

	UpdateIDs();
}

void JayObjet::BuildCylinder() {
	vertices = getCylinderVertices(50, 150, ObjectResolution, ObjectResolution);
	normals = getCylinderNormals(ObjectResolution, ObjectResolution);
	tus = getCylinderTu(ObjectResolution, ObjectResolution);
	tvs = getCylinderTv(ObjectResolution, ObjectResolution);
	texCoords = getCylinderUVs(ObjectResolution, ObjectResolution);

	UpdateIDs();
}

glm::vec3 rotRodriguez(glm::vec3 ptToRot, glm::vec3 s, float angle)
{
	glm::mat3x3 matRot;
	float cos = glm::cos(angle);
	float sin = glm::sin(angle);

	matRot[0][0] = s.x*s.x + (1 - s.x*s.x) * cos;
	matRot[0][1] = s.x*s.y * (1 - cos) + s.z*sin;
	matRot[0][2] = s.x*s.z*(1 - cos) - s.y*sin;

	matRot[1][0] = s.x*s.y*(1 - cos) - s.z*sin;
	matRot[1][1] = s.y*s.y + (1 - s.y*s.y)*cos;
	matRot[1][2] = s.y*s.z*(1 - cos) + s.x*sin;

	matRot[2][0] = s.x*s.z*(1 - cos) + s.y*sin;
	matRot[2][1] = s.y*s.z*(1 - cos) - s.x*sin;
	matRot[2][2] = s.z*s.z + (1 - s.z*s.z)*cos;

	return(matRot*ptToRot);
}

glm::vec3 rotRodriguez(glm::vec3 ptToRot, glm::vec3 s, float cos, float sin)
{
	glm::mat3x3 matRot;

	matRot[0][0] = s.x*s.x + (1 - s.x*s.x) * cos;
	matRot[0][1] = s.x*s.y * (1 - cos) + s.z*sin;
	matRot[0][2] = s.x*s.z*(1 - cos) - s.y*sin;

	matRot[1][0] = s.x*s.y*(1 - cos) - s.z*sin;
	matRot[1][1] = s.y*s.y + (1 - s.y*s.y)*cos;
	matRot[1][2] = s.y*s.z*(1 - cos) + s.x*sin;

	matRot[2][0] = s.x*s.z*(1 - cos) + s.y*sin;
	matRot[2][1] = s.y*s.z*(1 - cos) - s.x*sin;
	matRot[2][2] = s.z*s.z + (1 - s.z*s.z)*cos;

	return(matRot*ptToRot);
}



std::vector<glm::vec3> JayObjet::getSphereVertices(float rad, int meridian, int latitude)
{
	std::vector<glm::vec3> vertices;
	glm::vec3 vertex;

	glm::vec3 ptRef1, ptRef2, pt1, pt2, pt3, pt4, vectLat, vectUp;

	vectLat = glm::vec3(1.f, 0.f, 0.f);
	vectUp = glm::vec3(0.f, 1.f, 0.f);

	float latFrag = glm::radians(180.f / latitude);
	float merFrag = glm::radians(360.f / meridian);
	float latCos = glm::cos(latFrag);
	float latSin = glm::sin(latFrag);
	float merCos = glm::cos(merFrag);
	float merSin = glm::sin(merFrag);
	ptRef2 = ptRef1 = glm::vec3(0.f, -rad, 0.f);

	for (float i = 0; i < latitude; i++, ptRef1 = ptRef2)
	{
		ptRef2 = rotRodriguez(ptRef1, vectLat, latCos, latSin);

		pt1 = ptRef1;
		pt2 = ptRef2;

		for (float j = 0; j < meridian; j++, pt1 = pt4, pt2 = pt3)
		{
			pt4 = rotRodriguez(pt1, vectUp, merCos, merSin);
			pt3 = rotRodriguez(pt2, vectUp, merCos, merSin);

			vertices.push_back(pt2);
			vertices.push_back(pt1);
			vertices.push_back(pt3);

			vertices.push_back(pt4);
			vertices.push_back(pt3);
			vertices.push_back(pt1);
		}
	}

	return vertices;
}


std::vector<glm::vec3> JayObjet::getSphereNormals(int meridian, int latitude, glm::vec3 vectInit)
{
	std::vector<glm::vec3> normals;
	glm::vec3 vertex;

	glm::vec3 normalRef1, normalRef2, norm1, norm2, norm3, norm4, vectLat, vectUp;

	vectLat = glm::vec3(1.f, 0.f, 0.f);
	vectUp = glm::vec3(0.f, 1.f, 0.f);

	float latFrag = glm::radians(180.f / latitude);
	float merFrag = glm::radians(360.f / meridian);
	float latCos = glm::cos(latFrag);
	float latSin = glm::sin(latFrag);
	float merCos = glm::cos(merFrag);
	float merSin = glm::sin(merFrag);

	normalRef2 = normalRef1 = vectInit;

	for (float i = 0; i < latitude; i++, normalRef1 = normalRef2)
	{
		normalRef2 = rotRodriguez(normalRef1, vectLat, latCos, latSin);

		norm1 = normalRef1;
		norm2 = normalRef2;

		for (float j = 0; j < meridian; j++, norm1 = norm4, norm2 = norm3)
		{
			norm4 = rotRodriguez(norm1, vectUp, merCos, merSin);
			norm3 = rotRodriguez(norm2, vectUp, merCos, merSin);

			normals.push_back(norm2);
			normals.push_back(norm1);
			normals.push_back(norm3);

			normals.push_back(norm4);
			normals.push_back(norm3);
			normals.push_back(norm1);
		}
	}

	return normals;
}


std::vector<glm::vec3> JayObjet::getSphereNormals(int meridian, int latitude)
{
	return(getSphereNormals(meridian, latitude, glm::vec3(0.f, -1.f, 0.f)));
}

std::vector<glm::vec3> JayObjet::getSphereTu(int meridian, int latitude)
{
	return(getSphereNormals(meridian, latitude, glm::vec3(0.f, 0.f, 1.f)));
}

std::vector<glm::vec3> JayObjet::getSphereTv(int meridian, int latitude)
{
	return(getSphereNormals(meridian, latitude, glm::vec3(1.f, 0.f, 0.f)));
}

std::vector<glm::vec2> JayObjet::getSphereUVs(int meridian, int latitude)
{
	std::vector<glm::vec2> uvs;

	glm::vec2 texRef1, texRef2, tex1, tex2, tex3, tex4;
	float xVar = 1.f / latitude;
	float yVar = 1.f / meridian;

	texRef2 = texRef1 = glm::vec2(0.f, 0.f);

	for (float i = 0; i < latitude; i++, texRef1 = texRef2)
	{
		texRef2 = texRef1;
		texRef2.y += yVar;

		tex1 = texRef1;
		tex2 = texRef2;

		for (float j = 0; j < meridian; j++, tex1 = tex4, tex2 = tex3)
		{
			tex4 = tex1;
			tex3 = tex2;
			tex4.x += xVar;
			tex3.x += xVar;

			uvs.push_back(tex2);
			uvs.push_back(tex1);
			uvs.push_back(tex3);

			uvs.push_back(tex4);
			uvs.push_back(tex3);
			uvs.push_back(tex1);
		}
	}

	return uvs;
}

std::vector<glm::vec3> JayObjet::getCylinderVertices(float rad, float height, int meridian, int latitude)
{
	std::vector<glm::vec3> vertices;
	glm::vec3 vertex;

	glm::vec3 ptRef1, ptRef2, pt1, pt2, pt3, pt4, vectLat, vectUp;

	vectLat = glm::vec3(1.f, 0.f, 0.f);
	vectUp = glm::vec3(0.f, 1.f, 0.f);

	float latFrag = glm::radians(180.f / latitude);
	float latCos = glm::cos(latFrag);
	float latSin = glm::sin(latFrag);

	float merFrag = glm::radians(360.f / meridian);
	float merCos = glm::cos(merFrag);
	float merSin = glm::sin(merFrag);

	float halfHeight = height / 2.f;
	ptRef2 = ptRef1 = glm::vec3(rad, -halfHeight, 0.f);

	float heightStep = height / latitude;

	for (int i = 0; i < latitude; i++, ptRef1 = ptRef2)
	{
		ptRef2.y += heightStep;

		pt1 = ptRef1;
		pt2 = ptRef2;

		for (int j = 0; j < meridian; j++, pt1 = pt4, pt2 = pt3)
		{
			pt4 = rotRodriguez(pt1, vectUp, merCos, merSin);
			pt3 = rotRodriguez(pt2, vectUp, merCos, merSin);

			vertices.push_back(pt2);
			vertices.push_back(pt1);
			vertices.push_back(pt3);

			vertices.push_back(pt4);
			vertices.push_back(pt3);
			vertices.push_back(pt1);
		}
	}

	//float angleStep = 2.f * 3.14159f / meridian;

	////	Cap on Bottom
	//for (int i = 0; i < meridian; ++i)
	//{		
	//	vertices.push_back(glm::vec3(0.f, -halfHeight, 0.f));
	//	vertices.push_back(glm::vec3(rad * cos(angleStep*i), -halfHeight, rad * sin(angleStep*i)));
	//	vertices.push_back(glm::vec3(rad * cos(angleStep*(i+1)), -halfHeight, rad * sin(angleStep*(i + 1))));
	//}

	////	Cap on top
	//for (int i = 0; i < meridian; ++i)
	//{
	//	vertices.push_back(glm::vec3(0.f, halfHeight, 0.f));
	//	vertices.push_back(glm::vec3(rad * cos(-angleStep*i), halfHeight, rad * sin(-angleStep*i)));
	//	vertices.push_back(glm::vec3(rad * cos(-angleStep*(i + 1)), halfHeight, rad * sin(-angleStep*(i + 1))));
	//}

	return vertices;
}


std::vector<glm::vec3> JayObjet::getCylinderNormals(int meridian, int latitude, glm::vec3 vectInit)
{
	std::vector<glm::vec3> normals;
	glm::vec3 vertex;
	glm::vec3 normal;

	glm::vec3 normRef1, norm1, norm2, norm3, norm4, vectLat, vectUp;

	vectLat = glm::vec3(1.f, 0.f, 0.f);
	vectUp = glm::vec3(0.f, 1.f, 0.f);

	float latFrag = glm::radians(180.f / latitude);
	float latCos = glm::cos(latFrag);
	float latSin = glm::sin(latFrag);

	float merFrag = glm::radians(360.f / meridian);
	float merCos = glm::cos(merFrag);
	float merSin = glm::sin(merFrag);

	normRef1 = vectInit;

	for (float i = 0; i < latitude; i++)
	{
		norm1 = normRef1;
		norm2 = normRef1;

		for (float j = 0; j < meridian; j++, norm1 = norm4, norm2 = norm3)
		{
			norm4 = rotRodriguez(norm1, vectUp, merCos, merSin);
			norm3 = rotRodriguez(norm2, vectUp, merCos, merSin);

			normals.push_back(norm2);
			normals.push_back(norm1);
			normals.push_back(norm3);

			normals.push_back(norm4);
			normals.push_back(norm3);
			normals.push_back(norm1);
		}
	}

	//float angleStep = 2.f * 3.14159f / meridian;

	////	Cap on Bottom
	//normal = glm::vec3(0.f, -1.f, 0.f);
	//for (int i = 0; i < meridian; ++i)
	//{
	//	normals.push_back(normal);
	//	normals.push_back(normal);
	//	normals.push_back(normal);
	//}

	////	Cap on top
	//normal = glm::vec3(0.f, 1.f, 0.f);
	//for (int i = 0; i < meridian; ++i)
	//{
	//	normals.push_back(normal);
	//	normals.push_back(normal);
	//	normals.push_back(normal);
	//}

	return normals;
}


std::vector<glm::vec3> JayObjet::getCylinderNormals(int meridian, int latitude) {
	return(getCylinderNormals(meridian, latitude, glm::vec3(1.f, 0.f, 0.f)));
}

std::vector<glm::vec3> JayObjet::getCylinderTu(int meridian, int latitude) {
	return(getCylinderNormals(meridian, latitude, glm::vec3(0.f, 1.f, 0.f)));
}

std::vector<glm::vec3> JayObjet::getCylinderTv(int meridian, int latitude) {
	return(getCylinderNormals(meridian, latitude, glm::vec3(0.f, 0.f, -1.f)));
}

std::vector<glm::vec2> JayObjet::getCylinderUVs(int meridian, int latitude)
{
	std::vector<glm::vec2> uvs;

	glm::vec2 uv;

	float xVar = 1.f / meridian;
	float yVar = 1.f / latitude;

	glm::vec2 uvRef1, uvRef2, uv1, uv2, uv3, uv4;
	uvRef2 = uvRef1 = glm::vec2(0.f, 0.f);

	for (float i = 0; i < latitude; i++, uvRef1 = uvRef2)
	{
		uvRef2.y += yVar;

		uv1 = uvRef1;
		uv2 = uvRef2;

		for (float j = 0; j < meridian; j++, uv1 = uv4, uv2 = uv3)
		{
			uv4 = uv1;
			uv3 = uv2;

			uv4.x += xVar;
			uv3.x += xVar;

			uvs.push_back(uv2);
			uvs.push_back(uv1);
			uvs.push_back(uv3);

			uvs.push_back(uv4);
			uvs.push_back(uv3);
			uvs.push_back(uv1);
		}
	}

	return uvs;
}



std::vector<glm::vec3> justchangethebase(std::vector<glm::vec3> base, std::vector<glm::vec3> toAdd, float multiplier)
{
	std::vector<glm::vec3> normals;

	for (unsigned int i = 0; i < base.size() && i < toAdd.size(); i++)
	{
		normals.push_back(base[i] + toAdd[i] * multiplier);
	}

	return normals;
}

std::vector<glm::vec3> addTo(std::vector<glm::vec3> This, std::vector<glm::vec3> andThis)
{
	std::vector<glm::vec3> adds;

	for (unsigned int i = 0; i < This.size(); i++)
	{
		adds.push_back(This[i]);
	}
	for (unsigned int i = 0; i < andThis.size(); i++)
	{
		adds.push_back(andThis[i]);
	}

	return adds;
}

std::vector<glm::vec3> JayObjet::getNormalPerVertex(std::vector<glm::vec3> base, std::vector<glm::vec3> toAdd, float multiplier) {
	std::vector<glm::vec3> normals;

	for (unsigned int i = 0; i < base.size() && i < toAdd.size(); i++)
	{
		normals.push_back(base[i]);
		normals.push_back(base[i] + toAdd[i] * multiplier);
	}

	return normals;
}
void JayObjet::BuildQuadForGraphicCalculations()
{

}


void JayObjet::CopyVectexes(vector<glm::vec3>)
{
	vertices.clear();
	normals.clear();
	tus.clear();
	tvs.clear();
	texCoords.clear();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices.push_back(vertices[i]);
		normals.push_back(normals[i]);
		tus.push_back(tus[i]);
		tvs.push_back(tvs[i]);
		texCoords.push_back(texCoords[i]);
	}
	UpdateIDs();
}