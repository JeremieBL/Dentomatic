#pragma once

#include "glm/glm.hpp"

class LightJay {
public:
	bool enabled = false;
	bool directional = true;
	glm::vec3 dir = glm::vec3(-1.0f, -1.0f, -1.0f); // Direction for directional light
	glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f); // Position for point light
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Color of the light

public:
	LightJay();
	~LightJay();

	void Init();
	void SetPosition(float x, float y, float z);
	void SetColor(float r, float g, float b, float a);
	void Enable();
	void Disable();

	void SetDirection(float x, float y, float z);
	glm::vec3 GetDirection()const;
	glm::vec3 GetPosition()const;
	bool IsEnabled() const;

	glm::vec3 GetColor() const;
	void SetEnabled(bool enable);
	void SetDirectional(bool isDirectional);
	bool IsDirectional() const;
};