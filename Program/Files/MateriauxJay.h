#pragma once

#include "glm/glm.hpp"
#include "emlist.h"
#include "Shader.h"

class MateriauxJay {
public:
	/// <summary>
	/// ////////// List of shaders for the material
	/// </summary>
	emlist<GLint> shaderIDList; // List of shaders for materials
	emlist<GLint>::iterator itshaderID;

	GLint Bind(GLint newShaderID);

	/// <summary>
	/// ////////// Activation of the material	
	/// </summary>
	bool active = true;

	bool IsActive() { return active; };
	bool ToggleActivation() { active = !active; return active; };
	bool SetActive(bool newActive) { active = newActive; return active; };


public:
	MateriauxJay();
	MateriauxJay(GLint newShaderID);
	~MateriauxJay();
};
