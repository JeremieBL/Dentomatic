
#pragma once

/*****************************************\
 Viewer.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>
#include "CameraJay.h"
#include "ShaderTexture.h"
#include "TrainingTexture.h"
#include "MultipleJays.h"
#include "emlist.h"

#include "Text.h"

class ViewerJay
{
	//	D�finit ce qui sera visible
	//	D�finit comment ce sera visualis�

public :
	ViewerJay();
	~ViewerJay();

	void push_backSubViewer(ViewerJay newSubviewer);
	void Display();

	void NewObject(MultipleJays newobject);

private:

	//	emlist<CameraJay> camera;						//	Caract�ristiques matriciels des points de vue
	enum class RenderType { localview = 0, raytracingview = 1, renderedtextureview = 2, trainingtextureview = 3};
	RenderType renderType = RenderType::localview;

	ShaderTexture textureToRender;		//	D�signe si sera mi en texture lors de l'�x�cusion
	TrainingTexture trainingTexture;	//	Texture d'une matrice � afficher pour cette vue, sera principalement 
										//	2 matrices.
	//	Non, pas ça. C'est l'environnement qui contient les vues et non l'inverse.
	//	Y a t-il des situations ou une vue contiendrait plusieurs environnement?
	//	Dans un mode d'édition, il peut y avoir plusieurs représentation de plusieurs vue de différentes manières dans une même vue,
	//  mais c'est à l'environnement au controleur principal du projet à gérer ça. Qqch d'autre peu gérer ça? Che pas.
	//	Environnement environnement;		//	L'environnement � faire un rendu

	//	vector<ViewerJay> subViewers;
	vector<glm::vec4> pvPositions;		//	D�termine les 2 coins minimums et maximums de la position des points de vues

	//Shader shader;						//	Shader � utiliser pour cette vue
		
	vector<Text> text;	//	Si on a le temps				//	Contient les text d'affichage � afficher
	vector<glm::vec4> textPosition;	//	Si on a le temps	//	Contient les 2 coins des textures � afficher.

	vector<float> textScale;			//	D�finit la dimension du text d'affichage
};