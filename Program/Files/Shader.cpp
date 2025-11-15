
#include "Shader.h"
#include "JayObjet.h"


// Default constructor
ShaderJay::ShaderJay()
{
    shaderName = "ShaderName";
	programId = 0;
	vertexId = 0;
	fragmentId = 0;
	isInitialized = false;
	// Initialize the shader with default files
	//  init("default_vertex_shader.glsl", "default_fragment_shader.glsl");
}

// Destructor
ShaderJay::~ShaderJay()
{
    FreeAllTextures();
}

// Constructor
ShaderJay::ShaderJay(string newname, const char *vsFile, const char *fsFile)
{
    shaderName = newname;

    programId = LoadShaders(vsFile, fsFile);
    
    //    This was the use I did.
    //init(vsFile, fsFile); // Initialize the shader
}

// Return the id of the shader program
unsigned int ShaderJay::id()
{
    return programId;
}

// Bind the shader
void ShaderJay::UseProgram()
{
    glUseProgram(programId);
}

// Unbind the shader
void ShaderJay::EndProgram()
{
    glUseProgram(0);
}

// Detach the shader
void ShaderJay::FreeShader()
{
    glDetachShader(programId, vertexId);
    glDetachShader(programId, fragmentId);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    glDeleteProgram(programId);
}

// Initialize the shader
void ShaderJay::init(const char *vsFile, const char *fsFile)
{
    if (isInitialized)
    {
        return;
    }

    isInitialized = true;

    // Create the shaders
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the shaders
    string vsText = readShader(vsFile);
    string fsText = readShader(fsFile);

    const char *vertexText = vsText.c_str();
    const char *fragmentText = fsText.c_str();

    if (vertexText == NULL)
    {
        cout << "Vertex shader file not found." << endl;
        return;
    }

    if (fragmentText == NULL)
    {
        cout << "Fragment shader file not found." << endl;
        return;
    }

    glShaderSource(vertexId, 1, &vertexText, 0);
    glCompileShader(vertexId);
    validateShader(vertexId, vsFile);

    glShaderSource(fragmentId, 1, &fragmentText, 0);
    glCompileShader(fragmentId);
    validateShader(fragmentId, fsFile);

    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);

    glBindAttribLocation(programId, 0, "in_Position");
    glBindAttribLocation(programId, 1, "in_Normal");
	glBindAttribLocation(programId, 2, "in_Color");
    glBindAttribLocation(programId, 3, "in_TexCoord");

    glLinkProgram(programId);
    validateProgram(programId);
}

// Read our shader from a text file
string ShaderJay::readShader(const char *fileName)
{
    string line = string();
    string shaderFile = string();

    ifstream file(fileName);
    if ( file.is_open() )
    {
        while ( !file.eof() )
        {
            getline(file, line);
            shaderFile.append(line);
            shaderFile.append("\n");
        }

        file.close();
    }

    return shaderFile;
}

GLuint* ShaderJay::AddTexture(const char* imagepath)
{
    textureList.push_back(TextureJay(imagepath));
  //  textureList.last()->idShaderTexture = glGetUniformLocation(programId, shaderTextureName);

    return &(textureList.last()->idGLTexture);
}

