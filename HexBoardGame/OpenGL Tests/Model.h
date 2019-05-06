#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <glm\glm.hpp>
#include "Transform.h"


class Mesh
{
private:
    int numVertices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normalVecs;
public:
    Mesh();
    Mesh(const char *filePath);
    int getNumVertices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTextureCoords();
    std::vector<glm::vec3> getNormals();
};

class MeshImporter
{
private:
    std::vector<float> vertVals;
    std::vector<float> triangleVerts;
    std::vector<float> textureCoords;
    std::vector<float> stVals;
    std::vector<float> normals;
    std::vector<float> normVals;
public:
    MeshImporter();
    void parseOBJ(const char *filePath);
    int getNumVertices();
    std::vector<float> getVertices();
    std::vector<float> getTextureCoordinates();
    std::vector<float> getNormals();
};

class Model
{
    std::vector<Mesh*> meshes;
    std::vector<GLuint> textures;
};



enum Meshes {
    Hexagon,
    MESH_LIST_SIZE
};


class ImportedMeshes {
public:
    static Mesh** MeshList;
};