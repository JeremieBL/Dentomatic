#pragma once



/*****************************************\
 NN.h
 ***** Par Jérémie Béliveau-Lefebvre *****
 Initialisé le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>

#include "../Eigen/Dense"

using namespace Eigen;

class NN
{
    //  Text en format Opengl prêt à être affiché
public :
    NN();
	~NN();
    
    MatrixXd initWeights(int, int);
    Vector2f Predict(int, int, int, int, MatrixXd);

    void forwardLayer(int actualLayer);
    void forward();
    void backPropagation();
    void backPropagationLayer(int actualLayer);
   
    VectorXf parameters;
    VectorXf outPuts;
private:
};