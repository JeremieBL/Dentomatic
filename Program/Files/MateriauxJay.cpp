#include "MateriauxJay.h"

MateriauxJay::MateriauxJay() {

}
MateriauxJay::MateriauxJay(GLint newShaderID) {
	Bind(newShaderID);
}

MateriauxJay::~MateriauxJay()
{

}

GLint MateriauxJay::Bind(GLint newShaderID) {
	itshaderID = shaderIDList.push_back(newShaderID);
	return *itshaderID;
}