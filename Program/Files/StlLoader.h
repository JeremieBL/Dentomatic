#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <sstream>
#include <array>
#include <cstdint>


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

namespace StlLoader {

    // Structure to hold vertex data (position only for simplicity)
    struct Vertex {
        float x, y, z;
    };
    bool LoadBinarySTL(const std::string& filename,
        std::vector<glm::vec3>& outVertices,
        std::vector<std::array<uint32_t, 3>>& outTriangles);

    // Function to load an STL file and extract vertices and indices for OpenGL
    bool loadSTL(const std::string& filename, std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices);

    //
    //// Example usage to set up OpenGL buffers (call this after loading your shaders)
    //void setupOpenGLBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, GLuint& vbo, GLuint& ibo, GLuint& vao) {
    //    // Generate and bind VAO
    //    glGenVertexArrays(1, &vao);
    //    glBindVertexArray(vao);
    //
    //    // Generate and bind VBO
    //    glGenBuffers(1, &vbo);
    //    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    //
    //    // Set vertex attribute pointers (assuming position is at location 0 in your shader)
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //    glEnableVertexAttribArray(0);
    //
    //    // Generate and bind IBO
    //    glGenBuffers(1, &ibo);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    //
    //    // Unbind VAO
    //    glBindVertexArray(0);
    //}
}