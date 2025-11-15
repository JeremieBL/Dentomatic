


/*****************************************\
 TrainingTexture.cpp
 ***** Par Jérémie Béliveau-Lefebvre *****
 Initialisé le 8 avril 2021
\*****************************************/



#include "TrainingTexture.h"


TrainingTexture::TrainingTexture()
{
}


TrainingTexture::~TrainingTexture()
{

}

ShaderTexture TrainingTexture::MatrixToTexture()
{


    return textureToWriteTo;
}

 MatrixXd TrainingTexture::TextureToMatrix()
{

     return tex;
}


