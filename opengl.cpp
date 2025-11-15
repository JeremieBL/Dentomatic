// Include standard headers
#include <stdio.h>
#include <stdlib.h>


#include <iostream>
#include <vector>
#include <cmath>


#include "../Eigen/Dense"

#define cimg_display 0

#include "../CImg.h"

using namespace Eigen;
using namespace cimg_library;
using namespace std;

#include "opengl.h"




OpenGL::OpenGL() {

};


OpenGL::~OpenGL() {

};

float g_Scale = 1.0f;
float g_MouseWheelScale = 0.05f;


void ScrollCallback(GLFWwindow* window, double x, double y)
{
	g_Scale -= g_MouseWheelScale * (float)y;
	g_Scale = std::max(0.01f, g_Scale);
}

void OpenGL::ContextInitialisation() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, "TP2 - Visualisation des donnees scalaires - 04494470 ", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// somewhere in your main function call:
	glfwSetScrollCallback(window, ScrollCallback);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);





	// The fullscreen quad's FBO
	g_quad_vertex_buffer_data = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};



};

void OpenGL::ShaderInitialisation() {

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	// Load the texture
	Texture = loadDDS("uvtemplate.DDS");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	colorMapID = glGetUniformLocation(programID, "colomapmod");
	minID = glGetUniformLocation(programID, "minToClamp");
	maxID = glGetUniformLocation(programID, "maxToClamp");




	// Create and compile our GLSL program from the shaders for isocontour
	iso_programID = LoadShaders("IsocontourVertShader.vertexshader", "IsocontourFragShader.fragmentshader");
	// Get a handle for our "MVP" uniform
	isoMatrixID = glGetUniformLocation(iso_programID, "MVP");
	iso_colorID = glGetUniformLocation(iso_programID, "inColor");



	// Create and compile our GLSL program from the shaders
	programR2T_ID = LoadShaders("StandardShadingRTT.vertexshader", "StandardShadingRTT.fragmentshader");


	// Get a handle for our "MVP" uniform
	MatrixR2T_ID = glGetUniformLocation(programR2T_ID, "MVP");
	ViewMatrixR2T_ID = glGetUniformLocation(programR2T_ID, "V");
	ModelMatrixR2T_ID = glGetUniformLocation(programR2T_ID, "M");

	TextureR2T_ID = glGetUniformLocation(programR2T_ID, "myTextureSampler");
	LightID = glGetUniformLocation(programR2T_ID, "LightPosition_worldspace");

	TextureR2T = loadDDS("uvmap.DDS");



	bool res = loadOBJ("suzanne.obj", verticesR2T, uvsR2T, normalsR2T);


	indexVBO(verticesR2T, uvsR2T, normalsR2T, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	glGenBuffers(1, &vertexbufferR2T);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferR2T);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbufferR2T);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferR2T);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbufferR2T);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferR2T);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbufferR2T);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferR2T);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programR2T_ID);




	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// -------------------------------


	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// The depth buffer
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	//// Alternative : Depth texture. Slower, but you can sample it later in your shader
	//GLuint depthTexture;
	//glGenTextures(1, &depthTexture);
	//glBindTexture(GL_TEXTURE_2D, depthTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	//// Depth texture alternative : 
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);


	// Set the list of draw buffers.
	DrawBuffers[0] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);


	// The fullscreen quad's FBO
	g_quad_vertex_buffer_data = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), &g_quad_vertex_buffer_data[0], GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	quad_programID = LoadShaders("Passthrough.vertexshader", "WobblyTexture.fragmentshader");
	texID = glGetUniformLocation(quad_programID, "renderedTexture");
	timeID = glGetUniformLocation(quad_programID, "time");




}

void OpenGL::DeclarationOfObjects() {


	////	These rows are in comments because they doesnt exit at the start.
	//for (size_t i = 0; i < simpleGLs.size(); i++)
	//{
	//	simpleGLs[i].Init();
	//}


	glGenVertexArrays(1, &VertexArrayID);
	glGenBuffers(1, &vertexbuffer);

	glGenVertexArrays(1, &IsocontourArrayID);
	glGenBuffers(1, &isocontoursbuffer);

	glGenVertexArrays(1, &VertexArrayR2TID);
	glBindVertexArray(VertexArrayR2TID);



};

