#pragma once



/*****************************************\
 Epoch.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>
#include <NN.h>

class Epoch : public NN
{
    //  Text en format Opengl pr�t � �tre affich�
public :
    Epoch();
	~Epoch();
    
private:
    int nbParametsrs;
    int nbOutputs;
    int nbTrainingItems;

    int nbNeurons;
    int nbLayers;
    int totalWeights;

};