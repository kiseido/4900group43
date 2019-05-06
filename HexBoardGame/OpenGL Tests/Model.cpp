#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "Model.h"
using namespace std;

Model ImportedMeshes::**Models[Meshes::MESH_LIST_SIZE];

Mesh::Mesh() {}

Mesh::Mesh(const char *filePath) {
    MeshImporter meshImporter = MeshImporter();
    meshImporter.parseOBJ(filePath);
    numVertices = meshImporter.getNumVertices();
    std::vector<float> verts = meshImporter.getVertices();
    std::vector<float> tcs = meshImporter.getTextureCoordinates();
    std::vector<float> normals = meshImporter.getNormals();

    for (int i = 0; i < numVertices; i++) {
        vertices.push_back(glm::vec3(verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2]));
        texCoords.push_back(glm::vec2(tcs[i * 2], tcs[i * 2 + 1]));
        normalVecs.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
    }
}

int Mesh::getNumVertices() { return numVertices; }
std::vector<glm::vec3> Mesh::getVertices() { return vertices; }
std::vector<glm::vec2> Mesh::getTextureCoords() { return texCoords; }
std::vector<glm::vec3> Mesh::getNormals() { return normalVecs; }

// ---------------------------------------------------------------

MeshImporter::MeshImporter() {}


void MeshImporter::parseOBJ(const char *filePath) {
    float x, y, z;
    string content;
    ifstream fileStream(filePath, ios::in);
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        if (line.compare(0, 2, "v ") == 0) {
            stringstream ss(line.erase(0, 1));
            ss >> x; ss >> y; ss >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        if (line.compare(0, 2, "vt") == 0) {
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }
        if (line.compare(0, 2, "vn") == 0) {
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y; ss >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        if (line.compare(0, 2, "f ") == 0) {
            string oneCorner, v, t, n;
            stringstream ss(line.erase(0, 2));
            for (int i = 0; i < 3; i++) {
                getline(ss, oneCorner, ' ');
                stringstream oneCornerSS(oneCorner);
                getline(oneCornerSS, v, '/');
                getline(oneCornerSS, t, '/');
                getline(oneCornerSS, n, '/');

                int vertRef = (stoi(v) - 1) * 3;
                int tcRef = (stoi(t) - 1) * 2;
                int normRef = (stoi(n) - 1) * 3;

                triangleVerts.push_back(vertVals[vertRef]);
                triangleVerts.push_back(vertVals[vertRef + 1]);
                triangleVerts.push_back(vertVals[vertRef + 2]);

                textureCoords.push_back(stVals[tcRef]);
                textureCoords.push_back(stVals[tcRef + 1]);

                normals.push_back(normVals[normRef]);
                normals.push_back(normVals[normRef + 1]);
                normals.push_back(normVals[normRef + 2]);
            }
        }
    }
}
int MeshImporter::getNumVertices() { return (triangleVerts.size() / 3); }
std::vector<float> MeshImporter::getVertices() { return triangleVerts; }
std::vector<float> MeshImporter::getTextureCoordinates() { return textureCoords; }
std::vector<float> MeshImporter::getNormals() { return normals; }