#pragma once



/*****************************************\
 Environnement.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;

#include <vector>
#include <unordered_map>
#include "CameraJay.h"
#include "ShaderTexture.h"
#include "MultipleJays.h"
#include "ViewerJay.h"
#include "SimpleJay.h"
#include "CameraJay.h"
#include "LightJay.h"
#include "Shader.h"
#include "MateriauxJay.h"
#include "emlist.h"


#include "../Eigen/Dense"

using namespace Eigen;

class Environnement
{       
public :
    Environnement();
	~Environnement();

    emlist<JayObjet> objetList;
    emlist<JayObjet>::iterator itObj;

    emlist<emlist<JayObjet>::iterator> selectedObjetList;
    emlist<emlist<JayObjet>::iterator>::iterator itSelObj;

    bool SearchForItemWithID_(int selectedId);
    bool SearchForItemWithID_ForMouseOver(int selectedId);
    void EmptySelection();
    void EmptyMouseOverSelection();

    //  Max Number Of Item Created.
    int mnoic = 0;
    unsigned int MNOIC() { return mnoic; };

    emlist<JayObjet> toolObjetList;
    emlist<JayObjet>::iterator itToolObj;

    emlist<MultipleJays> multipleglList;
    emlist<MultipleJays>::iterator itmultiGl;

    emlist<ViewerJay> viewerList;
    emlist<ViewerJay>::iterator itView;

    unordered_map<string, ShaderJay> shaderList;
    unordered_map<string, ShaderJay>::iterator itShad;

    emlist<MateriauxJay> materialsList;
    emlist<MateriauxJay>::iterator itMat;

    emlist<CameraJay> cameraList;
    emlist<CameraJay>::iterator itCam;

    emlist<LightJay> lightList;
    emlist<LightJay>::iterator itLight;
    
    void Add(ShaderJay newShader);
    void Add(MultipleJays newObject);
    void Display(CameraJay& camera);

    void drawWithOutline(GLuint shaderProgram, GLuint outlineShaderProgram, GLuint vao,
        unsigned int vertexCount, const glm::mat4& model,
        const glm::mat4& view, const glm::mat4& projection,
        const glm::vec3& objectColor, const glm::vec3& outlineColor,
        float outlineScale);

    emlist<JayObjet>::iterator Add(JayObjet newObj);
    int RenewObjetIds();

    void Display();
    void DeclareObjets();

    void DisplayTools();
    void DeclareTools();
};