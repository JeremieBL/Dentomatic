

/*****************************************\
 SurfaceBezier.cpp
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/


#include "SurfaceBezier.h"


SurfaceBezier::SurfaceBezier()
{
}

SurfaceBezier::SurfaceBezier(const glm::vec3 newpts[16])
{
    for (int i = 0; i < 16; i++)
    {
        pts[i] = newpts[i];
    }
}


SurfaceBezier::~SurfaceBezier()
{

}

void SurfaceBezier::newSurface(glm::vec3 newpts[16])
{
    for (int i = 0; i < 16; i++)
    {
        pts[i] = newpts[i];
    }
}

vector<glm::vec3> SurfaceBezier::GetPointsCopy()
{
    vector<glm::vec3> points;
    
    for (size_t i = 0; i < std::size(pts); i++)
    {
        points.push_back(pts[i]);
    }

    return points;
}


glm::vec3 SurfaceBezier::courbe(float t, glm::vec3 pt0, glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3)
{
    return glm::vec3((1 - t) * (1 - t) * (1 - t) * pt0 + 3 * (1 - t) * (1 - t) * t * pt1 +
    3 * (1 - t) * t*t*pt2 + t*t*t*pt3);
}

glm::vec3 SurfaceBezier::pos(float u, float v)
{
    glm::vec3 position;

    glm::vec3 cut[4];

    cut[0] = courbe(u, pts[0], pts[1], pts[2], pts[3]);
    cut[1] = courbe(u, pts[4], pts[5], pts[6], pts[7]);
    cut[2] = courbe(u, pts[8], pts[9], pts[10], pts[11]);
    cut[3] = courbe(u, pts[12], pts[13], pts[14], pts[15]);

    position = courbe(v, cut[0], cut[1], cut[2] , cut[3]);

    return position;
}

glm::vec3 SurfaceBezier::grad(float u, float v)
{
    glm::vec3 gradient;

    return gradient;

}

glm::vec3 SurfaceBezier::gradu(float u, float v)
{
    glm::vec3 gradient;

    return gradient;

}

glm::vec3 SurfaceBezier::gradv(float u, float v)
{
    glm::vec3 gradient;

    return gradient;

}
