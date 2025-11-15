#pragma once



/*****************************************\
 MachineLearning.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>
#include <Epoch.h>

#include "../Eigen/Dense"

using namespace Eigen;


class MachineLearning
{
    //  Text en format Opengl pr�t � �tre affich�
public :
    MachineLearning();
	~MachineLearning();
    
    vector<Epoch> epochs; 
    vector<MatrixXd> Weights;    
    vector<vector<float>> outPutResults;

    int epochSelected;

private:
};