GLuint* ShaderJay::AddTexture(const char* imagepath, const char* shaderTextureName)
{
    textureList.push_back(TextureJay(imagepath, shaderTextureName));
    //NewUniformTexture(shaderTextureName, textureList.last()->idGLTexture);
//      newuniformName, GLint newidTex;

  //  GLint temptextureID = ;
    uniformList.push_back(
        Uniform(shaderTextureName,
            glGetUniformLocation(programId, shaderTextureName),
            UniformType::typeTexture,
            textureList.last()->idGLTexture)
    );


    return &(textureList.last()->idGLTexture);
}
void ShaderJay::getUniformLocationOfTransformMatrices(GLfloat* newMVPMat_)
{
    MVPMat_ = newMVPMat_;
    MVPID = glGetUniformLocation(programId, "MVP");

    typeMatrixDeclared = TypeMatrixDeclared::MVPonly;
}
void ShaderJay::getUniformLocationOfTransformMatrices(GLfloat* newMVPMat_, GLfloat* newProjMat_, GLfloat* newViewMat_, GLfloat* newModMat_)
{
    MVPMat_ = newMVPMat_;
    ProjMat_ = newProjMat_;
    ViewMat_ = newViewMat_;
    ModMat_ = newModMat_;

    MVPID = glGetUniformLocation(programId, "MVP");
    ProjMatrixID = glGetUniformLocation(programId, "P");
    ViewMatrixID = glGetUniformLocation(programId, "V");
    ModelMatrixID = glGetUniformLocation(programId, "M");

    typeMatrixDeclared = TypeMatrixDeclared::all;
}

void ShaderJay::PassMatrixes(void* var)
{

    switch (typeMatrixDeclared) {
    case TypeMatrixDeclared::all:
        //glUniformMatrix4fv(MVPID, 1, GL_FALSE, MVP_);

        if (var != nullptr)
        {
            matTransfo = static_cast<float*>(var);

        }
        else
            ModMat_2Use = ModMat_;

        glUniformMatrix4fv(MVPID, 1, GL_FALSE, MVPMat_);
        glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, ProjMat_);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, ViewMat_);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, ModMat_2Use);
        break;
    case TypeMatrixDeclared::MVPonly:
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, MVPMat_);
        break;
    case TypeMatrixDeclared::Projonly:
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, ProjMat_);
        break;
    case TypeMatrixDeclared::Modelonly:
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, ModMat_2Use);
        break;
    case TypeMatrixDeclared::Viewonly:
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, ViewMat_);
        break;
    default:
        break;
    }
}

void ShaderJay::PassVariables(void* var)
{
    for (itUniform = uniformList.begin(); itUniform != uniformList.before_begin() && itUniform != uniformList.end(); itUniform++)
    {
        itUniform->PassVariable(var);
    }
}

GLint ShaderJay::NewUniformUsingObjectVar(const char* newuniformName, TypeObjetVar typeVar2use) {
    uniformList.push_back(Uniform("newuniformName", glGetUniformLocation(programId, newuniformName), typeVar2use));
	return uniformList.last()->id;
}

/*
//  Ici, j'ai comme l'impression quy faudra retranscrire les 40 fonction de openGL, on le fera pe une autre fois
void ShaderJay::PassVariable(string varName, void* val) {

    glUniform1i(Uniform::FindInto(uniformList, varName)->id, *(static_cast<int*>(val)));
}

void ShaderJay::PassVariable(string varName, float val) {

    glUniform1f(Uniform::FindInto(uniformList, varName)->id, val);
}
void ShaderJay::PassVariable(string varName, const int* val) {

    glUniform1iv(Uniform::FindInto(uniformList, varName)->id, 1.0, val);
}
void ShaderJay::PassVariable(string varName, const float* val) {

    glUniform1fv(Uniform::FindInto(uniformList, varName)->id, 1.0, val);
}*/



// Validate if the shaders compiled correctly
void ShaderJay::validateShader(GLuint shader, const char* file = 0)
{
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if (length > 0)
    {
        cout << "Shader " << shader << " (" << (file != 0 ? file : "") << ") compilation error: " << buffer << endl;
    }
}

// Validate if the program linked correctly to the shaders
void ShaderJay::validateProgram(GLuint program)
{
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
    if (length > 0)
        cout << "Program " << program << " linking error: " << buffer << endl;

    glValidateProgram(program);
    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE)
        cout << "Error validating program " << program << endl;
}


GLint ShaderJay::NewUniform(const char* newuniformName, glm::vec4* newVar4, UniformType type)
{
    uniformList.push_back(Uniform(newuniformName, glGetUniformLocation(programId, newuniformName), newVar4, type));
    return (uniformList.last()->id);
}

