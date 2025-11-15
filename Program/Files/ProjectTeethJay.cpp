// Include standard headers

#include "ProjectTeethJay.h"


TypeNavigation ProjectTeethJay::getTypeNav() {
	return mTypeNav;
};

void ProjectTeethJay::setTypeNav(TypeNavigation newTypeNav) {
	mTypeNav = newTypeNav;
};


void ProjectTeethJay::CheckInforFromOpenGL()
{
	GLint maxBufferSize = 0;
//	glGetIntegerv(GL_MAX_ELEMENT_ARRAY_BUFFER_BINDING, &maxBufferSize);
}


ProjectTeethJay::ProjectTeethJay() {

	camerapos = glm::vec3(
		distance * m_Scale * cos(verticalAngle) * cos(horizontalAngle),
		-distance * m_Scale * cos(verticalAngle) * sin(horizontalAngle),
		distance* m_Scale* sin(verticalAngle));

	direction = glm::vec3(
		distance * m_Scale * cos(verticalAngle) * cos(horizontalAngle),
		-distance * m_Scale * cos(verticalAngle) * sin(horizontalAngle),
		distance * m_Scale * sin(verticalAngle));

	target = glm::vec3(0,0,0);
	camerapos = (camerapos - target)  * 3.0f;
	dir = target - camerapos;
	camvert = vert = glm::vec3(0,0,1.0f);
	rightvect = glm::cross(dir, camvert);
	rightvect = glm::normalize(glm::vec3(rightvect.x, rightvect.y, 0));
	camvert = glm::normalize(glm::cross(rightvect, dir));

	cameraposPerspective = target + (camerapos - target) * m_Scale;

	forwardVect = glm::normalize(glm::vec3(dir.x, dir.y, 0));







	InitiateBindingFunction();

	glm::vec3 surface[16];

	surface[0] = glm::vec3(3, 0, -3); surface[1] = glm::vec3(1, -1, -3); surface[2] = glm::vec3(-1, 1, -3); surface[3] = glm::vec3(-3, 0, -3);
	surface[4] = glm::vec3(3, -1, -1); surface[5] = glm::vec3(1, 10, -1); surface[6] = glm::vec3(-1, -10, -1); surface[7] = glm::vec3(-3, 1, -1);
	surface[8] = glm::vec3(3, 1, 1); surface[9] = glm::vec3(1, -10, 1); surface[10] = glm::vec3(-1, 10, 1); surface[11] = glm::vec3(-3, -1, 1);
	surface[12] = glm::vec3(3, 0, 3); surface[13] = glm::vec3(1, 1, 3); surface[14] = glm::vec3(-1, -1, 3); surface[15] = glm::vec3(-3, 0, 3);

	mbezier.newSurface(surface);

	ContextInitialisation();

	//	On cré un environnement
	itEnv = environnementList.push_back(Environnement());

	////	On cré un object dedans
	//itEnv->Add(JayObjet(mbezier.GetPointsCopy()));
	//itEnv->itObj = itEnv->objetList.push_back(JayObjet(mbezier.GetPointsCopy()));

	//	On cré des points de lumière, ici on ne va en faire qu'un seul
	itEnv->itLight = itEnv->lightList.push_back(LightJay());

	//  Là y faudrait faire un nouveau shader avec la ref pour le linker à l'objet qu'on veut créer. 
	//	Mais avant, on pourrait être faire une classe matériaux pour les matériaux qu'on veut appliquer aux objets. 


	ShaderInitialisation();	
	BuildTools();
	ConstructionAndUpdate();

	MultipleJays jaySurface(vectices, "Shaders/TransformVertexShader.vertexshader", "Shaders/TextureFragmentShader.fragmentshader");

	itEnv->itView = itEnv->viewerList.push_back(ViewerJay());
	itEnv->itView->NewObject(jaySurface);



	////	This one look like its needless.	//
	//	MultipleJays secondobj;
	//	secondobj.BuildCube(1.0f);
	//	subviewers[1].NewObject(secondobj);
};

void ProjectTeethJay::InitiateBindingFunction()
{
	//	First has to be position 
//	For forward function, 		//	Les chiffres devrait petre des constantes et la liste devrait �tre un dictionnairy.
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Up, _Key(GLFW_KEY_UP, GLFW_KEY_W, m_anything, b_pressed)));

	//	For other directions
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Down, _Key(GLFW_KEY_DOWN, GLFW_KEY_S, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Right, _Key(GLFW_KEY_RIGHT, GLFW_KEY_D, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Left, _Key(GLFW_KEY_LEFT, GLFW_KEY_A, m_anything, b_pressed)));

	//	For grid change "="
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ChangeGridUpper, _Key(GLFW_KEY_EQUAL, 0, m_anything, b_pressed)));

	//	For grid change "-no 5
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ChangeGridLower, _Key(GLFW_KEY_MINUS, 0, m_anything, b_pressed)));

	//	For colormoderelease change "="
