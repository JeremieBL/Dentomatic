//
//  Program.cpp
//




// Include GLEW
#include <GL/glew.h>
#include <Windows.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <cmath>

using namespace std;

#include "ProjectTeethJay.h"

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

//#include "pu.h" 

float F(float x, float y)
{
    return(8 * exp(-(x * x + y * y) / 5));
}

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}


void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

int main(int argc, const char* argv[]) {
    
    ShowConsole();

    //puInit();
    //InitUI();

	ProjectTeethJay projet;

	do {
        projet.HighwayToGPU();
        if (projet.SetupForDisplay())
            break;
        projet.Display_Loop();

        //puDisplay();
	}
	while (projet.LoopConditions());

	projet.CleanUp();

    return 0;
}

