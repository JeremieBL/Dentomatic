
#include "ShaderTexture.h"
#include "JayObjet.h"

ShaderTexture::ShaderTexture(string s1, int sizeX, int sizeY, const void* first)
{
	glGenTextures(1, &textureRef);

	glBindTexture(GL_TEXTURE_2D, textureRef);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, sizeX, sizeY);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sizeX, sizeY, GL_RED, GL_FLOAT, first);
	glBindTexture(GL_TEXTURE_2D, 0);
}

ShaderTexture::ShaderTexture(string newName, int sizeX, int sizeY)
{
	name = newName;
	glGenTextures(1, &textureRef);

	glBindTexture(GL_TEXTURE_2D, textureRef);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, sizeX, sizeY);
	//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32, MT_total_width, MT_total_height);
	glBindTexture(GL_TEXTURE_2D, 0);
}


ShaderTexture::ShaderTexture() : textureRef(0)
{

}

ShaderTexture::~ShaderTexture()
{

}

void ShaderTexture::DeleteTexture()
{
	glDeleteTextures(1, &textureRef);
}

void ShaderTexture::BindTexture(string s1)
{
	glGenTextures(1, &textureRef);

}
