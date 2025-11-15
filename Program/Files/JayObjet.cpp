

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
};


JayObjet::JayObjet(GLenum newmode, vector<glm::vec3> newPoints) : mode(newmode), vertices(newPoints)
{
};

JayObjet::~JayObjet()
{
	Clean();
}

void JayObjet::Init(int newShader) {
	shader = newShader;
}

void JayObjet::Init() {
	isInit = true;
	glGenVertexArrays(1, &vertexArrayID);
}

void JayObjet::DeclareObjet() {
	Init();
}

void JayObjet::Clean() {

	if (isInit) glDeleteVertexArrays(1, &vertexArrayID);
	if (isvbo) glDeleteBuffers(1, &vertexBufferID);
	if (isnbo) glDeleteBuffers(1, &normalBufferID);
	if (isuvbo) glDeleteBuffers(1, &uvBufferID);
	if (istubo) glDeleteBuffers(1, &tangentU_BufferID);
	if (istvbo) glDeleteBuffers(1, &tangentV_BufferID);
	if(isindbo) glDeleteBuffers(1, &indicesBufferID);
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

	if(!isInit) {
		Init();
	}

	glBindVertexArray(vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	int in_PositionLocation = glGetAttribLocation(shader, "in_Position");
	glEnableVertexAttribArray(in_PositionLocation);
	glVertexAttribPointer(in_PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


	if (isnbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

		int in_NormalLocation = glGetAttribLocation(shader, "in_Normal");
		glEnableVertexAttribArray(in_NormalLocation);
		glVertexAttribPointer(in_NormalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (isuvbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);

		int in_NormalLocation = glGetAttribLocation(shader, "in_UVs");
		glEnableVertexAttribArray(in_NormalLocation);
		glVertexAttribPointer(in_NormalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istubo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tangentU_BufferID);
		glBufferData(GL_ARRAY_BUFFER, tus.size() * sizeof(glm::vec3), &tus[0], GL_STATIC_DRAW);

		int in_TuLocation = glGetAttribLocation(shader, "in_Tv");
		glEnableVertexAttribArray(in_TuLocation);
		glVertexAttribPointer(in_TuLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istvbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tangentV_BufferID);
		glBufferData(GL_ARRAY_BUFFER, tvs.size() * sizeof(glm::vec3), &tvs[0], GL_STATIC_DRAW);

		int in_TvLocation = glGetAttribLocation(shader, "in_Tv");
		glEnableVertexAttribArray(in_TvLocation);
		glVertexAttribPointer(in_TvLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}


	//if (istbo)
	//{
	//	glBindBuffer(GL_ARRAY_BUFFER, tangentBufferID);
	//	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

	//	int in_TexCoordLocation = glGetAttribLocation(shader, "in_TexCoord");
	//	glEnableVertexAttribArray(in_TexCoordLocation);
	//	glVertexAttribPointer(in_TexCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//}
}

void JayObjet::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	//// Get the locations of uniforms
	//int projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");
	//int viewMatrixLocation = glGetUniformLocation(shader, "viewMatrix");
	//int modelMatrixLocation = glGetUniformLocation(shader, "modelMatrix");
	//int modelViewLocation = glGetUniformLocation(shader, "modelView");
	//int normalMatrixLocation = glGetUniformLocation(shader, "normalMatrix");

	//// Copy data to the GPU
	//glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	//glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	//modelView = viewMatrix * modelMatrix;
	//glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
	//normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));
	//glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, &normalMatrix[0][0]);


	Draw();
}



void JayObjet::Draw() {

	//  Pour les 4 prochains paragraphes, je ne suis pas d'accord pcq ça implique de rechercher dans le shader, alors qu'ici, ça n'a pas sa place.
	//  On est dans l'affichage, alors on est supposé avoir déclaré les shader et on est supposé avoir transféré les vertices déjà.
	//	On est juste supposé appeler les regroupement qu'on a déjà uploadés. 

	//if (isMaterial)
	//{
	//	int materialKaLocation = glGetUniformLocation(shader, "materialKa");
	//	int materialKdLocation = glGetUniformLocation(shader, "materialKd");
	//	int materialKsLocation = glGetUniformLocation(shader, "materialKs");
	//	int materialShininessLocation = glGetUniformLocation(shader, "materialShininess");

	//	glUniform3f(materialKaLocation, materials.ambient[0], materials.ambient[1], materials.ambient[2]);
	//	glUniform3f(materialKdLocation, materials.diffuse[0], materials.diffuse[1], materials.diffuse[2]);
	//	glUniform3f(materialKsLocation, materials.specular[0], materials.specular[1], materials.specular[2]);
	//	glUniform1f(materialShininessLocation, materials.shininess);
	//}

	//if (isColorTexture)
	//{
	//	// Draw our object
	//	GLint colorTex_uniform_loc = glGetUniformLocation(shader, "colorTexture");
	//	glUniform1i(colorTex_uniform_loc, 0);
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, textureColorID);
	//}

	//if (heightTexture)
	//{
	//	GLint dispTex_uniform_loc = glGetUniformLocation(shader, "heightTexture");
	//	glUniform1i(dispTex_uniform_loc, 1);
	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, textureHeightID);
	//}

	//if (bumpTexture)
	//{
	//	GLint bumpTex_uniform_loc = glGetUniformLocation(shader, "bumpTexture");
	//	glUniform1i(bumpTex_uniform_loc, 2);
	//	glActiveTexture(GL_TEXTURE2);
	//	glBindTexture(GL_TEXTURE_2D, textureBumpID);
	//}

	int attribRank = 0;
	glBindVertexArray(vertexArrayID);


	if (isvbo)
	{
		glEnableVertexAttribArray(vertatt);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer((GLuint)vertatt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	if (isnbo)
	{
		glEnableVertexAttribArray(normatt);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID); //	normalBufferID
		glVertexAttribPointer((GLuint)normatt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (isuvbo)
	{
		glEnableVertexAttribArray(uvsatt);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID); //	uvBufferID
		glVertexAttribPointer((GLuint)uvsatt, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istubo)
	{
		glEnableVertexAttribArray(tanUatt);
		glBindBuffer(GL_ARRAY_BUFFER, tangentU_BufferID);
		glVertexAttribPointer((GLuint)tanUatt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (istvbo)
	{
		glEnableVertexAttribArray(tanVatt);
		glBindBuffer(GL_ARRAY_BUFFER, tangentV_BufferID);
		glVertexAttribPointer((GLuint)tanVatt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);



	if (!isindbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		// Draw the triangle ! ////		Grossière erreur! On est supposé avoir déjà uploadé les points dans le GPU!
		glDrawArrays(verticesMode, 0, vertices.size()); // 12*3 indices starting at 0 -> 12 triangles
	}
	else
	{
		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);

		// Draw the triangles !
		glDrawElements(
			indsMode,      // mode
			_indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);
	}


	glBindVertexArray(0);
	
}

void JayObjet::DumpTheseDatasIntoBufferForGPU(vector<glm::vec2> newData, GLenum newmode, TypeData pos, GLint newAttPos) {

	if (!isInit)
		Init();

	glBindVertexArray(vertexArrayID);

	switch (pos) {
	case TypeData::uvs:
		uvs = newData;
		isuvbo = true;
		uvsMode = newmode;
		uvsatt = newAttPos;

		glGenBuffers(1, &uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

		//glGenBuffers(1, &uvbufferR2T);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbufferR2T);
		//glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);


		//uvsatt = maxAttributeToEnable;
		//glVertexAttribPointer((GLuint)uvsatt, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(uvsatt);
		//maxAttributeToEnable++;
		break;

		//glGenBuffers(1, &uvbufferR2T);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbufferR2T);
		//glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	default:
		break;
	}
	glBindVertexArray(0);

}

void JayObjet::DumpTheseDatasIntoBufferForGPU(vector<unsigned short> newData, GLenum newmode, TypeData pos)
{
	if (!isInit)
		Init();
//	bool isindbo = false;
//	unsigned int indicesBufferID = 0;

	glBindVertexArray(vertexArrayID);

	switch (pos) {
	case TypeData::indices:
		_indices = newData;
		isindbo = true;
		indsMode = newmode;


		glGenBuffers(1, &indicesBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned short), &_indices[0], GL_STATIC_DRAW);
		//indatt = maxAttributeToEnable;
		//glVertexAttribPointer((GLuint)maxAttributeToEnable, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(maxAttributeToEnable);
		//maxAttributeToEnable++;
			// Index buffer

		//	Je penses que c'est ici que ça va.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);

		break;
	default:
		break;
	}
	glBindVertexArray(0);

}

void JayObjet::DumpTheseDatasIntoBufferForGPU(vector<glm::vec3> newData, GLenum newmode, TypeData pos, GLint newAttPos) {
	
	if (!isInit)
		Init();

	glBindVertexArray(vertexArrayID);

	switch (pos) {
	case TypeData::vertices:
		vertices = newData;
		isvbo = true;
		verticesMode = newmode;
		vertatt = newAttPos;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		//vertatt = maxAttributeToEnable;
		//glVertexAttribPointer((GLuint)maxAttributeToEnable, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(maxAttributeToEnable);
		//maxAttributeToEnable++;

		break;

	case TypeData::normals:
		normals = newData;
		isnbo = true;
		normalsMode = newmode;
		normatt = newAttPos;

		glGenBuffers(1, &normalBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);


		//glGenBuffers(1, &normalBufferID);
		//glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
		//normatt = maxAttributeToEnable;
		//glVertexAttribPointer((GLuint)maxAttributeToEnable, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(maxAttributeToEnable);
		//maxAttributeToEnable++;
		break;

	case TypeData::Utangents:
		tvs = newData;
		istubo = true;
		tusMode = newmode;
		tanUatt = newAttPos;

		glGenBuffers(1, &tangentU_BufferID); 
		glBindBuffer(GL_ARRAY_BUFFER, tangentU_BufferID);
		glBufferData(GL_ARRAY_BUFFER, tvs.size() * sizeof(glm::vec3), &tvs[0], GL_STATIC_DRAW);
		tanUatt = maxAttributeToEnable;
		glVertexAttribPointer((GLuint)maxAttributeToEnable, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(maxAttributeToEnable);
		maxAttributeToEnable++;
		break;

	case TypeData::Vtangents:
		tvs = newData;
		istvbo = true;
		tvsMode = newmode;
		tanVatt = newAttPos;

		glGenBuffers(1, &tangentV_BufferID); 
		glBindBuffer(GL_ARRAY_BUFFER, tangentV_BufferID);
		glBufferData(GL_ARRAY_BUFFER, tvs.size() * sizeof(glm::vec3), &tvs[0], GL_STATIC_DRAW);
		tanVatt = maxAttributeToEnable;
		glVertexAttribPointer((GLuint)maxAttributeToEnable, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(maxAttributeToEnable);
		maxAttributeToEnable++;
		break;
	default:
		break;
	}

	glBindVertexArray(0);
}

void JayObjet::Display() {
	if (!active) return ;
	assert(isvbo || isindbo);
	assert(ptrShader != nullptr);


	//if (ptrShader->isMultiPass) {
	//	for (itshaderID = ptrShader->shaderIDList.begin(); itshaderID != ptrShader->shaderIDList.before_begin() && itshaderID != ptrShader->shaderIDList.end(); itshaderID++)
	//	{
	//		(*itshaderID)->second.UsePrePass();
	//		(*itshaderID)->second.UseProgram();
	//		(*itshaderID)->second.PassMatrixes();
	//		Draw();
	//		//	(*itshaderID)->second.EndProgram();		//	Pointless since we will use other shader right after
	//		(*itshaderID)->second.RestaureAfterPrePass();
	//	}		
	//}

	ptrShader->UseProgram();

	ptrShader->PassMatrixes();
	ptrShader->PassVariables(this);

	Draw();

	ptrShader->EndProgram();
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
				vertex.x = xpos; vertex.y = -0.f; vertex.z = zpos;					vertices.push_back(vertex); normals.push_back(normal); tus.push_back(tu); tvs.push_back(tv); texCoords.push_back(glm::vec2(uvx, uvy));
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

	int in_PositionLocation = glGetAttribLocation(shader, "in_Position");
	glEnableVertexAttribArray(in_PositionLocation);
	glVertexAttribPointer(in_PositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void JayObjet::DrawNormals(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	glUseProgram(shader);	// bind shader
					//int lightPosLocation = glGetUniformLocation(shader, "lightPosition");
					//glUniform4f(lightPosLocation, light.position[0], light.position[1], light.position[2], 0.f);

	glm::mat4 normalMat = glm::mat4(1.0f);

	// Get the locations of uniforms
	int projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");
	int viewMatrixLocation = glGetUniformLocation(shader, "viewMatrix");
	int modelMatrixLocation = glGetUniformLocation(shader, "modelMatrix");
	int modelViewLocation = glGetUniformLocation(shader, "modelView");
	int normalMatrixLocation = glGetUniformLocation(shader, "normalMatrix");

	int materialKdLocation = glGetUniformLocation(shader, "materialKd");

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

	glBindVertexArray(0);

	glUseProgram(0); // Unbind shader}
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

void JayObjet::CalculateSmoothShading() {
	/* 
	#include <vector>
#include <map>
#include <glm/glm.hpp>  // Assuming GLM library for vector math

// Structure to hold the optimized mesh with indices and smooth normals
struct OptimizedMesh {
    std::vector<glm::vec3> vertices;  // Unique vertices
    std::vector<unsigned int> indices;  // Triangle indices (every 3 form a triangle)
    std::vector<glm::vec3> normals;   // Per-vertex smooth normals

    // Structure for vertex-to-triangle adjacency: list of triangle indices per vertex
    std::vector<std::vector<size_t>> vertexToTriangles;  // vertexToTriangles[vert_index] = list of triangle indices (0-based, where triangle_index = face_id)
};

// Function to optimize vertices by deduplicating, build indices, and compute smooth shading normals.
// Input: input_vertices - flat list of glm::vec3, every 3 consecutive form a triangle.
// Assumes exact floating-point equality for deduplication; in practice, consider tolerance for floats.
OptimizedMesh optimizeAndComputeSmoothNormals(const std::vector<glm::vec3>& input_vertices) {
    OptimizedMesh mesh;

    // Ensure input is multiple of 3
    if (input_vertices.size() % 3 != 0) {
        // Handle error: invalid input
        return mesh;
    }

    size_t num_triangles = input_vertices.size() / 3;

    // Map to track unique vertices and their indices
    std::map<glm::vec3, unsigned int> unique_vertex_map;
    unsigned int next_index = 0;

    // Temporary list to compute per-face normals
    std::vector<glm::vec3> face_normals(num_triangles, glm::vec3(0.0f));

    // Build unique vertices, indices, and face normals
    for (size_t i = 0; i < input_vertices.size(); i += 3) {
        const glm::vec3& A = input_vertices[i];
        const glm::vec3& B = input_vertices[i + 1];
        const glm::vec3& C = input_vertices[i + 2];

        // Compute face normal
        glm::vec3 AB = B - A;
        glm::vec3 AC = C - A;
        glm::vec3 N = glm::cross(AB, AC);
        if (glm::length(N) > 0.0f) {
            N = glm::normalize(N);
        }
        size_t triangle_index = i / 3;
        face_normals[triangle_index] = N;

        // Add vertices to unique map and build indices
        for (size_t j = 0; j < 3; ++j) {
            const glm::vec3& v = input_vertices[i + j];
            auto it = unique_vertex_map.find(v);
            if (it == unique_vertex_map.end()) {
                unique_vertex_map[v] = next_index;
                mesh.vertices.push_back(v);
                mesh.indices.push_back(next_index);
                ++next_index;
            } else {
                mesh.indices.push_back(it->second);
            }
        }
    }

    // Now build vertexToTriangles adjacency
    mesh.vertexToTriangles.resize(mesh.vertices.size());
    for (size_t tri = 0; tri < num_triangles; ++tri) {
        unsigned int idx0 = mesh.indices[tri * 3];
        unsigned int idx1 = mesh.indices[tri * 3 + 1];
        unsigned int idx2 = mesh.indices[tri * 3 + 2];

        mesh.vertexToTriangles[idx0].push_back(tri);
        mesh.vertexToTriangles[idx1].push_back(tri);
        mesh.vertexToTriangles[idx2].push_back(tri);
    }

    // Compute smooth normals: average face normals for each vertex's adjacent triangles
    mesh.normals.resize(mesh.vertices.size(), glm::vec3(0.0f));
    for (size_t vert = 0; vert < mesh.vertices.size(); ++vert) {
        const auto& tris = mesh.vertexToTriangles[vert];
        if (tris.empty()) continue;

        glm::vec3 sum_normal(0.0f);
        for (size_t t : tris) {
            sum_normal += face_normals[t];
        }
        glm::vec3 avg_normal = sum_normal / static_cast<float>(tris.size());
        if (glm::length(avg_normal) > 0.0f) {
            avg_normal = glm::normalize(avg_normal);
        }
        mesh.normals[vert] = avg_normal;
    }

    return mesh;
}
*/
}

void JayObjet::CalculateFlatShading() {

	// Ensure the number of vertices is a multiple of 3
	assert(vertices.size() % 3 == 0);
	normals.clear();
	normals.resize(vertices.size());

	for (size_t i = 0; i < vertices.size(); i += 3) {
		const glm::vec3& A = vertices[i];
		const glm::vec3& B = vertices[i + 1];
		const glm::vec3& C = vertices[i + 2];

		glm::vec3 AB = B - A;
		glm::vec3 BC = C - B;
		glm::vec3 N = glm::cross(AB, BC);

		// Normalize the normal vector if it's not zero
		if (glm::length(N) > 0.0f) {
			N = glm::normalize(N);

		}

		// Assign the same normal to all three vertices of the triangle
		normals[i] = N;
		normals[i + 1] = N;
		normals[i + 2] = N;
	}
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

unordered_map<string, ShaderJay>::iterator JayObjet::Bind(unordered_map<string, ShaderJay>::iterator newShaderID) {
	itshaderID = shaderIDList.push_back(newShaderID);
	ptrShader = &(*itshaderID)->second;
	return (itShaderLinked = *itshaderID);
}

ToolObjet::ToolObjet() {

}

ToolObjet::~ToolObjet() {

}