void OpenGL::ConstructionAndUpdateOfObjects() {

	if (!gridUpdated) {
		gridUpdated = true;

		vectices.resize(0);
		uvs.resize(0);

		increment = (float) size / division;

		isocontours.resize(0);

		minToClamp = 6;
		maxToClamp = 0;

		//MatrixXd _2Dgrid;
		//_2Dgrid.resize(division, division);

		_2DTexture.resize(division + 1, division + 1);

		cimg_forXY(_2DTexture, _x, _y)
		{
			float x = (float)_x / division * size - size / 2.f;
			float y = (float)_y / division * size - size / 2.f;
			
			_2DTexture(_x, _y) = Height(x, y);

			minToClamp = std::min(minToClamp, _2DTexture(_x, _y));
			maxToClamp = std::max(maxToClamp, _2DTexture(_x, _y));
		}

		float i = -size / 2.0f;
		for (int k = 0; k < division; k++, i += increment)
		{
			float j = -size / 2.0f;
			for (int l = 0; l < division; l++, j += increment)
			{
				glm::vec3 points[4];
				points[0] = glm::vec3(i, _2DTexture(k, l + 1), -j - increment);
				points[1] = glm::vec3(i, _2DTexture(k, l), -j);
				points[2] = glm::vec3(i + increment, _2DTexture(k + 1, l), -j);
				points[3] = glm::vec3(i + increment, _2DTexture(k + 1, l + 1), -j - increment);

				vectices.push_back(points[0]);
				vectices.push_back(points[1]);
				vectices.push_back(points[2]);
				vectices.push_back(points[0]);
				vectices.push_back(points[2]);
				vectices.push_back(points[3]);			
			}
		}

		glBindVertexArray(VertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(glm::vec3), &vectices[0], GL_STATIC_DRAW);
	}


	if (!isocontourUpdated)
	{
		isocontourUpdated = true;

		isocontours = MakeIsoline(isolineFreeFloat);

		if (isocontours.size()) {
			glBindVertexArray(IsocontourArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, isocontoursbuffer);
			glBufferData(GL_ARRAY_BUFFER, isocontours.size() * sizeof(glm::vec3), &isocontours[0], GL_STATIC_DRAW);
		}

		for (size_t i = 0; i < isoContoursGL.size(); i++)
		{
			isoContoursGL[i].UpdateIDs();
		}
	}

};

void OpenGL::HighwayToGPU() {

};

void OpenGL::SetupForDisplay() {

};

