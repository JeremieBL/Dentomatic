#pragma once
#include <string>
#include "vector"

using namespace std;

class ShaderTexture
{
private:
public:
	unsigned int textureRef;

	string name;

	ShaderTexture();
	ShaderTexture(string s1, int sizeX, int sizeY, const void* first);
	ShaderTexture(string, int, int);
	~ShaderTexture();

	void DeleteTexture();

	void BindTexture(string);
};