//	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ChangeColorMap, _Key(GLFW_KEY_C, 0, m_anything, b_pressed)));

	//	For orthomoderelease change "="
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ChangeOrthoMod, _Key(GLFW_KEY_O, 0, m_anything, b_pressed)));

	//	For camera change in edition mode "="
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_LeftControl, _Key(GLFW_KEY_LEFT_CONTROL, 0, m_anything, b_pressed)));

	//	For activation of the "shift key"
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_LeftShift, _Key(GLFW_KEY_LEFT_SHIFT, 0, m_anything, b_pressed)));

	//	For activation of the "shift key"
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Space, _Key(GLFW_KEY_SPACE, 0, m_anything, b_pressed)));

	//	For activation of the "Exit without saving"
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Exit, _Key(GLFW_KEY_ESCAPE, 0, m_anything, b_pressed)));

	//	Those can be understand by reading the KeyConfig Definition
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_NavRotateTarget, _Key(GLFW_KEY_W, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_NavRotateCamera, _Key(GLFW_KEY_Q, 0, m_anything, b_pressed)));
	//	Faire aussi du pointage
	//	Faire du pointage sur une forme géométrique.
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Etire, _Key(GLFW_KEY_E, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Rotation, _Key(GLFW_KEY_R, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Translation, _Key(GLFW_KEY_T, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_SpecifierPapilleHaut, _Key(GLFW_KEY_5, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_SpecifierCreteHaut, _Key(GLFW_KEY_4, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_SpecifierCentreBas, _Key(GLFW_KEY_6, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ContourCrete, _Key(GLFW_KEY_A, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_EpaisseurLiner, _Key(GLFW_KEY_S, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_EpaisseurBoudin, _Key(GLFW_KEY_D, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_EpaiseureGencive, _Key(GLFW_KEY_F, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_CreerReperes, _Key(GLFW_KEY_B, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_LancerReperes, _Key(GLFW_KEY_N, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_Cachee, _Key(GLFW_KEY_H, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_FonctionOpposee, _Key(GLFW_KEY_LEFT_ALT, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_NavCenterOnSelected, _Key(GLFW_KEY_C, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_NavCenterOnAll, _Key(GLFW_KEY_V, 0, m_anything, b_pressed)));
	m_KeyListing.m_KeyList.insert(make_pair(_KeyConfig_ToggleShowGrid, _Key(GLFW_KEY_G, 0, m_anything, b_pressed)));
}

ProjectTeethJay::~ProjectTeethJay() {
	FreeAllShaders();
	EmptySelector();
	itEnv = nullptr;
};


void ScrollCallback(GLFWwindow* window, double x, double y)
{
	JaySpace::g_diffScale = float(y);
}


void drop_callback(GLFWwindow* window, int count, const char** paths) {
	
	JaySpace::dragNdrop_paths = paths;
	JaySpace::dragNdrop_count = count; 
}


void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	JaySpace::button = button;
	JaySpace::action = action;
	JaySpace::mods = mods;

	if (action == GLFW_PRESS)	{
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			JaySpace::button_left_just_clicked = true;
			JaySpace::button_left = true;
			JaySpace::button_left_just_released = false;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			JaySpace::button_right_just_clicked = true;
			JaySpace::button_right = true;
			JaySpace::button_right_just_released = false;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			JaySpace::button_middle_just_clicked = true;
			JaySpace::button_middle = true;
			JaySpace::button_middle_just_released = false;
			break;
		default: break;
		};
	}
	else {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			JaySpace::button_left = false;
			JaySpace::button_left_just_released = true;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			JaySpace::button_right = false;
			JaySpace::button_right_just_released = true;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			JaySpace::button_middle = false;
			JaySpace::button_middle_just_released = true;
			break;
		default: break;
		};
	}
	//if (action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
	//{
	//	cout << "Shift mod was launched" << endl;
	//}
}

//	Quand on change qqchose aux settings, il faut aussi changer le context et tout réinitialiser...par point de vue.
//	Effectivement, chaque point de vue est différent.

void ProjectTeethJay::ContextInitialisation() {

	//////////////	Start of the configurating opengl and the window that we want	///////////////////////
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


	//	Remove the context of the window
	//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	
	//	For full screen
	//	GLFWwindow* window = glfwCreateWindow(640, 480, "Borderless Fullscreen", glfwGetPrimaryMonitor(), NULL);
	// 
	//	Open a window and create its OpenGL context
	//	window = glfwCreateWindow(windowWidth, windowHeight, "TP2 - Visualisation des donnees scalaires - 04494470 ", glfwGetPrimaryMonitor(), NULL);


	window = glfwCreateWindow(windowWidth, windowHeight, "TP2 - Visualisation des donnees scalaires - 04494470 ", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	//// Initialize ImGui
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	//ImGui::StyleColorsDark(); // Set dark theme

	//// Setup ImGui backends
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init("#version 130");


		// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	//////////////	End of the making of the window	and launch the entire thing	///////////////////////






	//	Setup up of inputs
	// 
	// 
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	if (mTypeNav == TN_playmode) {
		// Hide the mouse and enable unlimited mouvement
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwPollEvents();
		//	Reset cursor position to the center
		glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
	}


	// Enable drop events
	glfwSetDropCallback(window, drop_callback);

	// Input callbacks
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);




	//Set up of the screen and way to calculates on it.
	// 
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//// CullCull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	//glCullFace(GL_FRONT_AND_BACK);


	// The building of a screen we can project on
	g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
};

void ProjectTeethJay::ShaderInitialisation() {
	GLenum err;
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "OpenGL error after loading texture: " << err << std::endl;
	}

	//	Tools for selection

	pickingShader = LoadShaders("Shaders/Selection.vertexshader", "Shaders/Selection.fragmentshader");
		
	selectFrameBuffer = SelectionFramebuffer(windowWidth, windowHeight);


//	initText2D("Holstein.DDS");	//	Not sure this is working

	//	This shader is for calculation purpose a 2x2 quad plate
	//	If we dont modify anything, it will simply show the texture that was draw in the Framebuffer2Texture it was destined to.
	CreateNewShader("QuadProgram", "Shaders/Passthrough.vertexshader", "Shaders/Texture.fragmentshader");
	ptrShad->NewUniformTexture("renderedTexture",(texID = glGetUniformLocation(quad_programID, "renderedTexture")));

	// Create and compile our GLSL program from the shaders and dumb it into a structure to keep it.
	CreateNewShader("JaySurface", "Shaders/TransformVertexShader.vertexshader", "Shaders/TextureFragmentShader.fragmentshader");
	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->AddTexture("uvtemplate.DDS", "myTextureSampler");
	ptrShad->NewUniform("colomapmod", &colormapMod, UniformType::typeint);
	ptrShad->NewUniform("minToClamp", &minToClamp, UniformType::typefloat);
	ptrShad->NewUniform("maxToClamp", &maxToClamp, UniformType::typefloat);

	////	Outline Shader for selection of objects
	//CreateNewShader("Outline", "Shaders/Outline.vertexshader", "Shaders/Outline.fragmentshader");
	//ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	//ptrShad->NewUniform("outlineThickness", &outlineThickness, UniformType::typefloat);
	//ptrShad->NewUniform("outlineColor", &outlineColor, UniformType::color3);


	//	Outline Shader for selection of objects
	CreateNewShader("SimpleOutline", "Shaders/SimpleOutline.vertexshader", "Shaders/SimpleOutline.fragmentshader");
	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->NewUniform("outlineColor", &outlineColor, UniformType::color3);


	//	Outline Shader for color of basci tools
	CreateNewShader("abasic", "Shaders/abasic.vertexshader", "Shaders/abasic.fragmentshader");
	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->NewUniformUsingObjectVar("objectColor", TypeObjetVar::typeCouleur);


	//uniform mat4 M;
	//uniform mat4 V;
	//uniform mat4 P;
	//uniform float outlineThickness; // Control the thickness of the outline (e.g., 0.05)

	//uniform vec4 outlineColor; // e.g., vec4(1.0, 1.0, 0.0, 1.0) for yellow


	//	A very basic shader for the teeth model
	CreateNewShader("Teeth", "Shaders/Teeth.vertexshader", "Shaders/Teeth.fragmentshader");
	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->NewUniform("lightDirection", &lightdir, UniformType::glmvec3);
	ptrShad->NewUniform("lightColor", &lightCol, UniformType::color3);
	ptrShad->NewUniform("toothColor", &toothCol, UniformType::color3);
	ptrShad->NewUniform("viewPos", &camerapos, UniformType::glmvec3);

	//	A realtime subsurfacescatering shader for more natural teeth edition.
	CreateNewShader("RealtimeSSSshader", "Shaders/RealtimeSSSshader.vertexshader", "Shaders/RealtimeSSSshader.fragmentshader");	
	AddThisPrePassToThisShader("DepthVertexSource", "RealtimeSSSshader", "Shaders/DepthVertexSource.vertexshader", "Shaders/DepthVertexSource.fragmentshader");
	NewUniformTexture("RealtimeSSSshader", "backDepthTex", OutputShaderToNewTexture("DepthVertexSource"));

	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->NewUniform("lightPos", &lightPos, UniformType::glmvec3);
	ptrShad->NewUniform("lightColor", &lightCol, UniformType::color3);
	ptrShad->NewUniform("subsurfaceColor", &camerapos, UniformType::glmvec3);
	ptrShad->NewUniform("lightIntensity", &lightIntensity, UniformType::typefloat);
	ptrShad->NewUniform("objectColor", &toothCol, UniformType::color3);
	ptrShad->NewUniform("density", &shaddensity, UniformType::typefloat);
	ptrShad->NewUniform("screenSize", &screenSize, UniformType::glmvec2);




	/*
	{
	// C++ struct matching the GLSL Light struct
struct Light {
    int type;         // 0: directional, 1: point
    glm::vec3 position;   // Used for point lights
    glm::vec3 direction;  // Used for directional lights
    glm::vec3 color;      // Light color (RGB)
};

// Function to set the lights uniform array in the shader
void setShaderLights(GLuint shaderProgram, const std::vector<Light>& lights, int maxLights) {
    // Ensure we don't exceed MAX_LIGHTS
    int numLights = std::min(static_cast<int>(lights.size()), maxLights);

    // Set the number of lights
    glUseProgram(shaderProgram);
    GLint numLightsLoc = glGetUniformLocation(shaderProgram, "numLights");
    glUniform1i(numLightsLoc, numLights);

    // Set each light's properties in the lights[MAX_LIGHTS] array
    for (int i = 0; i < numLights; ++i) {
        const Light& light = lights[i];

        // Construct the uniform name for each field (e.g., "lights[0].type")
        std::string baseName = "lights[" + std::to_string(i) + "]";

        // Set type
        GLint typeLoc = glGetUniformLocation(shaderProgram, (baseName + ".type").c_str());
        glUniform1i(typeLoc, light.type);

        // Set position
        GLint posLoc = glGetUniformLocation(shaderProgram, (baseName + ".position").c_str());
        glUniform3fv(posLoc, 1, &light.position[0]);

        // Set direction
        GLint dirLoc = glGetUniformLocation(shaderProgram, (baseName + ".direction").c_str());
        glUniform3fv(dirLoc, 1, &light.direction[0]);

        // Set color
        GLint colorLoc = glGetUniformLocation(shaderProgram, (baseName + ".color").c_str());
        glUniform3fv(colorLoc, 1, &light.color[0]);
    }

    // Optional: Set remaining lights to "off" (type = -1 or zeroed-out properties) to avoid undefined behavior
    for (int i = numLights; i < maxLights; ++i) {
        std::string baseName = "lights[" + std::to_string(i) + "]";
        GLint typeLoc = glGetUniformLocation(shaderProgram, (baseName + ".type").c_str());
        glUniform1i(typeLoc, -1); // Invalid type to indicate unused light
        GLint posLoc = glGetUniformLocation(shaderProgram, (baseName + ".position").c_str());
        glUniform3f(posLoc, 0.0f, 0.0f, 0.0f);
        GLint dirLoc = glGetUniformLocation(shaderProgram, (baseName + ".direction").c_str());
        glUniform3f(dirLoc, 0.0f, 0.0f, 0.0f);
        GLint colorLoc = glGetUniformLocation(shaderProgram, (baseName + ".color").c_str());
        glUniform3f(colorLoc, 0.0f, 0.0f, 0.0f);
    }
	}
	
	*/


	CreateNewShader("IsoContour", "Shaders/IsocontourVertShader.vertexshader", "Shaders/IsocontourFragShader.fragmentshader");
	
	// Get a handle for our "MVP" uniform
	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0]);
	ptrShad->NewUniform("inColor", &isoColor, UniformType::color3);





///////////	Shader program for the monkey suzanne

	CreateNewShader("MonkeySuzanne", "Shaders/StandardShadingRTT.vertexshader", "Shaders/StandardShadingRTT.fragmentshader");

	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	//ptrShad->NewUniform("myTextureSampler", ptrShad->AddTexture("uvmap.DDS"), UniformType::typeTexture);
	
	ptrShad->AddTexture("uvmap.DDS", "myTextureSampler");

	ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);
	ptrShad->NewUniform("LightPosition_worldspace", &lightPos, UniformType::light3);
	


	 //	For the monkey suzanne
	itEnv->itObj = itEnv->Add(JayObjet());

	itEnv->itShad = itEnv->shaderList.find("MonkeySuzanne");
	itEnv->itObj->Bind(itEnv->itShad);

	bool res = loadOBJ("suzanne.obj", verticesR2T, uvsR2T, normalsR2T);
	// Load it into a VBO
	indexVBO(verticesR2T, uvsR2T, normalsR2T, indices, indexed_vertices, indexed_uvs, indexed_normals);

	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indices, GL_TRIANGLES, TypeData::indices);
	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_vertices, GL_TRIANGLES, TypeData::vertices, 0);
	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_normals, GL_TRIANGLES, TypeData::normals, 2);
	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_uvs, GL_TRIANGLES, TypeData::uvs, 1);

	
	///////////	end of the shader program for the monkey suzanne

}

void ProjectTeethJay::BuildTools()
{
	BuildPointer();

	BuildGrid();
}

void ProjectTeethJay::BuildGrid() {
	//	We want to build a grid of 2D points, that will be used to create the surface of the teeth.
	//	We will use a bezier surface to create the surface of the teeth.
	//	The grid will be used to create the surface of the teeth.

	vector<glm::vec3> gridBorders;

	for (int i = -10; i <= 10; i++)
	{
		gridBorders.push_back(glm::vec3(i, -11, 0));
		gridBorders.push_back(glm::vec3(i, 11, 0));

		gridBorders.push_back(glm::vec3(-11, i, 0));
		gridBorders.push_back(glm::vec3(11, i, 0));

	}

	AddTool(JayObjet());
	itEnv->itToolObj->name = "Grid";
	itEnv->itToolObj->objColor = glm::vec3(0.6f, 0.6f, 0.6f);
	itEnv->itToolObj->Bind(itEnv->shaderList.find("abasic"));
	itEnv->itToolObj->DumpTheseDatasIntoBufferForGPU(gridBorders, GL_LINES, TypeData::vertices, 0);
}

void ProjectTeethJay::BuildPointer()
{
	glm::vec3 pointerPos(0, 0, 0);

	AddTool(JayObjet());
	itEnv->itToolObj->Bind(itEnv->shaderList.find("abasic"));
	itEnv->itToolObj->objColor = glm::vec3(0.7f, 0.7f, 0.7f);

	UpdatePointer(pointerPos);
}


void ProjectTeethJay::UpdatePointer(glm::vec3 newCoord)
{
	pointerPoints.clear();

	itEnv->itToolObj = itEnv->toolObjetList[0];

	pointerPoints.push_back(newCoord + glm::vec3(1, 0, 0));
	pointerPoints.push_back(newCoord + glm::vec3(-1, 0, 0));
	pointerPoints.push_back(newCoord + glm::vec3(0, 1, 0));
	pointerPoints.push_back(newCoord + glm::vec3(0, -1, 0));
	pointerPoints.push_back(newCoord + glm::vec3(0, 0, 1));
	pointerPoints.push_back(newCoord + glm::vec3(0, 0, -1));

	itEnv->itToolObj->DumpTheseDatasIntoBufferForGPU(pointerPoints, GL_LINES, TypeData::vertices, 0);
}



emlist<JayObjet>::iterator ProjectTeethJay::AddTool(JayObjet newObj)
{
	return itEnv->itToolObj = itEnv->toolObjetList.push_back(newObj);
}


void ProjectTeethJay::ConstructionAndUpdate() {

	//	The initial construction should not occur here.
	//	Ici, ça devrait être l'upgrade des formes géométrique selon la modification des données. 

	if (!gridUpdated) {
		gridUpdated = true;

		vectices.resize(0);
		uvs.resize(0);

		minToClamp = 6;
		maxToClamp = 0;

		//MatrixXd _2Dgrid;
		//_2Dgrid.resize(division, division);

		_2DTexture.resize(division + 1, division + 1, 3);

		cimg_forXY(_2DTexture, _x, _y)
		{
			float u = (float) 1.f / division * _x;
			float v = (float) 1.f / division * _y;
			
			//	Calcule la position x, y, z, selon les position u/v données à la surface de bézier
			glm::vec3 pos = mbezier.pos(u, v);

			_2DTexture(_x, _y, 0) = pos.x;
			_2DTexture(_x, _y, 1) = pos.y;
			_2DTexture(_x, _y, 2) = pos.z;

			minToClamp = std::min(minToClamp, _2DTexture(_x, _y, 1));
			maxToClamp = std::max(maxToClamp, _2DTexture(_x, _y, 1));
		}

		for (int i = 0; i < division; ++i)
		{
			for (int j = 0; j < division; ++j)
			{
				glm::vec3 points[4];
				points[0] = glm::vec3(_2DTexture(i, j + 1, 0), _2DTexture(i, j + 1, 2), _2DTexture(i, j + 1, 1));
				points[1] = glm::vec3(_2DTexture(i, j, 0), _2DTexture(i, j, 2), _2DTexture(i, j, 1));
				points[2] = glm::vec3(_2DTexture(i + 1, j, 0), _2DTexture(i + 1, j, 2), _2DTexture(i + 1, j, 1));
				points[3] = glm::vec3(_2DTexture(i + 1, j + 1, 0), _2DTexture(i + 1, j + 1, 2), _2DTexture(i + 1, j + 1, 1));

				vectices.push_back(points[0]);
				vectices.push_back(points[1]);
				vectices.push_back(points[2]);
				vectices.push_back(points[0]);
				vectices.push_back(points[2]);
				vectices.push_back(points[3]);
			}
		}


		//	Bind the shader to the object we want to be bind with
	//	itEnv->itObj = itEnv->Add(JayObjet());
	//	itEnv->itShad = itEnv->shaderList.find("Teeth");

	//	itEnv->itObj->Bind(itEnv->itShad);

	////	itEnv->itObj = itEnv->objetList[0];
	//	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(vectices,GL_TRIANGLES, TypeData::vertices, 0);
	////	itEnv->itObj->CalculateSmoothShading();
	//	itEnv->itObj->CalculateFlatShading();
	//	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(itEnv->itObj->normals, GL_TRIANGLES, TypeData::normals, 1);

	}

	//	Load of a small stl file.
	std::vector<glm::vec3> vects;
	std::vector<uint32_t> incs;

	std::vector<uint32_t> triangles;

	StlLoader::loadSTL("Contacts-24.stl", vects, triangles);
	//	StlLoader::loadSTL("cube.stl", vects, triangles);

	glm::vec3 maxs(-16000000, -16000000, -16000000);
	glm::vec3 mins(16000000, 16000000, 16000000);
	glm::vec3 average(0, 0, 0);

	int i = 0;
	int j = i + 1;

	for (; i < vects.size(); i++, j++)
	{
		maxs = glm::max(maxs, vects[i]);
		mins = glm::min(mins, vects[i]);

		average = average * float(i) / float(j) + vects[i] / float(j);
	}

	for (int i = 0; i < vects.size(); i++)
	{
		vects[i] = (vects[i] - average);	//	We want to center the object on the origin.]
	}
	maxs = maxs - average;	//	We want to center the object on the origin.
	mins = mins - average;	//	We want to center the object on the origin.

	// Function to simplify vertices and generate indices
	SimplifiedMesh sv = simplifyVertices(vects, float(EPSILON));

	itEnv->itShad = itEnv->shaderList.find("Teeth");

	itEnv->itObj = itEnv->Add(JayObjet());
	itEnv->itObj->Bind(itEnv->itShad);

	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(vects, GL_TRIANGLES, TypeData::vertices, 0);
	itEnv->itObj->CalculateFlatShading();
//	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(sv.vertices, GL_TRIANGLES, TypeData::vertices, 0);
	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(itEnv->itObj->normals, GL_TRIANGLES, TypeData::normals, 1);
//	itEnv->itObj->DumpTheseDatasIntoBufferForGPU(sv.indices, GL_TRIANGLES, TypeData::indices);

	//indexVBO(verticesR2T, uvsR2T, normalsR2T, indices, indexed_vertices, indexed_uvs, indexed_normals);

	//itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indices, GL_TRIANGLES, TypeData::indices);
	//itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_vertices, GL_TRIANGLES, TypeData::vertices, 0);
	//itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_normals, GL_TRIANGLES, TypeData::normals, 2);
	//itEnv->itObj->DumpTheseDatasIntoBufferForGPU(indexed_uvs, GL_TRIANGLES, TypeData::uvs, 1);


	itEnv->itObj->center = /*average*/ glm::vec3(0, 0, 0);
	itEnv->itObj->maxs = maxs;
	itEnv->itObj->mins = mins;


};

void ProjectTeethJay::HighwayToGPU() {
	//	Ok, so here are all the physic calculation we could perform by the graphic card through compute shader or shaders in general
};

bool ProjectTeethJay::SetupForDisplay() {
	return ComputeMatricesFromInputs() ? true : false;
};

void ProjectTeethJay::Display_Loop() {
	////Set up of the screen and way to calculates on it.
	//// Start ImGui frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();

	//// Example ImGui window
	//ImGui::Begin("Hello, ImGui!");
	//ImGui::Text("This is a test window.");
	//if (ImGui::Button("Click Me")) {
	//	printf("Button clicked!\n");
	//}
	//ImGui::End();

	//// Render
	//ImGui::Render();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glDisable(GL_STENCIL_TEST);

	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, windowWidth, windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//	Our matrices are linked to the shaders already
	ModelMatrix = glm::mat4(1.0);
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	//	Pour l'instant, y a rien dans cette fonction

	DisplayObjet();
	DisplayTools();

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
};




// Assuming you have a shader program and VAO setup
void ProjectTeethJay::DisplayObjectAsSelected(emlist<JayObjet>::iterator itObj, glm::vec3 color2use) {

	// Enable stencil testing
	glEnable(GL_STENCIL_TEST);

	// Step 1: Render object normally, writing to stencil buffer
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // All fragments pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Write 1 to stencil
	glStencilMask(0xFF); // Enable writing to stencil buffer
	glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer

	//	Draw the object normally
	itObj->Display();

	// Step 2: Render outline
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Pass where stencil is not 1
	glStencilMask(0x00); // Disable writing to stencil buffer
	glDisable(GL_DEPTH_TEST); // Disable depth test for outline

	itEnv->itShad = itEnv->shaderList.find("SimpleOutline");

	// Use outline shader program
	glUseProgram(itEnv->itShad->second.id());

	// Scale model matrix for outline
	glm::mat4 outlineModel = glm::scale(ModelMatrix, glm::vec3(outlineThickness));
	
	//ptrShad->getUniformLocationOfTransformMatrices(&MVP[0][0], &ProjectionMatrix[0][0], &ViewMatrix[0][0], &ModelMatrix[0][0]);

	// Set uniforms for outline
	glUniformMatrix4fv(glGetUniformLocation(itEnv->itShad->second.id(), "M"), 1, GL_FALSE, &outlineModel[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(itEnv->itShad->second.id(), "V"), 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(itEnv->itShad->second.id(), "P"), 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUniform3fv(glGetUniformLocation(itEnv->itShad->second.id(), "outlineColor"), 1, &color2use[0]);

	//itEnv->itShad->second.PassMatrixes();
	//itEnv->itShad->second.PassVariables(&itObj);

	// Draw scaled object for outline
	glBindVertexArray(itObj->vertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, itObj->vertices.size());
	glBindVertexArray(0);

	// Clean u
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
}

void ProjectTeethJay::DisplayObjet()
{
	emlist<JayObjet>::iterator itObj;

	for (itObj = itEnv->objetList.begin(); itObj != itEnv->objetList.before_begin() && itObj != itEnv->objetList.end(); itObj++)
	{
		if (itObj->selected)
			DisplayObjectAsSelected(itObj, outlineColor);
		else
			if (itObj->mouseOver)
				DisplayObjectAsSelected(itObj, outlineMouseOverColor);
			else
				itObj->Display();

	}
}

void ProjectTeethJay::DisplayTools()
{
	itEnv->DisplayTools();
}

void ProjectTeethJay::CleanUp() {

	//// Cleanup
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();


	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteVertexArrays(1, &VertexArrayR2TID);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbufferR2T);
	glDeleteBuffers(1, &uvbufferR2T);
	glDeleteBuffers(1, &normalbufferR2T);
	glDeleteBuffers(1, &elementbufferR2T);
	glDeleteProgram(programR2T_ID);
	glDeleteTextures(1, &TextureR2T);

	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &renderedTexture);
	glDeleteRenderbuffers(1, &depthrenderbuffer);
	glDeleteBuffers(1, &quad_vertexbuffer);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
};


bool ProjectTeethJay::LoopConditions() {
	return 
		//glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0;
};

float ProjectTeethJay::Height(float x, float y) {
	return 2 * exp(-(x*x + y*y)) + exp(-((x - 3) * (x - 3) + (y - 3) * (y - 3)));
}


bool ProjectTeethJay::ComputeMatricesFromInputs() {

	////////////		Cette fonction est à changer 
	//	On doit effectivement prendre en considération les inputs mais aussi le type d'édition
	//	
	// 
	////////////////////////////
	
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	xpos = ypos = 0;
	glfwGetCursorPos(window, &xpos, &ypos);

	//	Calculate the difference with the other frame and flush the old coordonnates
	glm::vec2 diff = SetNewScreenPos(glm::vec2(xpos, ypos));
	glm::vec2 screenpos = diff;
		
	Pos = glm::vec2(xpos - windowWidth / 2.0f, windowHeight / 2.0f - ypos);

	ratiox = Pos.x / (windowWidth / 2.0f);
	ratioy = Pos.y / (windowHeight / 2.0f);

	if (mTypeNav == TN_playmode )
	{
		diff.x = diff.x * sensibilityControl;
		diff.y = diff.y * sensibilityControl;
	}	

	if (m_KeyListing.IsActivated(window, _KeyConfig_Space))
	{
		JaySpace::g_diffScale = JaySpace::g_diffScale * precisionControler;
		diff.x = (float) diff.x * precisionControler;
		diff.y = (float) diff.y * precisionControler;
	}

	JaySpace::g_Scale -= JaySpace::g_MouseWheelScale * JaySpace::g_diffScale;
	JaySpace::g_Scale = std::max(0.01f, JaySpace::g_Scale);

	if (m_KeyListing.IsActivated(window, _KeyConfig_Exit))
	{
		glfwDestroyWindow(window);
		return true;
	}

	xpos = -diff.x + windowWidth / 2;
	ypos = -diff.y + windowHeight / 2;

	GatherInputs();

	if (mTypeNav == TN_playmode) {

		// Reset mouse position for next frame
		//	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(windowWidth / 2 - xpos);
		verticalAngle += mouseSpeed * float(windowHeight / 2 - ypos);

		if (m_KeyListing.IsActivated(window, _KeyConfig_NavRotateCamera))
		{
			camerapos = JaySpace::Rotation(camerapos, target, vert, diff.x / 90 * PI);
			camerapos = JaySpace::Rotation(camerapos, target, rightvect, diff.y / 90 * PI);
		}
		else
			if (m_KeyListing.IsActivated(window, _KeyConfig_NavRotateTarget))
			{
				target = JaySpace::Rotation(target, camerapos, vert, diff.x / 90 * PI);
				target = JaySpace::Rotation(target, camerapos, rightvect, diff.y / 90 * PI);
			}

		camvert = JaySpace::Rotation(camvert, vert, diff.x / 90.0f * PI);
		camvert = JaySpace::Rotation(camvert, rightvect, diff.y / 90.0f * PI);

		//rightvect = JaySpace::Rotation(rightvect, vert, diff.x / 90.0f * PI);
		//rightvect = JaySpace::Rotation(rightvect, rightvect, diff.y / 90.0f * PI);

	}

	cameraposPerspective = target + (camerapos - target) * m_Scale;

	dir = target - camerapos;
	forwardVect = glm::normalize(glm::vec3(dir.x, dir.y, 0));
	
	//rightvect = JaySpace::Contact_Droite_Plan(camerapos + rightvect, dir, camerapos, dir);
	//rightvect = glm::normalize(rightvect);

	rightvect = glm::cross(dir, camvert);
	rightvect = glm::normalize(glm::vec3(rightvect.x, rightvect.y, 0));
	camvert = glm::normalize(glm::cross(rightvect, dir));

	//	Calculs pour les caméras
	distLength = JaySpace::Magnitude(target - cameraposPerspective);
	xFoV = initialFoV / float(windowHeight) * float(windowWidth);
	screenDim = glm::vec2(0, distLength * tan(initialFoV / 2.0f / 180.0f * PI));
	screenDim.x = screenDim.y * float(windowWidth) / float(windowHeight);
	screenDimHalf = screenDim / 2.0f;


	//	Doivent être recalculé en fonction de chaque objet.
	if (OrthoMod) {
		coordScalar = glm::vec2(ratiox, ratioy) * screenDim * JaySpace::g_Scale * m_Scale;
		clickdir = target + rightvect * coordScalar.x + camvert * coordScalar.y;

		ptaimOnPlan = glm::vec3(JaySpace::Contact_Droite_Plan(clickdir, dir, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)));

		ViewMatrix = glm::lookAt(camerapos, target, camvert);
		ProjectionMatrix = glm::ortho(
			-screenDim.x * JaySpace::g_Scale * m_Scale,
			screenDim.x* JaySpace::g_Scale * m_Scale,
			-screenDim.y * JaySpace::g_Scale * m_Scale,
			screenDim.y * JaySpace::g_Scale * m_Scale,
			-150.f, 150.f);
	}
	else
	{
		coordScalar = glm::vec2(ratiox, ratioy) * screenDim;
		clickdir = target + rightvect * coordScalar.x + camvert * coordScalar.y;
		ptaimOnPlan = glm::vec3(JaySpace::Contact_Droite_Plan(cameraposPerspective, clickdir - cameraposPerspective, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)));

		ViewMatrix = glm::lookAt(cameraposPerspective, target, camvert);
		ProjectionMatrix = glm::perspective(glm::radians(initialFoV /* * m_Scale*/), float(windowWidth) / float(windowHeight), 0.001f, 150.0f);
	}


	if (mTypeNav != TN_playmode)
		UpdatePointer(ptaimOnPlan);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	RegulateInputs();

	return false;
}

