#pragma once



/*****************************************\
 SurfaceBezier.h
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/



#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <iostream>
using namespace std;
#include <vector>

class SurfaceBezier
{
    //  Text en format Opengl pr�t � �tre affich�
public :
    SurfaceBezier();
    SurfaceBezier(const glm::vec3 newpts[16]);
    ~SurfaceBezier();
    
    glm::vec3 courbe(float t, glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3, glm::vec3 pt4);
    glm::vec3 pos(float, float);
    glm::vec3 grad(float, float);
    glm::vec3 gradu(float, float);
    glm::vec3 gradv(float, float);

    void newSurface(glm::vec3 newpts[16]);
    vector<glm::vec3> GetPointsCopy();
private:
    glm::vec3 pts[16];
    glm::vec3 midpt;

};