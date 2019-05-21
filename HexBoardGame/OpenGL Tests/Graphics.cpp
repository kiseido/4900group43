#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "Graphics.h"
#include "ResourceImporter.h"

using namespace std;


Mesh* Resources::MeshList[MESH_LIST_SIZE];
Texture Resources::TextureList[TEXTURE_LIST_SIZE];
Model* Resources::ModelList[MODEL_LIST_SIZE];
Material* Resources::MaterialList[MATERIAL_LIST_SIZE];



Model::Model(MeshID m, TextureID t, MaterialID mat) {
    mesh = Resources::GetMesh(m);
    texture = Resources::GetTexture(t);
    material = Resources::GetMaterial(mat);
}

Material::Material() {
    ambient = glm::vec4(0.7f);
    diffuse = glm::vec4(0.5f);
    specular = glm::vec4(0.25f);
    shininess = 0.5;
}

Material::Material(glm::vec4 amb, glm::vec4 diff, glm::vec4 spec, float shin) : ambient(amb), diffuse(diff), specular(spec), shininess(shin) {
    
}

Mesh* Resources::GetMesh(MeshID meshId) {
    if (Resources::MeshList[meshId] == nullptr || Resources::MeshList[meshId] == 0) {
        switch (meshId) {
        case HexagonTileMesh:
            Resources::MeshList[meshId] = LoadMesh("hexagon.obj");
            break;
        case Piece1Mesh:
            Resources::MeshList[meshId] = LoadMesh("piece1.obj");
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
            Resources::TextureList[textureId] = LoadTexture("grass.jpg");
            break;
        case WaterTexture:
            Resources::TextureList[textureId] = LoadTexture("water.jpg");
            break;
        case DesertTexture:
            Resources::TextureList[textureId] = LoadTexture("desert.jpg");
            break;
        case RockTexture:
            Resources::TextureList[textureId] = LoadTexture("rock.jpg");
            break;
        case Piece1Texture:
            Resources::TextureList[textureId] = LoadTexture("wood.jpg");
            break;
        default:
            Resources::TextureList[textureId] = 0;
        }
    }
    return Resources::TextureList[textureId];
}

Texture Resources::LoadTexture(const char* filePath) {
    Texture t;
    ResourceImporter::TextureImporter::ImportTexture(filePath, t);
    return t;
}

Model Resources::GetModel(ModelID modelId) {
    switch (modelId) {
    case GrassTileModel:
        return Model(HexagonTileMesh, GrassTexture);
        break;
    case WaterTileModel:
        return Model(HexagonTileMesh, WaterTexture);
        break;
    case DesertTileModel:
        return Model(HexagonTileMesh, DesertTexture);
        break;
    case RockTileModel:
        return Model(HexagonTileMesh, RockTexture);
        break;
    case Piece1Model:
        return Model(Piece1Mesh, Piece1Texture);
        break;
    default:
        return Model();
    }
}

Material* Resources::GetMaterial(MaterialID materialId) {
    if (Resources::ModelList[materialId] == nullptr || Resources::ModelList[materialId] == 0) {
        switch (materialId) {
        case BasicMaterial:
            Resources::MaterialList[materialId] = new Material(glm::vec4(0.7f), glm::vec4(0.5f), glm::vec4(0.25f), 0.5f);
            break;
        default:
            Resources::MaterialList[materialId] = nullptr;
        }
    }
    return Resources::MaterialList[materialId];
}