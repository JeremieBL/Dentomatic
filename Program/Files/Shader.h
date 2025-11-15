//#ifndef SHADER_h
//#define SHADER_H
#pragma once


#include <iostream>
using namespace std;
#include <fstream>

#include <vector>
#include <unordered_map>
#include "emlist.h"
#include <gl/glew.h>
#include <common/shader.hpp>
#include <common/texture.hpp>
//#include "JayObjet.h"
enum class TypeObjetVar;
class JayObjet;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <common/controls.hpp>
//#include <common/objloader.hppTextureJay
//#include <common/vboindexer.hpp>


enum class UniformType {
    neutral = 0,
    typeint = 1,
    typefloat = 2,
    typeMatrix4x4 = 3,
    typeTexture = 4,
    color3 = 5,
    color4 = 6,
    light3 = 7,
    glmvec2 = 8,
    glmvec3 = 9,
    matricefloat4x4 = 10,
	typeObjetVar = 11 // For JayObjet
};


enum class TypeMatrixDeclared {
    all = 0,
    MVPonly = 1,
    Projonly = 2,
    Viewonly = 3,
    Modelonly = 4
};

class TextureJay {
public:
    GLuint idGLTexture;
    string shaderTextureName;
    string type;
    string path;

    TextureJay(const char* texturePath, const char* newshaderTextureName);
    TextureJay(const char* texturePath);

    TextureJay();

    TextureJay(unsigned int textureId, const string& newtextureName, const string& textureType, const string& texturePath)
        : idGLTexture(textureId), shaderTextureName(newtextureName), type(textureType), path(texturePath) {
    };
    ~TextureJay();

    void FreeTexture();
};

class Uniform {
public:
    string name;
    void* var;
    UniformType type;
    GLint id;
    GLint idTex;
    glm::vec4* var4;
    glm::vec3* var3;
    glm::vec2* var2;
    TypeObjetVar typeObjetVarDeclared;

    Uniform();
    Uniform(const char* newName, GLint newid, UniformType newType, GLint newidTex);
    Uniform(const char* newName, GLint newid, glm::vec4* newvar4, UniformType newType);
    Uniform(const char* newName, GLint newid, glm::vec3* newvar3, UniformType newType);
    Uniform(const char* newName, GLint newid, glm::vec2* newvar2, UniformType newType);
    Uniform(const char* newName, GLint newid, void* newvar, UniformType newType);
    Uniform(const char* newName, GLint newid, TypeObjetVar);
    ~Uniform();

    static emlist<Uniform>::iterator FindInto(emlist<Uniform> uniformList, string varName);
    void PassVariable(void* var = nullptr);
};




class ShaderJay {
public:
    ShaderJay();
    ShaderJay(string newname, const char* vsFile, const char* fsFile);
    ~ShaderJay();

    //	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    GLfloat* MVPMat_;
    GLfloat* ProjMat_;
    GLfloat* ViewMat_;
    GLfloat* ModMat_;
    GLfloat* ModMat_2Use;

    GLfloat* matTransfo;
    string shaderName;

    emlist<TextureJay> textureList;
    emlist<TextureJay>::iterator itTexture;
    emlist<Uniform> uniformList;
    emlist<Uniform>::iterator itUniform;

    emlist<unordered_map<string, ShaderJay>::iterator> shaderIDList; // List of shaders for materials
	emlist<unordered_map<string, ShaderJay>::iterator>::iterator itshaderID;

    //unordered_map<string, Uniform> uniformList;
    //unordered_map<string, Uniform>::iterator itUniform;

    unsigned int id();
    void UseProgram();
    void EndProgram();

    void FreeShader();
    void init(const char *vertexShaderFile, const char *fragmentShaderFile);
    GLuint* AddTexture(const char* imagepath, const char* shaderTextureName);
    GLuint* AddTexture(const char* imagepath);

    TypeMatrixDeclared typeMatrixDeclared = TypeMatrixDeclared::all;

    void getUniformLocationOfTransformMatrices(GLfloat* newMVPMat_);
    void getUniformLocationOfTransformMatrices(GLfloat* newMVPMat_, GLfloat* newProjMat_,GLfloat* newViewMat_, GLfloat* newModMat_);

    void PassMatrixes(void* var = nullptr);
	void PassVariables(void* var = nullptr);
    GLint NewUniformUsingObjectVar(const char*, TypeObjetVar);

    //void PassVariable(string,void*);
    //void PassVariable(string, float);
    //void PassVariable(string, const int*);
    //void PassVariable(string, const float*);

    GLint NewUniform(const char* newuniformName, glm::vec4* newVar4, UniformType type);
    GLint NewUniform(const char* newuniformName, glm::vec3* newVar3, UniformType type);
    GLint NewUniform(const char* newuniformName, glm::vec2* newVar2, UniformType type);
    GLint NewUniform(const char* newuniformName, void* val, UniformType type);
    GLint NewUniformTexture(const char* newuniformName, GLint newidTex);
 //   void NewUniform(const char* uniformName, UniformType type);

    bool isMultiPass = false;
    unordered_map<string, ShaderJay>::iterator AddPrePass(unordered_map<string, ShaderJay>::iterator);
    emlist<string> prePassShaderList;
    GLint OutputShaderToNewTexture(int screenWidth, int screenHeight);
    GLint OutputShaderToNewTexture_ForCalculations(int screenWidth, int screenHeight);
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    GLuint renderedTexture;
    GLuint FrameBufferName = 0;
    GLuint depthrenderbuffer = 0;
    GLuint quad_vertexbuffer = 0;
    vector<glm::vec3> g_quad_vertex_buffer_data;
    void UsePrePass();
    void RestaureAfterPrePass();
    
    void FreeAllTextures();

    GLuint MVPID;
    GLuint ProjMatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;


private:
    std::string readShader( const char *fileName);
    void validateShader(GLuint shader, const char* file);
    void validateProgram(GLuint program);

    unsigned int programId;
    unsigned int vertexId;
    unsigned int fragmentId;
   // GLint textureid;
    bool isInitialized = false;
};
//
//#endif

