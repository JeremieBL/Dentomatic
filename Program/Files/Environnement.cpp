

/*****************************************\
 Environnement.cpp
 ***** Par J�r�mie B�liveau-Lefebvre *****
 Initialis� le 8 avril 2021
\*****************************************/


#include "Environnement.h"


Environnement::Environnement()
{
}


Environnement::~Environnement()
{

}

void Environnement::Add(ShaderJay newShader)
{
    shaderList.insert(std::make_pair(newShader.shaderName, newShader));
    itShad = shaderList.find(newShader.shaderName);
}

void Environnement::Add(MultipleJays newObject)
{
    itmultiGl = multipleglList.push_back(newObject);
}

emlist<JayObjet>::iterator Environnement::Add(JayObjet newObject)
{
    itObj = objetList.push_back(newObject);
    
    mnoic++;
    itObj->id = mnoic;

    itObj->name = "Objet_" + std::to_string(mnoic);
    
    return itObj;
}

int Environnement::RenewObjetIds()
{
    mnoic = 0;

    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
        itObj->id = ++mnoic;
    }

    return mnoic;
}

void Environnement::Display(CameraJay& camera)
{
    for (itmultiGl = multipleglList.begin(); itmultiGl != multipleglList.before_begin() && itmultiGl != multipleglList.end(); itmultiGl++)
    {
        itmultiGl->Display(camera);
    }
}

// Assuming you have a shader program and VAO setup
void Environnement::drawWithOutline(GLuint shaderProgram, GLuint outlineShaderProgram, GLuint vao,
    unsigned int vertexCount, const glm::mat4& model,
    const glm::mat4& view, const glm::mat4& projection,
    const glm::vec3& objectColor, const glm::vec3& outlineColor,
    float outlineScale = 1.05f) {

    // Enable stencil testing
    glEnable(GL_STENCIL_TEST);

    // Step 1: Render object normally, writing to stencil buffer
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // All fragments pass
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Write 1 to stencil
    glStencilMask(0xFF); // Enable writing to stencil buffer
    glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer

    // Use main shader program
    glUseProgram(shaderProgram);

    // Set uniforms for main object
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, &objectColor[0]);

    // Draw the object
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    // Step 2: Render outline
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Pass where stencil is not 1
    glStencilMask(0x00); // Disable writing to stencil buffer
    glDisable(GL_DEPTH_TEST); // Disable depth test for outline

    // Use outline shader program
    glUseProgram(outlineShaderProgram);

    // Scale model matrix for outline
    glm::mat4 outlineModel = glm::scale(model, glm::vec3(outlineScale));

    // Set uniforms for outline
    glUniformMatrix4fv(glGetUniformLocation(outlineShaderProgram, "model"), 1, GL_FALSE, &outlineModel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(outlineShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(outlineShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniform3fv(glGetUniformLocation(outlineShaderProgram, "outlineColor"), 1, &outlineColor[0]);

    // Draw scaled object for outline
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    // Clean up
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
}

void Environnement::Display()
{
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {

		////  Display the object
          itObj->Display();  


  //       
  //       // First pass: Render the object normally, writing to stencil
  //      glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass, set stencil to 1
  //      glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Replace on pass
  //      glStencilMask(0xFF); // Enable writing to stencil

  //      itShad = shaderList.find("Outline");
  //      itShad->second.PassMatrixes();
  //      itShad->second.PassVariables(&itObj);
  //      itShad->second.UseProgram();

		//itObj->Draw();
  //      itShad->second.EndProgram();

  //      // Second pass: Render enlarged outline, only where stencil != 1
  //      glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Pass if stencil != 1
  //      glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // No change to stencil
  //      glStencilMask(0x00); // Disable writing to stencil

  //      glDepthMask(GL_FALSE); // Disable depth write to avoid z-fighting/issues


  //      itObj->Draw();

  //      // Reset states
  //      glDepthMask(GL_TRUE);
  //      glDisable(GL_STENCIL_TEST);
  //      itShad->second.EndProgram();

    }
}

void Environnement::DeclareObjets() {
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
        itObj->DeclareObjet();
    }
}


void Environnement::DisplayTools()
{
    for (itToolObj = toolObjetList.begin(); itToolObj != toolObjetList.before_begin() && itToolObj != toolObjetList.end(); itToolObj++)
    {
        itToolObj->Display();
    }
}

void Environnement::DeclareTools()  {
    for (itToolObj = toolObjetList.begin(); itToolObj != toolObjetList.before_begin() && itToolObj != toolObjetList.end(); itToolObj++)
    {
        itToolObj->DeclareObjet();
    }
}

bool Environnement::SearchForItemWithID_(int selectedId) {
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
        if (itObj->id == selectedId) {
            itObj->SetSelection(true);
            itSelObj = selectedObjetList.push_back(itObj);
            //  (&(*itSelObj)).
            return true;
        }
    }
    return false;
}
bool Environnement::SearchForItemWithID_ForMouseOver(int selectedId) {
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
        if (itObj->id == selectedId) {
            itObj->SetmouseOver(true);
            return true;
        }
    }
    return false;
}

void Environnement::EmptySelection() {
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
		itObj->SetSelection(false);
    }

    selectedObjetList.clear();
}


void Environnement::EmptyMouseOverSelection() {
    for (itObj = objetList.begin(); itObj != objetList.before_begin() && itObj != objetList.end(); itObj++)
    {
        itObj->SetmouseOver(false);
    }
}