vector<glm::vec3> ProjectTeethJay::MakeCurveSurface()
{
	vector<glm::vec3> surface2return;
	   
	for (int i = 0; i < division; i++)
	{
		for (int j = 0; j < division; j++)
		{
			glm::vec3 points[4];
			points[0] = glm::vec3(_2DTexture(i, j + 1, 0), _2DTexture(i, j + 1, 1), _2DTexture(i, j + 1, 2));
			points[1] = glm::vec3(_2DTexture(i, j, 0), _2DTexture(i, j, 1), _2DTexture(i, j, 2));
			points[2] = glm::vec3(_2DTexture(i + 1, j, 0), _2DTexture(i + 1, j, 1), _2DTexture(i + 1, j, 2));
			points[3] = glm::vec3(_2DTexture(i + 1, j + 1, 0), _2DTexture(i + 1, j + 1, 1), _2DTexture(i + 1, j + 1, 2));

			vectices.push_back(points[0]);
			vectices.push_back(points[1]);
			vectices.push_back(points[2]);
			vectices.push_back(points[0]);
			vectices.push_back(points[2]);
			vectices.push_back(points[3]);
		}
	}

	return surface2return;
}



//
//std::vector<std::string> extract_stl_from_zip(const std::string& zip_path) {
//	std::vector<std::string> stl_paths;
//
//	// Read entire ZIP into memory
//	std::ifstream file(zip_path, std::ios::binary | std::ios::ate);
//	if (!file.is_open()) {
//		std::cerr << "Failed to open ZIP: " << zip_path << std::endl;
//		return stl_paths;
//	}
//
//	auto size = file.tellg();
//	std::vector<uint8_t> zip_data(size);
//	file.seekg(0, std::ios::beg);
//	file.read(reinterpret_cast<char*>(zip_data.data()), size);
//	file.close();
//
//	mz_zip_archive zip_archive = {};
//	if (!mz_zip_reader_init_mem(&zip_archive, zip_data.data(), zip_data.size(), 0)) {
//		std::cerr << "Failed to init ZIP reader for: " << zip_path << std::endl;
//		return stl_paths;
//	}
//
//	// Get number of files in ZIP
//	int num_files = mz_zip_reader_get_num_files(&zip_archive);
//	for (int i = 0; i < num_files; ++i) {
//		mz_zip_archive_file_stat file_stat;
//		if (mz_zip_reader_file_stat(&zip_archive, i, &file_stat) == 0) {
//			std::string filename(file_stat.m_filename);
//			if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".stl") {
//				// Found STL file
//
//				// Get temp directory (platform-agnostic)
//				const char* temp_dir = std::getenv("TMPDIR");  // macOS/Linux
//				if (!temp_dir) temp_dir = std::getenv("TMP");  // Windows
//				if (!temp_dir) temp_dir = "/tmp";  // Fallback
//				std::string temp_path = std::string(temp_dir) + "/" + filename;
//
//				// Extract to temp file
//				if (mz_zip_reader_extract_to_file(&zip_archive, i, temp_path.c_str(), 0)) {
//					stl_paths.push_back(temp_path);
//					std::cout << "Extracted STL: " << temp_path << std::endl;
//				}
//				else {
//					std::cerr << "Failed to extract: " << filename << std::endl;
//				}
//			}
//		}
//	}
//
//	mz_zip_reader_end(&zip_archive);
//	return stl_paths;
//}