GLint ShaderJay::NewUniform(const char* newuniformName, glm::vec3* newVar3, UniformType type)
{
    uniformList.push_back(Uniform(newuniformName, glGetUniformLocation(programId, newuniformName), newVar3, type));
    return (uniformList.last()->id);
}

GLint ShaderJay::NewUniform(const char* newuniformName, glm::vec2* newVar2, UniformType type)
{
    uniformList.push_back(Uniform(newuniformName, glGetUniformLocation(programId, newuniformName), newVar2, type));
    return (uniformList.last()->id);
}

GLint ShaderJay::NewUniform(const char* newuniformName, void* val, UniformType type)
{
    uniformList.push_back(Uniform(newuniformName, glGetUniformLocation(programId, newuniformName), val, type));
    return (uniformList.last()->id);
}

GLint ShaderJay::NewUniformTexture(const char* newuniformName, GLint newidTex)
{
    uniformList.push_back(Uniform(newuniformName, glGetUniformLocation(programId, newuniformName), UniformType::typeTexture, newidTex));
    return uniformList.last()->id;
}

GLint ShaderJay::OutputShaderToNewTexture(int screenWidth, int screenHeight) {
    // Set up back depth texture and FBO.
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, screenWidth, screenHeight, 0, GL_RED, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &FrameBufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferName);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Back depth FBO incomplete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return 0;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return renderedTexture;
}


GLint ShaderJay::OutputShaderToNewTexture_ForCalculations(int screenWidth, int screenHeight) {

    // ---------------------------------------------
    // Render to Texture - specific code begins here
    // -------------------------------


    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    glGenFramebuffers(1, &FrameBufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferName);

    // The texture we're going to render to
    glGenTextures(1, &renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" means "empty" )
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
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


    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    // The building of a screen we can project on
    g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
    g_quad_vertex_buffer_data.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
    g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    g_quad_vertex_buffer_data.push_back(glm::vec3(1.0f, 1.0f, 0.0f));


    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data) * sizeof(glm::vec3), &g_quad_vertex_buffer_data[0], GL_STATIC_DRAW);

    //  The quadprogram will be called "QuadProgram" and will be listed in the environnement shaderlist
    // 
	return renderedTexture;
}

unordered_map<string, ShaderJay>::iterator ShaderJay::AddPrePass(unordered_map<string, ShaderJay>::iterator itShaderJay)
{
	shaderIDList.push_back(itShaderJay);
	isMultiPass = true;

	return *shaderIDList.last();
}

void ShaderJay::UsePrePass()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferName);
    glClearColor(-1.0f, -1.0f, -1.0f, -1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_MAX);
    glBlendFunc(GL_ONE, GL_ONE);
    glCullFace(GL_FRONT);  // Render back faces.
}
void ShaderJay::RestaureAfterPrePass()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Back to screen.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // If needed.
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);  // Render front faces.

}
void ShaderJay::FreeAllTextures()
{
    for (itTexture = textureList.begin(); itTexture != textureList.before_begin() && itTexture != textureList.end(); itTexture++)
    {
        itTexture->FreeTexture();
    }
}


TextureJay::TextureJay() : idGLTexture(0), shaderTextureName(""), type(""), path("")
{
};

TextureJay::~TextureJay()
{
 //   FreeTexture();
};

TextureJay::TextureJay(const char* texturePath, const char* newshaderTextureName)
{
    path = texturePath;
    shaderTextureName = newshaderTextureName;
    idGLTexture = loadDDS(texturePath);
}

TextureJay::TextureJay(const char* texturePath)
{
    path = texturePath;
    idGLTexture = loadDDS(texturePath);
}
void TextureJay::FreeTexture()
{
	if (idGLTexture == 0) return;

    glDeleteTextures(1, &idGLTexture);
}

