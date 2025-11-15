

/*****************************************\
 Environnement.cpp
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/


#include "NN.h"


NN::NN()
{
}


NN::~NN()
{

}


MatrixXd NN::initWeights(int x, int y)
{
    MatrixXd weights(x, y);

    weights.setRandom();

  //  weights = abs(weights);

    return weights;
}


Vector2f NN::Predict(int nbParams, int nbNeurons, int nbLayers, int nbOutputs, MatrixXd weights)
{
    Vector2f ouputs(nbOutputs);


    return ouputs;
}


void NN::forwardLayer(int actualLayer)
{
};


void NN::forward()
{
};


void NN::backPropagation()
{
};


void NN::backPropagationLayer(int actualLayer)
{
};