void ProjectTeethJay::GatherInputs()
{
	//	std::chrono::system_clock::now();

	m_Scale = JaySpace::g_Scale;
	//	JaySpace::g_MouseWheelScale;


	for (int i = 0; i < JaySpace::dragNdrop_count; ++i) {
		std::string path(JaySpace::dragNdrop_paths[i]);

		//miniz_cpp::zip_file file(path);
		//file.printdir();

		//cout << path << endl;

		////pathforallfolders;
		//if (path.size() >= 4 && path.substr(path.size() - 4) == ".zip") {

		//}
		//if (path.size() >= 4 && path.substr(path.size() - 4) == ".zip") {
		//	// Handle ZIP: Extract STL and load
		//	std::vector<std::string> stl_paths = extract_stl_from_zip(path);
		//	for (const auto& stl_path : stl_paths) {
		//		loadstl(stl_path.c_str());  // Assuming loadstl takes a const char* path
		//	}
		//}
		//else if (path.substr(path.size() - 4) == ".stl") {
		//	// Optional: Direct STL drop support
		//	loadstl(path.c_str());
		//}
	}


	if (JaySpace::button_left_just_clicked || JaySpace::button_left_just_released)
	{
		//	cout << "Line of creation should be here" << endl;
		cout << "Click here" << endl;
	}

	//	MouseOver selection for lighter color
	{
		EmptyMouseOverSelection();

		selectedId = selectFrameBuffer.selectObject(&(itEnv->objetList), (int)Pos.x, (int)Pos.y,
			windowWidth, windowHeight, pickingShader);

		if (selectedId != 13421772 && selectedId != -1) {
			SearchForItemWithID_ForMosueOver(selectedId);
		}
	}

	if (JaySpace::button_left_just_clicked)
	{		
		//	static std::vector<SceneObject> objects; // Your scene objects
		//static GLuint pickingShader; // Compiled picking shader

		selectedId = selectFrameBuffer.selectObject(&(itEnv->objetList), (int)Pos.x, (int)Pos.y,
		windowWidth, windowHeight, pickingShader);

		if (selectedId != -1) {
			SearchForItemWithID_(selectedId);
		}
		else
		{
			EmptySelection();
		}
	}



	//{
	//	// Move forward
	////	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	if (m_KeyListing.IsActivated(window, _KeyConfig_Up)) {
	//		target += 0.1f * forwardVect;
	//		camerapos += 0.1f * forwardVect;
	//	}
	//	// Move backward
	//	if (m_KeyListing.IsActivated(window, _KeyConfig_Down)) {
	//		target -= 0.1f * forwardVect;
	//		camerapos -= 0.1f * forwardVect;
	//	}
	//	// Strafe right
	//	if (m_KeyListing.IsActivated(window, _KeyConfig_Right)) {
	//		target += 0.1f * rightvect;
	//		camerapos += 0.1f * rightvect;
	//	}
	//	// Strafe left
	//	if (m_KeyListing.IsActivated(window, _KeyConfig_Left)) {
	//		target -= 0.1f * rightvect;
	//		camerapos -= 0.1f * rightvect;
	//	}
	//}

	if (m_KeyListing.IsActivated(window, _KeyConfig_ChangeGridUpper)) {
		division++;

		gridUpdated = false;
	}

	if (m_KeyListing.IsActivated(window, _KeyConfig_ChangeGridLower) && division != 1) {
		division--;
		division = std::max(1, division);

		gridUpdated = false;
	}


	//if (m_KeyListing.IsActivated(window, _KeyConfig_ChangeColorMap)) {
	//	if (colormapModeReleased) {
	//		colormapModeReleased = false;
	//		colormapMod++;
	//		if (colormapMod > 4) colormapMod = 0;
	//	}
	//}
	//else
	//{
	//	colormapModeReleased = true;
	//}


	if (m_KeyListing.IsActivated(window, _KeyConfig_ChangeOrthoMod)) {
		if (OrthoModReleased) {
			OrthoModReleased = false;
			OrthoMod = !OrthoMod;
		}
	}
	else
	{
		OrthoModReleased = true;
	}
	;

	CheckOnKeyFunction(_KeyConfig_ToggleShowGrid, std::bind(&ProjectTeethJay::ToggleGrid, this));


	if (m_KeyListing.IsActivated(window, _KeyConfig_NavRotateCamera))
	{
		if (m_KeyListing.IsRecentlyActivated(_KeyConfig_NavRotateCamera))
		{
			tempoldnav = mTypeNav;
		}
		ChangeTypeNavTo(mTypeNav = TN_playmode);
	}
	else
	{
		if (m_KeyListing.IsJustReleased(_KeyConfig_NavRotateCamera))
			ChangeTypeNavTo(mTypeNav = tempoldnav);

		if (m_KeyListing.IsActivated(window, _KeyConfig_NavRotateTarget))
		{
			if (m_KeyListing.IsRecentlyActivated(_KeyConfig_NavRotateTarget))
			{
				tempoldnav = mTypeNav;
			}
			ChangeTypeNavTo(mTypeNav = TN_playmode);
		}
		else
		{
			if (m_KeyListing.IsJustReleased(_KeyConfig_NavRotateTarget))
				ChangeTypeNavTo(mTypeNav = tempoldnav);
		}
	}


	CheckOnKeyFunction(_KeyConfig_NavCenterOnSelected, std::bind(&ProjectTeethJay::MoveCamToSeletingObject_KeepParallelism, this));

	//CheckOnKeyFunction(_KeyConfig_Translation, std::bind(&ProjectTeethJay::MoveCamToSeletingObject_KeepParallelism, this));

}

