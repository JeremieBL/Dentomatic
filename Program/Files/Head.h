#pragma once


//
//
//
//
///*
/////////////////			Things to do		\\\\\\\\\\\\\\\\\\\\\\
//
//Baking time :
//-	Les helpers pour les fl�ches, les afficher, les s�lectionner, les utiliser
//-	Les helpers en g�n�ral, les s�lectionner, les modifier, leur utilit�
//===	Faire les modifications rotation et scale comme translation		//	Sauf que �a fait des d�fauts lors d'application des modifications � l'occasion :(
//-	Les terrains, faire le s�lecteur de points, bumping etc.
//-	Appliquer des textures par le s�lecteur de points bump
//-	Mettre le s�lecteur de couleurs dans la barre de droite
//-	Actualiser les lumi�res pour un plus bel �clairage
//-	Appliquer la dynamique, par les sph�re, les cylindres, les points et les faces.
//-	Faire l��diteur de jeux
//-	Faire la continuit� des projected pattern.
//-	Deleter PP, ses Pt et GpPt
//-	Ajouter des membres � PP
//-	Recopier les membres � PP
//-	Faire les armes par PP
//-	Faire les v�hicules par PP
//-	Faire les terrains par PP
//-	Fonction d�extrusion
//-	Fonction d�extrusion-rotation
//-	Fonction boolean
//-	Les objets fog
//-	Les objets fum�es
//-	Ajouter des os dans PP
//-	Linker les points de la skin/des objets ajout�s
//-	Appliquer des FrameWorks aux os/objets
//-	Faire l��dition des tableaux
//-	D�finir les triggers
//-	Faire l��dition des games
//-
//
//
//
//
//
//*/
//
//
//
//
///*
//
//
//opengl32.lib
//glu32.lib
//glew32.lib
//glfw3.lib
//SOIL.lib
//
//
//GLaux.lib
//glut32.lib
//
//
//kernel32.lib
//user32.lib
//gdi32.lib
//winspool.lib
//comdlg32.lib
//advapi32.lib
//shell32.lib
//ole32.lib
//oleaut32.lib
//uuid.lib
//odbc32.lib
//odbccp32.lib
//*/
//
//
//
//
//
//#include <windows.h>	
//#include <fbxsdk.h>
//
//#include "SDK_Utility.h"
//
//#include "Matrices.h"
//
//#include <GL/glew.h>
////Include GLFW
//#include <GLFW/glfw3.h>
//
////#include <GL/freeglut.h>
//
////#include "glApplication.cpp"
////	#include "glWindow.cpp"
//#include "glApplication.cpp"
//#include "glutWindow.h"
////#include "glutWindow.cpp"
//#include "glsl.cpp"
//
////	#ifdef WIN32
////#include <fileapi.h>
//
//
////	using namespace System;
//
////	#endif
//
//#include <algorithm>
//#include <cassert>
//#include <time.h>
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
//#include <cstring>
//#include <string>
//#include <stdio.h>
//#include <stdint.h>
//#include <winuser.h>
//#include <windowsx.h>
//#include <winsock.h>
//#include <GL\gl.h>
//#include <GL\glut.h>
//#include <GL\glu.h> 
//#include <GL\glaux.h>
//#include <cmath>
//#include <limits>
//#include <cctype>
//#include <assert.h>
//#include <sstream>
//#include "texture.h"
//
//
//#inlude "ICONS.C"
//	<ICON FILENAME="Sudoku.ico"/>

//#include "myWindow.h"
//
//#include <MMSystem.h>
//	#inlude "Script4.rc"

//#inlude "PPrim.ico"

#define  GLUT_NONE_BUTTON                   0x0000
//#define None		0

#define	PI		3.1415926535897932384626433832795f
#define PI180	0.0174532925199432957692369076848861f	// pi / 180

#define Degree_Rad 180/PI

#define EPSILON 1.0e-8

#define ZERO EPSILON

#define t_24 1.0/24
#define t_30 1.0/30

#define ColRadRouge		PI/2
#define ColRadBleu		PI*7/6
#define ColRadVerte		PI*11/6

int OpenGLWidhtDisplay = 1920;
int OpenGLHeightDisplay = 1080;


int LargeurWindowsForms = 1305;
int HauteurWindowsForms = 766;

