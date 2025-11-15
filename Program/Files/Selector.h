#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "emlist.h"
#include "JayObjet.h"
#include "Vecteur.h"

#include <iostream>
using namespace std;


// Framebuffer for picking
class SelectionFramebuffer {
private:
    GLuint fbo;
    GLuint colorBuffer;
    GLuint depthBuffer;
    int width, height;
    glm::vec3 color;

public:
    SelectionFramebuffer();
    SelectionFramebuffer(int w, int h);
    ~SelectionFramebuffer();
    void bind();
    void unbind();
    GLuint getFBO() const;
    glm::vec3 idToColor(int id);
    int colorToId(const GLubyte* color);
    int colorToId(glm::vec4 color);
    int selectObject(emlist<JayObjet> *objects,
        int mouseX, int mouseY, int windowWidth, int windowHeight,
        GLuint shaderProgram);
};