void OpenGL::Display_Loop() {

	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		//computeMatricesFromInputs(window);
		ComputeMatricesFromInputs();
		//ProjectionMatrix = getProjectionMatrix();
		//ViewMatrix = getViewMatrix();
		ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glUniform1i(colorMapID, colormapMod);
		glUniform1f(minID, minToClamp);
		glUniform1f(maxID, maxToClamp);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);


		glBindVertexArray(VertexArrayID);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vectices.size()); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(0);


		glUseProgram(iso_programID);
		glUniform3f(iso_colorID, 0.0, 0.0, 0.0f);

		glUniformMatrix4fv(isoMatrixID, 1, GL_FALSE, &MVP[0][0]);


		if (isTogglingBetweenIsoContours)
		{
			for (size_t i = 0; i < isoContoursGL.size(); i++)
				if (selectedIsocontour != i)
					isoContoursGL[i].Draw();
		}
		else {
			for (size_t i = 0; i < isoContoursGL.size(); i++)
				isoContoursGL[i].Draw();
		}


		glUseProgram(0);


		glUseProgram(iso_programID);

		if (isoIsSelected) {
			glUniform3f(iso_colorID, 1.0, 0.0, 0.0f);
		}
		else
		{
			glUniform3f(iso_colorID, 0.25f, 0.75f, 1.0f);
		}


		glBindVertexArray(IsocontourArrayID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, isocontoursbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the lines !

		glDrawArrays(GL_LINES, 0, isocontours.size());
		glBindVertexArray(0);

		glDisableVertexAttribArray(0);


		glUseProgram(0);

	}


	//	// Render to our framebuffer
	//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	//glViewport(0, 0, windowWidth, windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	//// Clear the screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Use our shader
	//glUseProgram(programR2T_ID);

	//// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(window);
	//glm::mat4 ProjectionMatrix = getProjectionMatrix();
	//glm::mat4 ViewMatrix = getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	//glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	//// Send our transformation to the currently bound shader, 
	//// in the "MVP" uniform
	//glUniformMatrix4fv(MatrixR2T_ID, 1, GL_FALSE, &MVP[0][0]);
	//glUniformMatrix4fv(ModelMatrixR2T_ID, 1, GL_FALSE, &ModelMatrix[0][0]);
	//glUniformMatrix4fv(ViewMatrixR2T_ID, 1, GL_FALSE, &ViewMatrix[0][0]);

	//glm::vec3 lightPos = glm::vec3(4, 4, 4);
	//glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	//// Bind our texture in Texture Unit 0
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, TextureR2T);
	//// Set our "myTextureSampler" sampler to use Texture Unit 0
	//glUniform1i(TextureR2T_ID, 0);

	//// 1rst attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbufferR2T);
	//glVertexAttribPointer(
	//	0,                  // attribute
	//	3,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);

	//// 2nd attribute buffer : UVs
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbufferR2T);
	//glVertexAttribPointer(
	//	1,                                // attribute
	//	2,                                // size
	//	GL_FLOAT,                         // type
	//	GL_FALSE,                         // normalized?
	//	0,                                // stride
	//	(void*)0                          // array buffer offset
	//);

	//// 3rd attribute buffer : normals
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, normalbufferR2T);
	//glVertexAttribPointer(
	//	2,                                // attribute
	//	3,                                // size
	//	GL_FLOAT,                         // type
	//	GL_FALSE,                         // normalized?
	//	0,                                // stride
	//	(void*)0                          // array buffer offset
	//);

	//// Index buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferR2T);

	//// Draw the triangles !
	//glDrawElements(
	//	GL_TRIANGLES,      // mode
	//	indices.size(),    // count
	//	GL_UNSIGNED_SHORT, // type
	//	(void*)0           // element array buffer offset
	//);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);





	//// Render to the screen
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//// Render on the whole framebuffer, complete from the lower left corner to the upper right
	//glViewport(0, 0, windowWidth, windowHeight);

	//// Clear the screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Use our shader
	//glUseProgram(quad_programID);

	//// Bind our texture in Texture Unit 0
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, renderedTexture);
	//// Set our "renderedTexture" sampler to use Texture Unit 0
	//glUniform1i(texID, 0);

	//glUniform1f(timeID, (float)(glfwGetTime() * 10.0f));

	//// 1rst attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	//glVertexAttribPointer(
	//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//	3,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);

	//// Draw the triangles !
	//glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	//glDisableVertexAttribArray(0);



	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

};

