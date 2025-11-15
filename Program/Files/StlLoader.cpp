#include "StlLoader.h"


using namespace std;



bool StlLoader::LoadBinarySTL(const std::string& filename,
    std::vector<glm::vec3>& outVertices,
    std::vector<std::array<uint32_t, 3>>& outTriangles) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    // 80-byte header
    char header[80];
    file.read(header, 80);

    // Number of triangles
    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), 4);

    outVertices.clear();
    outTriangles.clear();

    for (uint32_t i = 0; i < numTriangles; ++i) {
        // Normal vector (ignored here)
        glm::vec3 normal;
        file.read(reinterpret_cast<char*>(&normal), 12);

        std::array<uint32_t, 3> tri;
        for (int v = 0; v < 3; ++v) {
            glm::vec3 vertex;
            file.read(reinterpret_cast<char*>(&vertex), 12);
            outVertices.push_back(vertex);
            tri[v] = static_cast<uint32_t>(outVertices.size() - 1);
        }
        outTriangles.push_back(tri);

        // Attribute byte count (ignored)
        uint16_t attrCount;
        file.read(reinterpret_cast<char*>(&attrCount), 2);
    }

    return true;
}

// Function to load an STL file and extract vertices and indices for OpenGL
bool StlLoader::loadSTL(const std::string& filename, std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open STL file: " << filename << std::endl;
        return false;
    }

    // Read header
    char header[80];
    file.read(header, 80);
    std::string headerStr(header, 80);
    file.seekg(0, std::ios::beg);

    // Check for ASCII STL
    if (headerStr.find("solid") != std::string::npos && headerStr.find("facet") != std::string::npos) {
        // ASCII STL
        std::string line;
        vertices.clear();
        indices.clear();
        while (std::getline(file, line)) {
            if (line.find("facet normal") != std::string::npos) {
                std::istringstream iss(line);
                std::string token;
                float nx, ny, nz;
                iss >> token >> token >> nx >> ny >> nz;
                // Skip "outer loop"
                std::getline(file, line);
                for (int i = 0; i < 3; ++i) {
                    std::getline(file, line);
                    if (line.find("vertex") != std::string::npos) {
                        std::istringstream viss(line);
                        std::string vtoken;
                        float x, y, z;
                        viss >> vtoken >> x >> y >> z;
                        glm::vec3 v;
                        glm::vec3 n;
                        v.x = x; v.y = y; v.z = z;
                        n.x = nx; n.y = ny; n.z = nz;
                        vertices.push_back(v);
                        indices.push_back(static_cast<uint32_t>(vertices.size() - 1));
                    }
                }
                // Skip "endloop" and "endfacet"
                std::getline(file, line);
                std::getline(file, line);
            }
        }
        file.close();
    }
    else {
        // Binary STL
        file.seekg(80);
        uint32_t numTriangles = 0;
        file.read(reinterpret_cast<char*>(&numTriangles), sizeof(uint32_t));
        vertices.clear();
        indices.clear();
        for (uint32_t i = 0; i < numTriangles; ++i) {
            float nx, ny, nz;
            file.read(reinterpret_cast<char*>(&nx), sizeof(float));
            file.read(reinterpret_cast<char*>(&ny), sizeof(float));
            file.read(reinterpret_cast<char*>(&nz), sizeof(float));
            for (int j = 0; j < 3; ++j) {
                float x, y, z;
                file.read(reinterpret_cast<char*>(&x), sizeof(float));
                file.read(reinterpret_cast<char*>(&y), sizeof(float));
                file.read(reinterpret_cast<char*>(&z), sizeof(float));
                glm::vec3 v;
                glm::vec3 n;
                v.x = x; v.y = y; v.z = z;
                n.x = nx; n.y = ny; n.z = nz;
                vertices.push_back(v);
                indices.push_back(static_cast<uint32_t>(vertices.size() - 1));
            }
            // Skip attribute byte count
            file.seekg(2, std::ios::cur);
        }
        file.close();
    }
    return true;
}


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