int LARGEUR_ECRAN = LargeurWindowsForms - 225;
int HAUTEUR_ECRAN = HauteurWindowsForms - 146;

int initXdisplay = 0;
int initYdisplay = 97;

int CurrentPosX, CurrentPosY;

using namespace std;

/// this will hold the openGL texture object for the loaded texture
unsigned int g_Texture = 0;

/// the position of the object
float position[2] = { 0,0 };




//
//
//
//float& _regulate(float& Num)
//{
//	if (Num < Max_Min && Num > Min_Min)	Num = 0.0;
//
//	return Num;
//
//};
//


//
//
////----------------------Variables externes du programme simple--------------------------//
//
//bool DirectementSuiteInclude = false;
//
////--------------------------------------------------------------------------------------//
//
//
//#include "resource.h" 
//
//int Tab = 0;
//
//void AskCodeName(int &NewName);
//int AskCodeName(void);
//int AskObjectInt();
//int AskFormeInt();
//string AskBoneName();
//string AskPartSkinName();
//string AskDynamicName();
//
//#include "SOIL.h"
//
///*
//#include <SDL.h>
//#undef main
//#include <SDL_net.h>
//#undef main
//*/
//
//
//class Checker
//{
//public:
//	Checker(float n) { float i = n; };
//	~Checker() {};
//};
//
#include "Header.h"
//
//#include "emlist.h"
//#include "forward_list.h"
////	#include "linearlist.h"
//#include "bilinearlist.h"
//#include "ptlist.h"
//
//#include "Declaration_fonction.h"
//#include "ConstVar.h"
////	#include Container
//
//#include "Sinus.h"
//#include "FrameTimer.h"
//#include "Timers.h"
//#include "Conversion.h"
//#include "TextBitmap.h"
//
//#include "Ecriture.h"
//
//#include "SavesManager.h"
//#include "Name.h"
//
//#include "Color.h"
//#include "RGBA.h"
//
//
//#include "Brush.h"
//#include "AfficherMots.h"
//#include "Material.h"
//	#include "Coordonnee.h"
//	#include "Vecteur.h"
//
//Vecteur3D MainOrigin = Vecteur3D(0, 0, 0);
//
//#include "TripodRef.h"
//
//
//
//#include "Bloc.h"
//#include "Frame.h"
//#include "FrameSequence.h"
//#include "FrameWork.h"
//#include "Timeline.h"
//
//#include "Point.h"
//#include "MasterPoint.h"
//
//
//	#include "JaySpaceVecteur.h"
//#include "TransRotScale.h"
//#include "TransformationVariables.h"
//#include "ShaderVariable.h"
//#include "ProgramShader.h"
//#include "ShadedTexture.h"
//
//#include "Actor.h"
//
//
//#include "VariableType.h"
//#include "VariableTypeList.h"
//
//#include "JayTextures.h"
////#include "ImageLoader.h"
//#include "Image2D.h"
//#include "Sound2D.h"
//
//#include "SelectionBox.h"
//
//
//#include "Plan.h"
//#include "Droite.h"
//	#include "JaySpace.h"
//#include "FormeInit.h"
//#include "Forme.h"
//#include "FormeCalculs.h"
//
////	#include "Mathex.h"
//#include "Tvector.h"
////#include "TRay.h"
////	#include "TMatrix.h"
//#include "Image.h"
//
//#include "Collision.h"
//
//#include "VecteurSortie.h"
//#include "VecteurSortieControler.h"
//
//#include "Nurbs.h"
//#include "SurfaceNurbs.h"
//
//#include "ObjetInit.h"
//#include "Objet.h"
//#include "BuildObject.h"
//
//#include "ChainPtrPtCtrl.h"
//
//#include "ChainObject.h"
//#include "ChainControlerObject.h"
//#include "FormedeBase.h"
//#include "ObjectsCreationFunctionPart1.h"
//#include "Light.h"
//
//#include "ListClass.h"
//NClass *ListClass;
//#include "FonctionMatrix.h"
//
//#include "Element2D.h"
//
//#include "DrawShapeFunctions.h"
//
//#include "Ecran.h"
//
//#include "Lumieres.h"
//#include "Camera.h"
//#include "Speaker.h"
//#include "Helper.h"
//
//#include "Calcul_Math_ForCamera.h"
//#include "Transformations.h"
//#include "PhysicPoint.h"
//#include "FormeAvancee.h"
//
//#include "Dynamic.h"
//#include "ApplyDynamic.h"
//#include "PartSkin.h"
//#include "Bone.h"
//#include "AngleSingleData.h"
//
//#include "PuppetToBoneModelConverter.h"
//#include "Puppet.h"
//#include "Miror.h"
//#include "SymetricBone.h"
//#include "Ajustedskin.h"
//#include "ProjectedWorkingLine.h"
//#include "ProjectedPattern.h"
//#include "ProjectedPatternTransformationFunction.h"
//
//#include "Instance.h"
//#include "Organism.h"
//#include "Element.h"
//#include "Dummy.h"
//#include "Vehicule.h"
//#include "Character.h"
//#include "Trigger.h"
//#include "StartLocation.h"
//#include "Input.h"
//#include "Physic.h"
//#include "MvtModule.h"
//#include "Terrain.h"
//
//#include "Sourie.h"
//#include "Keyboard.h"
//#include "KeyPressedWork.h"
//#include "keys.h"
//#include "Event.h"
//
//#include "MouvCam.h"
//#include "ActionMovCam.h"
//#include "Affichage.h"
//
//#include "ObjetTransformationFunction.h"
//
//#include "Sauvegarde.h"
//
//#include "IA.h"
//
//#include "Liens.h"
//
//#include "Action.h"
//
//#include "PlayerUtilitary.h"
//#include "Statistics.h"
//#include "ArtificialIntelligence.h"
//#include "AffectationPack.h"
//#include "Equipment.h"
//#include "EquipmentSetup.h"
//#include "Faction.h"
//#include "GameElement.h"
//#include "ObjectInSpace.h"
//#include "Player.h"
//#include "PlayerUnderLevelList.h"
//
//#include "DynamicSpace.h"
//
//#include "Scene.h"
//#include "Game.h"
//
//#include "SelectionHeader.h"
//#include "Selection.h"
//
//#include "Toolsbox.h"
//#include "PaletteCouleur.h"
//
//#include "Selection_Transformation1.h"
//#include "Selection_Transformation3.h"
//#include "Selection_Transformation4.h"
//#include "Selection_Affichage.h"
//
//#include "Vues.h"
//#include "ActionMovingCamera.h"
//#include "Menu.h"
//#include "Menu2.h"
//#include "Menu3.h"
//#include "Menu4.h"
//#include "MenuTranscription.h"
//#include "MenuEnregistrement.h"
//#include "SelectionMenu.h"
//#include "CommandLines.h"
//#include "Propriete.h"
//
//#include "Environnement.h"
//#include "Environnement_Transformations.h"
//#include "Environnement_SaveManager.h"
//#include "Environnement_ForSelection.h"
//#include "EnvironnementMenuFunctions.h"
//#include "EnvironnementListControlers.h"
//#include "EnvironnementTranscription.h"
//#include "EnvironnementEMTranscription.h"
//#include "EnvironnementConverter.h"
//
//#include "Edition.h"
//#include "Programme.h"
//Programme ProgOff;
//#include "PtrM.h"
//iMulti iM;
//
//
//#include "Environnement_Delete.h"
//
//#include "FonctionsSauvegarde.h"
//#include "CreationGraphique.h"
//#include "FonctionMateriel.h"
//
//#include "FonctionAjouterPoint.h"
//#include "TraiterSelection.h"
//#include "FonctionsAffObj.h"
//#include "FonctionsSelObj.h"
//#include "FonctionsAffLumetSelLum.h"
//#include "FonctionMenu.h"
//#include "SimpleMath.h"
//#include "CppFunctions.h"
//#include "Class_Sup.h"
//#include "Exit.h"
//
//#include "ReshapeFunctions.h"
//
//#include "ImageSize.h"
//
//#include "Letter2DdBasic.h"
//#include "Alphabet2Dbasic.h"
//
//#include "Texte.h"
//
//#include "DescriptiveLine.h"
//
//#include "Include.h"
//#include "Define.h"
//#include "TypeNameVariable.h"
//#include "Tabulation.h"
//#include "Variable.h"
//#include "JaySpace.h"
//#include "VariableElement.h"
//#include "CommandVariable.h"
//#include "FreeOperator.h"
//#include "Command.h"
//#include "BasicCommand.h"
//#include "FunctionCondition.h"
//#include "SelectCommandObjetList.h"
//#include "CFonction.h"
//#include "InvitedClass.h"
//#include "NClass.h"
//#include "Fonction.h"
//#include "GroupedeFonction.h"
//#include "EV2D.h"
//#include "EV3D.h"
//
//#include "Condition.h"
//
//#include "Constante.h"
//#include "ConstanteT.h"
//
////	#include "Memoire.h"
//#include "MemoireObjetCPP.h"
//
////	#include "Enregistrement1.h"
////	#include "Enregistrement2.h"
////	#include "EnregistrementMain.h"
//
//int EspaceAffichage_y(void);
//int EspaceAffichage_x(void);
//int EspaceAffichage_W(void);
//int EspaceAffichage_H(void);
//
//
//#include "Dessin.h"
//
//#include "Boutton.h"
//#include "BarreSeparation.h"
//#include "Icone.h"
//#include "IconeDeDeplacement.h"
//#include "Glissoir.h"
//#include "EspaceDecriture.h"
//#include "ElementDeTableau.h"
//#include "Tableau.h"
//#include "OptionneurDeListe.h"
//#include "CochingBox.h"
//#include "CochingDot.h"
//#include "BarreDoutil.h"
//#include "FondDentete.h"
//#include "ElementListee.h"
//#include "TitreListee.h"
//#include "ListeHierarchique.h"
//#include "ZoneAffichage.h"
//#include "BookMark.h"
//#include "Fenetre.h"
//#include "AffichageMemoireObjetCPP.h"
//#include "SelectToolbox.h"
//#include "ToolBox.h"
//#include "FreeSelector.h"
//
//
//
////	#inlude "bmpLoader.c"
//#include "LoadBmpImage.h"
//
////	#inlude "BitmapMemory.h"
//#include "bmpfunction.h"
//
//
////	#inlude "Ev2D.h"
////	#inlude "Ev3D.h"
//
//void UploadProject();
//void UploadPhoto();
//
//#include "LoadAlphabet.h"
//#include "StringWord.h"
//
//int SParenthese = 0, Parenthese = 0;
//
//bool CommentType = 0;	//	Soit 0 = // et 1 = /*
//bool IntoComment = false;
//bool ReadingSomething = false;
//bool InAString = false;
//bool InAGuillemetComatString = false;
//int unsigned TypeString;
//#define TypeGuillemet	1
//#define TypeComat		2
//int ReadComment(ifstream *FicIn, string &Word);
//bool InProcessOfReadingComment = false;
//
//
//#include "Program.h"
//
//#include "UploadPhoto.h"
//#include "UploadAlphabet.h"
//#include "UploadProject.h"
//#include "ReadingTools.h"
//#include "ReadCommand.h"
//#include "ReadProject.h"
//#include "ClassFillingFonctions.h"
//
//#include "Fonctions.h"
//#include "TranscrireProgramComplet.h"
//#include "EnregistrerMenu.h"
//
//#include "Butterfly.h"
//#include "ExecutiveCommand.h"
//#include "FonctionsToolbox.h"
//#include "FonctionsClavier.h"
//
//
//
//
////--------------------------Variables externes du programme-----------------------------//
//
//
//
//
////--------------------------D�finitions externes du programme---------------------------//
//
//#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES); \
//glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();
//
////--------------------------------Fin des d�clarations----------------------------------//
//
//
//int GetLargeurWord(string Word);
//
//
//
//#include "FunctionNavigationMain.h"
//#include "FunctionSelectionMain.h"
//#include "FunctionBrushToolMain.h"
//#include "FunctionCreateMain.h"
//#include "FunctionProjectedPatternMain.h"
//#include "ApplyTransfo.h"
//#include "FunctionTransformationMain.h"
//#include "FunctionShapingMain.h"
//#include "BrushSelectionNFunctions.h"
//
//
//#include "EndeveryFunctionnalities.h"
//
//
//#include "OldMain.h"
//
////	Checker Chek21(2.1);