bool ProjectTeethJay::ToggleGrid()
{
	itEnv->itToolObj = itEnv->toolObjetList[1];	//	Hard coded dont u think?
	itEnv->itToolObj->active = !itEnv->itToolObj->active;

	isShowGrid = !isShowGrid;
	return isShowGrid;
};


bool ProjectTeethJay::CheckOnKeyFunction(GLint keyfunction2Check, std::function<void()> func2Launch)
{
	if (m_KeyListing.IsActivated(window, keyfunction2Check)
		&& (m_KeyListing.IsRecentlyActivated(keyfunction2Check)))
	{
		func2Launch();
	}
	else
		if (m_KeyListing.IsJustReleased(keyfunction2Check))
		{
			return false;
		}
	return true;
}

void ProjectTeethJay::MoveCamToSeletingObject_KeepParallelism()
{
	if (itEnv->selectedObjetList.size() > 0)
	{
		glm::vec3 target2camdir = camerapos - target;
		//initialFoV* m_Scale

		glm::vec3 newTarget = (*itEnv->selectedObjetList[0])->center;

		//	1 find bigest angle to adapt on x
		//	Find biggest angle to adapt on y
		//	Get the one that has the most adaptation to do (take the biggest front the mins and maxs)

		glm::vec3 center = (*itEnv->selectedObjetList[0])->center;
		glm::vec3 maxs = (*itEnv->selectedObjetList[0])->maxs;
		glm::vec3 mins = (*itEnv->selectedObjetList[0])->mins;

		vector<glm::vec3> listCorners;

		//	The 8 corners encompassing volumes
		listCorners.push_back(glm::vec3(maxs.x, maxs.y, maxs.z));
		listCorners.push_back(glm::vec3(mins.x, mins.y, mins.z));

		listCorners.push_back(glm::vec3(mins.x, mins.y, maxs.z));
		listCorners.push_back(glm::vec3(maxs.x, maxs.y, maxs.z));
		listCorners.push_back(glm::vec3(maxs.x, mins.y, maxs.z));
		listCorners.push_back(glm::vec3(mins.x, maxs.y, mins.z));
		listCorners.push_back(glm::vec3(maxs.x, mins.y, mins.z));
		listCorners.push_back(glm::vec3(maxs.x, maxs.y, mins.z));

		//	On doit calculer quelle des mins et maxs vont donner le plus grand ratio par rapport au FOV, donc faire attention
		//	à x vs y

		glm::vec2 biggestFovCoordNeeded(0, 0);
		float aimedFOV = initialFoV / 0.9f/2.0f/180*PI;
		int indicex = -1, indicey = -1;

		for (int i = 0; i < listCorners.size(); i++)
		{
			glm::vec2 coord2compare = JaySpace::Coord3DToScreenFov(
				listCorners[0],
				initialFoV,
				newTarget + target2camdir,
				newTarget,
				rightvect
			);
			coord2compare = glm::abs(coord2compare);

			if (coord2compare.x > biggestFovCoordNeeded.x)
			{
				biggestFovCoordNeeded.x = coord2compare.x;
				indicex = i;
			}

			if (coord2compare.y > biggestFovCoordNeeded.y)
			{
				biggestFovCoordNeeded.y = coord2compare.y;
				indicey = i;
			}
		}
		float b;
		int indexToUse = (biggestFovCoordNeeded.x > biggestFovCoordNeeded.y) ?
			(indicex, b = biggestFovCoordNeeded.x) :
			(indicey, b = biggestFovCoordNeeded.y);

		float G = JaySpace::Magnitude(listCorners[indexToUse] - camerapos);
		float H = G * sin(b);
		float newLdir = H / sin(aimedFOV) /2.0f;

		//if (newLdir < 0 || H < 0 || G < 0)
		//{
		//	cout << "The camera goes the other way arround : " << "aimedFOV" << aimedFOV <<" newLdir : " << newLdir << " H : " << H << " G : " << G << endl;
		//}
		//else
		//	cout << "Ìt says its fine but : " << "Offcenter : " << JaySpace::Magnitude(camerapos  -target) <<" b : " <<b<< " newLdir : " << newLdir << " H : " << H << " G : " << G << endl;


		target2camdir = glm::normalize(target2camdir);

		camerapos = newTarget + target2camdir * newLdir;
		target = newTarget;
		m_Scale = JaySpace::g_Scale = 1.0f;
	}
}
void ProjectTeethJay::RegulateInputs(){
	JaySpace::button_left_just_released = false;
	JaySpace::button_right_just_released = false;
	JaySpace::button_middle_just_released = false;
	JaySpace::button_left_just_clicked = false;
	JaySpace::button_right_just_clicked = false;
	JaySpace::button_middle_just_clicked = false;
	JaySpace::g_diffScale = 0.0f;
	JaySpace::dragNdrop_count = 0;
}

