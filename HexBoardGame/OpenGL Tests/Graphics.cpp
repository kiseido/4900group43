#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "Graphics.h"
#include "ResourceImporter.h"

using namespace std;


Mesh* Resources::MeshList[MESH_LIST_SIZE];
Texture Resources::TextureList[TEXTURE_LIST_SIZE];
Model* Resources::ModelList[MODEL_LIST_SIZE];


Mesh::Mesh() {}


Model::Model(MeshID m, TextureID t) {
    mesh = Resources::GetMesh(m);
    texture = Resources::GetTexture(t);
}

Mesh* Resources::GetMesh(MeshID meshId) {
    if (Resources::MeshList[meshId] == nullptr || Resources::MeshList[meshId] == 0) {
        switch (meshId) {
        case HexagonTileMesh:
            Resources::MeshList[meshId] = LoadMesh("hexagon.obj");
            break;
        default:
            Resources::MeshList[meshId] = nullptr;
        }
    }
    return Resources::MeshList[meshId];
}

Mesh* Resources::LoadMesh(const char* filePath) {
    Mesh* m = new Mesh();
    ResourceImporter::MeshImporter::ImportObj(filePath, m->numVertices, m->pvalues, m->tvalues, m->nvalues);
    return m;
}

Texture Resources::GetTexture(TextureID textureId) {
    if (Resources::TextureList[textureId] == 0) {
        switch (textureId) {
        case GrassTexture:
            break;
        default:
            Resources::MeshList[textureId] = 0;
        }
    }
    return Resources::TextureList[textureId];
}

Model* Resources::GetModel(ModelID modelId) {
    if (Resources::ModelList[modelId] == nullptr || Resources::ModelList[modelId] == 0) {
        switch (modelId) {
        case GrassTileModel:
            Resources::ModelList[modelId] = new Model(HexagonTileMesh, GrassTexture);
            break;
        default:
            Resources::ModelList[modelId] = nullptr;
        }
    }
    return Resources::ModelList[modelId];
}