void OpenGL::CleanUp() {

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &isocontoursbuffer);
	glDeleteProgram(programID);
	glDeleteProgram(iso_programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteVertexArrays(1, &IsocontourArrayID);
	glDeleteVertexArrays(1, &VertexArrayR2TID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
};


bool OpenGL::LoopConditions() {
	return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0;
};

float OpenGL::Height(float x, float y) {
	return 2 * exp(-(x*x + y*y)) + exp(-((x - 3) * (x - 3) + (y - 3) * (y - 3)));
}


void OpenGL::ComputeMatricesFromInputs() {
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(windowWidth / 2 - xpos);
		verticalAngle += mouseSpeed * float(windowHeight / 2 - ypos);

	m_Scale = g_Scale;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction;
	glm::vec3 right;

	if (OrthoMod)
	{
		aim.x += (float) float(windowWidth / 2 - xpos) / 100 * m_Scale;
		aim.z += (float) float(windowHeight / 2 - ypos) / 100* m_Scale;
	}
	else
	{

		direction = glm::vec3(
			distance * m_Scale * cos(verticalAngle) * sin(horizontalAngle),
			distance * m_Scale * sin(verticalAngle),
			distance * m_Scale * cos(verticalAngle) * cos(horizontalAngle)
		);

		position = aim - direction;

		// Right vector
		right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);

		// Up vector
		up = glm::cross(right, direction);

	}

	glm::vec3 forwardVect(
		cos(verticalAngle) * sin(horizontalAngle),
		0,
		cos(verticalAngle) * cos(horizontalAngle));

	if (OrthoMod)
	{
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			aim.z -= 0.05f;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			aim.z += 0.05f;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			aim.x += 0.05f;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			aim.x -= 0.05f;
		}
	}
	else
	{
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			aim += 0.1f * forwardVect;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			aim -= 0.1f * forwardVect;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			aim += 0.1f * right;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			aim -= 0.1f * right;
		}
	}


	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		//	Here we add an isocontour at the place the isocontour is located
		if (!isoIsSelected && Q_wasnotpressed)
		{
			Q_wasnotpressed = false;
			isTogglingBetweenIsoContours = true;

			SimpleGL newSimpleGLObject(MakeIsoline(isolineFreeFloat));
			isoContoursGL.push_back(newSimpleGLObject);
			isoContoursHeights.push_back(isolineFreeFloat);
			selectedIsocontour = isoContoursHeights.size() - 1;

			isocontourUpdated = false;
		}

	}
	else
	{
		Q_wasnotpressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

		if (R_wasnotpressed)
		{
			R_wasnotpressed = false;
			isTogglingBetweenIsoContours = true;

			if (isoIsSelected)
			{
				isoIsSelected = false;
			}
			else
			{
				if (!(selectedIsocontour < 0) && selectedIsocontour < isoContoursGL.size())
				{

					isoIsSelected = true;
				}
			}
		}
	}
	else
	{
		R_wasnotpressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		//	Here we toggle between the selection of iso contour

		if (isoContoursGL.size() != 0 && E_wasnotpressed)
		{
			E_wasnotpressed = false;

			selectedIsocontour++;
			if (selectedIsocontour > isoContoursGL.size() - 1)selectedIsocontour = 0;
			isolineFreeFloat = isoContoursHeights[selectedIsocontour];
			isocontours = MakeIsoline(isolineFreeFloat);

			isocontourUpdated = false;

			isTogglingBetweenIsoContours = true;
		}
	}
	else
	{
		E_wasnotpressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		//	Here we delete the isocontour
		if (isoIsSelected && isoContoursGL.size() != 0 && X_wasnotpressed)	//	Double certitude
		{
			X_wasnotpressed = false;
			isTogglingBetweenIsoContours = true;

			isoContoursGL.erase(isoContoursGL.begin() + selectedIsocontour);
			isoContoursHeights.erase(isoContoursHeights.begin() + selectedIsocontour);


			selectedIsocontour = std::max(--selectedIsocontour, 0);
			

			if (isoContoursGL.size() != 0)
			{
				isolineFreeFloat = isoContoursHeights[selectedIsocontour];
				isocontours = MakeIsoline(isolineFreeFloat);
			}
			else
			{
				isoIsSelected = false;
			}

		}

		isocontourUpdated = false;
	}
	else
	{
		X_wasnotpressed = true;
	}


	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		//	Here we lower the selected isocontour
		if (isoIsSelected)
		{
			isolineFreeFloat = (isoContoursHeights[selectedIsocontour] -= 0.01f);
			isoContoursGL[selectedIsocontour].UpdateWith(isocontours = MakeIsoline(isolineFreeFloat));
		}
		else
		{
			isTogglingBetweenIsoContours = false;

			isolineFreeFloat -= 0.01f;
			isolineFreeFloat = std::max(isolineFreeFloat, 0.f);
		}

		isocontourUpdated = false;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		//	Here we lift the selected isocontour
		if (isoIsSelected)
		{
			isolineFreeFloat = (isoContoursHeights[selectedIsocontour] += 0.01f);
			isoContoursGL[selectedIsocontour].UpdateWith(isocontours = MakeIsoline(isolineFreeFloat));
		}
		else
		{
			isTogglingBetweenIsoContours = false;
			isolineFreeFloat += 0.01f;
		}

		isocontourUpdated = false;
	}

	aim.x = (aim.x < -5) ? -5 : (aim.x > 5) ? 5 : aim.x;	//	Clamp aim.x between [-5, 5]
	aim.z = (aim.z < -5) ? -5 : (aim.z > 5) ? 5 : aim.z;	//	Clamp aim.z between [-5, 5]

	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
		division++;

		gridUpdated = false;
	}

	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && division != 1) {
		division--;
		division = std::max(1, division);

		gridUpdated = false;
	}


	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (colormapModeReleased) {
			colormapModeReleased = false;
			colormapMod++;

			if (colormapMod > 4) colormapMod = 0;
		}
	}
	else
	{
		colormapModeReleased = true;
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (OrthoModReleased) {
			OrthoModReleased = false;
			OrthoMod = !OrthoMod;
		}
	}
	else
	{
		OrthoModReleased = true;
	}


	if (OrthoMod) {

		ViewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0),       // Camera position
			glm::vec3(0.0, -1.0, 0.0), // The point the camera looks at
			glm::vec3(0.0, 0.0, -1.0));// The camera's up vector

			// Initialize the projection matrix
		ProjectionMatrix = glm::ortho(
			-5.f/ windowHeight * windowWidth * m_Scale + aim.x,
			5.f / windowHeight * windowWidth * m_Scale + aim.x,
			-5.f * m_Scale - aim.z,
			5.f * m_Scale - aim.z,
			-5.f,
			5.f);
	}
	else
	{
		float FoV = initialFoV;

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.001f, 100.0f);
		// Camera matrix
		ViewMatrix = glm::lookAt(
			position,           // Camera is here
			position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

vector<glm::vec3> OpenGL::MakeIsoline(float isolineLevel)
{
	vector<glm::vec3> isoline2return;

	float i = -size / 2.0f;
	for (int k = 0; k < division; k++, i += increment)
	{
		float j = -size / 2.0f;
		for (int l = 0; l < division; l++, j += increment)
		{
			glm::vec3 points[4];
			points[0] = glm::vec3(i, _2DTexture(k, l + 1), -j - increment);
			points[1] = glm::vec3(i, _2DTexture(k, l), -j);
			points[2] = glm::vec3(i + increment, _2DTexture(k + 1, l), -j);
			points[3] = glm::vec3(i + increment, _2DTexture(k + 1, l + 1), -j - increment);

			//	Marching square technic right here;

			int code = 0;
			if (points[0].y > isolineLevel) code += 1;
			if (points[1].y > isolineLevel) code += 2;
			if (points[2].y > isolineLevel) code += 4;
			if (points[3].y > isolineLevel) code += 8;


			glm::vec3 isoPt[4];

			float ratios[4];
			ratios[0] = std::abs(points[0].y - isolineLevel) / std::abs(points[0].y - points[1].y);
			ratios[1] = std::abs(points[1].y - isolineLevel) / std::abs(points[1].y - points[2].y);
			ratios[2] = std::abs(points[2].y - isolineLevel) / std::abs(points[2].y - points[3].y);
			ratios[3] = std::abs(points[3].y - isolineLevel) / std::abs(points[3].y - points[0].y);


			glm::vec3 midPt[4];
			midPt[0] = (ratios[0] * points[1] + (1 - ratios[0]) * points[0]);
			midPt[1] = (ratios[1] * points[2] + (1 - ratios[1]) * points[1]);
			midPt[2] = (ratios[2] * points[3] + (1 - ratios[2]) * points[2]);
			midPt[3] = (ratios[3] * points[0] + (1 - ratios[3]) * points[3]);

			switch (code)
			{
			case 0:
				break;
			case 1:
			case 14:
				isoline2return.push_back(midPt[0]);
				isoline2return.push_back(midPt[3]);
				break;
			case 2:
			case 13:
				isoline2return.push_back(midPt[0]);
				isoline2return.push_back(midPt[1]);
				break;
			case 3:
			case 12:
				isoline2return.push_back(midPt[1]);
				isoline2return.push_back(midPt[3]);
				break;
			case 4:
			case 11:
				isoline2return.push_back(midPt[1]);
				isoline2return.push_back(midPt[2]);
				break;
			case 5:
				isoline2return.push_back(midPt[1]);
				isoline2return.push_back(midPt[2]);
				isoline2return.push_back(midPt[3]);
				isoline2return.push_back(midPt[0]);
				break;
			case 6:
			case 9:
				isoline2return.push_back(midPt[0]);
				isoline2return.push_back(midPt[2]);
				break;
			case 7:
			case 8:
				isoline2return.push_back(midPt[2]);
				isoline2return.push_back(midPt[3]);
				break;
			case 10:
				isoline2return.push_back(midPt[0]);
				isoline2return.push_back(midPt[1]);
				isoline2return.push_back(midPt[2]);
				isoline2return.push_back(midPt[3]);
				break;
			case 15:
				break;
			default:
				break;
			}
		}
	}

	return isoline2return;
}