void ProjectTeethJay::ChangeTypeNavTo(TypeNavigation newTypeNav)
{
	switch (mTypeNav) {
	case TN_selecting:
		break;
	case TN_editing:
		break;
	case TN_painting:
		break;
	case TN_playmode:
		// Hide the mouse and enable unlimited mouvement
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		// Set the mouse at the center of the screen
		glfwPollEvents();
		////glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		//glfwSetScrollCallback(window, ScrollCallback);
		break;
	case TN_automatic:
		break;
	case TN_basic:
	default:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	}
}



glm::vec2 ProjectTeethJay::SetNewScreenPos(glm::vec2 newCoord)
{
	mdiffCoord = mScreenCoord - newCoord;
	mScreenCoord = newCoord;

	return  mdiffCoord;

}


unordered_map<string, ShaderJay>::iterator ProjectTeethJay::CreateNewShader(string newName, const char* pathVertex, const char* pathFragment)
{
	//	WARNING! This one does put a new item in the list, but it also aim the 2 shaderPtr onto the new shader created.
	itEnv->shaderList.insert(make_pair(newName, ShaderJay(newName, pathVertex, pathFragment)));

	itEnv->itShad = itEnv->shaderList.find(newName); 
	ptrShad = &itEnv->itShad->second;

	return itEnv->itShad;
}



