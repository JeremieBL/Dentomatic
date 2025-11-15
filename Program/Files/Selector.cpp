#include "Selector.h"	


// Assume you have a basic OpenGL setup with GLFW and GLEW initialized

// Structure to represent selectable objects
struct SceneObject {
    GLuint vao; // Vertex Array Object
    glm::vec3 position;
    int id; // Unique ID for picking
    // Add other properties like vertices, model matrix, etc.
};
SelectionFramebuffer::SelectionFramebuffer(int w, int h) : width(w), height(h) {
    // Create framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create color attachment
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);

    // Create depth attachment
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    // Check framebuffer status
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

SelectionFramebuffer::SelectionFramebuffer()
{
}

SelectionFramebuffer::~SelectionFramebuffer()
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &colorBuffer);
    glDeleteRenderbuffers(1, &depthBuffer);
}

void SelectionFramebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void SelectionFramebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint SelectionFramebuffer::getFBO() const { return fbo; }

// Function to convert object ID to unique color
glm::vec3 SelectionFramebuffer::idToColor(int id) {
    int residualid = id - (id % (256 * 256));
    id = id - residualid;
    residualid = residualid / 256 / 256;

    color.z = residualid;

    residualid = id - (id % 256);
    id = id - residualid;
    residualid = residualid / 256;

    color.y = residualid;

    color.x = id;

    return color;
}

// Function to convert color back to ID
int SelectionFramebuffer::colorToId(const GLubyte* color) {
    return color[0] + color[1] * 256 + color[2] * 256 * 256;
}
int SelectionFramebuffer::colorToId(glm::vec4 color) {
    return color.x + color.y * 256 + color.z * 256 * 256;
}

// Selection function
int SelectionFramebuffer::selectObject(emlist<JayObjet> *objects,
    int mouseX, int mouseY, int windowWidth, int windowHeight,
    GLuint shaderProgram) {
    mouseX = mouseX + windowWidth / 2.0f;
    mouseY = mouseY + windowHeight / 2.0f;
    // Save OpenGL state
    GLint previousFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFBO);
    GLint previousProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
    GLboolean multisampleEnabled = glIsEnabled(GL_MULTISAMPLE);
    GLboolean ditherEnabled = glIsEnabled(GL_DITHER);
    GLint previousViewport[4];
    glGetIntegerv(GL_VIEWPORT, previousViewport);
    GLint previousVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVAO);

    // Bind picking framebuffer
    bind();
    glViewport(0, 0, windowWidth, windowHeight);

    // Clear picking buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configure rendering state
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DITHER);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    // Render each object
    for (emlist<JayObjet>::iterator it = objects->begin(); it != objects->before_begin() && it != objects->end(); it++) {
        // Verify shader program
        glUseProgram(shaderProgram);

        // Set picking color
        glm::vec3 color = idToColor(it->id);

        GLint pickingColorLoc = glGetUniformLocation(shaderProgram, "pickingColor");

        glUniform3fv(pickingColorLoc, 1, &color[0]);

        if(&it->ptrShader != nullptr)
        {
            // Set matrices (replace with your actual matrices)
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, it->ptrShader->ModMat_);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, it->ptrShader->ViewMat_);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, it->ptrShader->ProjMat_);
            
            //glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, it->ptrShader->ProjMat_);
        }

        // Bind VAO
        glBindVertexArray(it->vertexArrayID);
        GLint vaoBound;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoBound);

        // Draw object
        glDrawArrays(GL_TRIANGLES, 0, it->vertices.size());
        glBindVertexArray(0);

        // Check for OpenGL errors
    }

    // Read pixelGL_RGBA32I, GL_INT
    GLubyte pixel[4];
    glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    // Restore OpenGL state
    glBindVertexArray(previousVAO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(previousProgram);
    glViewport(previousViewport[0], previousViewport[1], previousViewport[2], previousViewport[3]);
    if (multisampleEnabled) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);
    if (ditherEnabled) glEnable(GL_DITHER); else glDisable(GL_DITHER);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    // Convert pixel color to ID
    int selectedId = colorToId(pixel);
  
    //  std::cout << "Selected ID: " << selectedId << std::endl;

    return (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) ? -1 : selectedId;
}


