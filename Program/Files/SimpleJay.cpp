


#include "SimpleJay.h"


SimpleJay::SimpleJay(vector<glm::vec3> newVertices)
{
	Init();
	vectices = newVertices;
	UpdateIDs();
}


SimpleJay::~SimpleJay()
{

}


void SimpleJay::Init()
{
	glGenVertexArrays(1, &ArrayID);
	glGenBuffers(1, &buffer);
}


void SimpleJay::UpdateIDs()
{
	assert(vectices.size() != 0);

	glBindVertexArray(ArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(glm::vec3), &vectices[0], GL_STATIC_DRAW);
}

void SimpleJay::Draw()
{
	assert(vectices.size() != 0);

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

	glDrawArrays(GL_LINES, 0, vectices.size());
	glBindVertexArray(0);

	glDisableVertexAttribArray(0);
}


void SimpleJay::UpdateWith(vector<glm::vec3> newvectices)
{
	vectices = newvectices;
	UpdateIDs();
}