Uniform::Uniform() {}
Uniform::Uniform(const char* newName, GLint newid, UniformType newType, GLint newidTex) : name(newName), id(newid), type(newType), idTex(newidTex) {}
Uniform::Uniform(const char* newName, GLint newid, glm::vec4* newvar4, UniformType newType) : name(newName), id(newid), var4(newvar4), type(newType) {}
Uniform::Uniform(const char* newName, GLint newid, glm::vec3* newvar3, UniformType newType) : name(newName), id(newid), var3(newvar3), type(newType) {}
Uniform::Uniform(const char* newName, GLint newid, glm::vec2* newvar2, UniformType newType) : name(newName), id(newid), var2(newvar2), type(newType) {}
Uniform::Uniform(const char* newName, GLint newid, void* newvar, UniformType newType) : name(newName), id(newid), var(newvar), type(newType) {}

Uniform::Uniform(const char* newName, GLint newid, TypeObjetVar newTypeObjetVar)
    :name(newName), id(newid), typeObjetVarDeclared(newTypeObjetVar)
{
    type = UniformType::typeObjetVar;
}

Uniform::~Uniform() {}

emlist<Uniform>::iterator Uniform::FindInto(emlist<Uniform> uniformList, string varName) {
    emlist<Uniform>::iterator itUniform;
    for (itUniform = uniformList.begin(); itUniform != uniformList.before_begin() && itUniform != uniformList.end(); itUniform++)
    {
        if (itUniform->name == varName)
            return itUniform;
    }

	//  Doit l'avoir trouvé, sinon c'est qu'il y a un problème
    assert(false);
    return itUniform;
}

void Uniform::PassVariable(void* var)
{
    JayObjet* objPtr;

    switch (type)
    {
    case UniformType::neutral:
        break;
    case UniformType::typeint:
        glUniform1i(id, *(static_cast<int*>(var)));
        break;
    case UniformType::typefloat:
        glUniform1f(id, *(static_cast<float*>(var)));
        break;
    case UniformType::typeMatrix4x4:
        glUniform1iv(id, 1, static_cast<int*>(var));
        break;
    case UniformType::typeTexture:
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, idTex);       
        glUniform1i(id, 0);
        break;
    case UniformType::color3:
     //   glUniform3fv(id, 3, &(*static_cast<glm::vec3*>(var))[0]);
        glUniform3f(id, var3->x, var3->y, var3->z);
        break;
    case UniformType::color4:
        glUniform4fv(id, 4, &(*static_cast<glm::vec4*>(var))[0]);
        break;
    case UniformType::light3:
        //  glm::vec3 var3 = (*static_cast<glm::vec4*>(var))[0];
        glUniform3f(id, var3->x, var3->y, var3->z);
        //glUniform3fv(id, 3, &(*static_cast<glm::vec3*>(var))[0]);
        break;
     case UniformType::glmvec3:
       // glUniform3fv(id, 3, &(*static_cast<glm::vec3*>(var))[0]);
         glUniform3f(id, var3->x, var3->y, var3->z);
         break;
     case UniformType::glmvec2:
       // glUniform3fv(id, 3, &(*static_cast<glm::vec3*>(var))[0]);
         glUniform2f(id, var3->x, var3->y);
         break;
     case UniformType::matricefloat4x4:
         glUniformMatrix4fv(id, 1, GL_FALSE, static_cast<float*>(var));
         break;
     case UniformType::typeObjetVar:
         objPtr = static_cast<JayObjet*>(var);
		 assert(objPtr != nullptr);

         switch (typeObjetVarDeclared) {
		 case TypeObjetVar::neutral:
			 break; 
         case TypeObjetVar::typeCentre:
             glUniform3f(id, float(objPtr->center.x), objPtr->center.y, objPtr->center.z);
             break;
         case TypeObjetVar::typeCouleur:
             glUniform3f(id, objPtr->objColor.x, objPtr->objColor.y, objPtr->objColor.z);
             break;
         case TypeObjetVar::typeMatrixTransformation4x4:
             glUniformMatrix4fv(id, 1, GL_FALSE, &objPtr->transformMatrix[0][0]);
             break;
         default: 
             break;
         }
         break;
     default:
        break;
    }
}