/*
// Selection function
int SelectionFramebuffer::selectObject(emlist<JayObjet> *objects,
    int mouseX, int mouseY, int windowWidth, int windowHeight,
    GLuint shaderProgram) {
    mouseX = (mouseX + windowWidth / 2.0f) * 2.0f;
    mouseY = (windowHeight-(mouseY + windowHeight / 2.0f))*2.0f;
    // Save OpenGL state
    GLint previousFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFBO);
    GLint previousProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
    GLboolean multisampleEnabled = glIsEnabled(GL_MULTISAMPLE);
    GLboolean ditherEnabled = glIsEnabled(GL_DITHER);
    GLint previousViewport[4];
    glGetIntegerv(GL_VIEWPORT, previousViewport);
    GLint previousVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVAO);

    // Bind picking framebuffer
    bind();
    glViewport(0, 0, windowWidth, windowHeight);

    // Clear picking buffer
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configure rendering state
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DITHER);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    // Render each object
    for (emlist<JayObjet>::iterator it = objects->begin(); it != objects->before_begin() && it != objects->end(); it++) {
        std::cout << "Attempting to render object ID: " << it->id << " with VAO: " << it->vertexArrayID << std::endl;

        // Verify shader program
        glUseProgram(shaderProgram);
        GLint programValid;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programValid);
        if (!programValid) {
            std::cerr << "Error: Picking shader program is invalid!" << std::endl;
            return -1;
        }

        // Set picking color
        glm::vec4 color = idToColor(10000 - it->id);


        GLint pickingColorLoc = glGetUniformLocation(shaderProgram, "pickingColor");
        if (pickingColorLoc == -1) {
            std::cerr << "Error: pickingColor uniform not found!" << std::endl;
            return -1;
        }
        glUniform4fv(pickingColorLoc, 1, &color[0]);

        // Set matrices (replace with your actual matrices)
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &it->modelMatrix[0][0]);
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &viewMatrix[0][0]);
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projectionMatrix[0][0]);

        // Verify VAO exists
        if (!glIsVertexArray(it->vertexArrayID)) {
            std::cerr << "Error: VAO " << it->vertexArrayID << " is not a valid VAO!" << std::endl;
            continue; // Skip invalid VAO
        }

        // Bind VAO
        glBindVertexArray(it->vertexArrayID);
        GLint vaoBound;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoBound);
        if (vaoBound != it->vertexArrayID) {
            std::cerr << "Error: VAO " << it->vertexArrayID << " not bound correctly! Current VAO: " << vaoBound << std::endl;
            continue; // Skip draw if VAO binding failed
        }

        // Draw object

            std::cout << "Drawing non-indexed object with " << it->vertices.size() << " vertices" << std::endl;
            if (it->vertices.size() <= 0) {
                std::cerr << "Error: Invalid vertex count for object " << it->id << ": " << it->vertices.size() << std::endl;
                continue;
            }
            glDrawArrays(GL_TRIANGLES, 0, it->vertices.size());
            glBindVertexArray(0);
        // Check for OpenGL errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL Error during picking for object " << it->id << ": " << err << std::endl;
        }
    }

    // Read pixel
    GLubyte pixel[4];
    glReadPixels(mouseX, windowHeight - mouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    std::cout << "Pixel color at (" << mouseX << ", " << mouseY << "): R=" << (int)pixel[0]
        << ", G=" << (int)pixel[1] << ", B=" << (int)pixel[2] << std::endl;

    // Restore OpenGL state
    glBindVertexArray(previousVAO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(previousProgram);
    glViewport(previousViewport[0], previousViewport[1], previousViewport[2], previousViewport[3]);
    if (multisampleEnabled) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);
    if (ditherEnabled) glEnable(GL_DITHER); else glDisable(GL_DITHER);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    cout << "Id : " << " ColorID : " << pixel[0] << "," << pixel[1] << "," << pixel[2] << endl;

    // Convert pixel color to ID
    int selectedId = colorToId(pixel);
    std::cout << "Selected ID: " << selectedId << std::endl;
    return (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) ? -1 : selectedId;
}
*/