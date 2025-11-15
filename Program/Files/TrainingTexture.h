#pragma once



/*****************************************\
 TrainingTexture.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>
#include <CameraJay.h>
#include <ShaderTexture.h>

#include "../Eigen/Dense"

using namespace Eigen;

class TrainingTexture
{
    //  Textures qui servent � s'entrainer dans un shader
public :
	TrainingTexture();
	~TrainingTexture();
    
    ShaderTexture MatrixToTexture();
    MatrixXd TextureToMatrix();

private:
    MatrixXd tex;      //   Ex notre NN de 100 x (100x100)
    ShaderTexture textureToWriteTo;
};