GLint ProjectTeethJay::NewUniformTexture(string shaderToAssignUniform, const char* varShaderName, GLint texture2Use)
{
	itEnv->itShad = itEnv->shaderList.find(shaderToAssignUniform);
	return itEnv->itShad->second.NewUniformTexture(varShaderName, texture2Use);
}

unordered_map<string, ShaderJay>::iterator ProjectTeethJay::AddThisPrePassToThisShader(
	const char* shaderToPrePass,
	const char* shaderName, 
	const char* vertexShader, 
	const char* fragmentShader) {
	unordered_map<string, ShaderJay>::iterator itShad2Pass = CreateNewShader(shaderToPrePass, vertexShader, fragmentShader);
	unordered_map<string, ShaderJay>::iterator itshader = itEnv->shaderList.find(shaderName);
	itshader->second.AddPrePass(itShad2Pass);

	return itShad2Pass;
}

GLint ProjectTeethJay::OutputShaderToNewTexture(const char* shaderName) {
	unordered_map<string, ShaderJay>::iterator itshader = itEnv->shaderList.find(shaderName);
	return itshader->second.OutputShaderToNewTexture(windowWidth, windowHeight);
}

void ProjectTeethJay::EmptySelector()
{
	if (SelectingFrameBuffer == 0) return;

	glDeleteFramebuffers(1, &SelectingFrameBuffer);
	glDeleteTextures(1, &colorBuffer);
	glDeleteRenderbuffers(1, &depthBuffer);
}

void ProjectTeethJay::FreeAllShaders()
{
	for(itEnv->itShad = itEnv->shaderList.begin(); itEnv->shaderList.size() > 0 && itEnv->itShad != itEnv->shaderList.end(); itEnv->itShad++)
	{
		itEnv->itShad->second.FreeShader();
	}
}

bool ProjectTeethJay::SearchForItemWithID_(int selectedId) {

	return itEnv->SearchForItemWithID_(selectedId);
}

bool ProjectTeethJay::SearchForItemWithID_ForMosueOver(int selectedId) {

	return itEnv->SearchForItemWithID_ForMouseOver(selectedId);
}

void ProjectTeethJay::EmptySelection()
{
	itEnv->EmptySelection();
}

void ProjectTeethJay::EmptyMouseOverSelection()
{
	itEnv->EmptyMouseOverSelection();
}

// Function to simplify vertices and generate indices
SimplifiedMesh ProjectTeethJay::simplifyVertices(const std::vector<glm::vec3>& inputVertices, float epsilon) {
	SimplifiedMesh result;

	// Map to store unique vertices and their indices
	std::unordered_map<glm::vec3, unsigned int, Vec3Hash, Vec3Equal> vertexMap(0, Vec3Hash(), Vec3Equal(0.00001));

	// Process each input vertex
	for (const auto& vertex : inputVertices) {
		// Check if vertex exists within epsilon distance
		auto it = vertexMap.find(vertex);
		if (it == vertexMap.end()) {
			// New vertex: add to result and map
			unsigned int index = static_cast<unsigned int>(result.vertices.size());
			result.vertices.push_back(vertex);
			vertexMap[vertex] = index;
			result.indices.push_back(index);
		}
		else {
			// Existing vertex: use its index
			result.indices.push_back(it->second);
		}
	}

	return result;
}