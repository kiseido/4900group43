#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Transform.h"

typedef GLuint Texture;


enum ModelID {
    GrassTileModel, WaterTileModel, ForestTileModel, RockTileModel, MountainTileModel, DesertTileModel, // Tiles
    Piece1Model, Piece2Model, Piece3Model, Piece4Model, Piece5Model, // Pieces
    BCITSquareModel, BCITBModel, BCITCModel, BCITIModel, BCITTModel, DigiProModel,
    MODEL_LIST_SIZE
};

enum TextureID {
    GrassTexture, WaterTexture, ForestTexture, RockTexture, MountainTexture, DesertTexture, // Tiles
    Piece1Texture, Piece2Texture, Piece3Texture, Piece4Texture, Piece5Texture, // Pieces
    BCITSquareTexture, BCITLetterTexture, DigiProTexture,
    TEXTURE_LIST_SIZE
};

enum MeshID {
    HexagonTileMesh, // Tiles
    Piece1Mesh, Piece2Mesh, Piece3Mesh, Piece4Mesh, Piece5Mesh, // Pieces
    BCITSquareMesh, BCITBMesh, BCITCMesh, BCITIMesh, BCITTMesh, DigiProMesh,
    MESH_LIST_SIZE
};

enum MaterialID {
    BasicMaterial,
    MATERIAL_LIST_SIZE
};

struct Mesh {
    Mesh() = default;
    int numVertices;
    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;
    //std::vector<glm::vec3> vertices;
    //std::vector<glm::vec2> texCoords;
    //std::vector<glm::vec3> normalVecs;
    ~Mesh() = default;
};


struct Material {
    Material();
    Material(glm::vec4 amb, glm::vec4 diff, glm::vec4 spec, float shin);
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
};



struct Model{
    Model() = default;
    Model(MeshID m, TextureID t, MaterialID mat = BasicMaterial);
    Mesh* mesh = nullptr;
    Material* material = nullptr;
    Texture texture = 0;
    uint8_t outlineWeight = 0;
    glm::vec3 outlineColor = { 0,0,0 };
    float overlayAlpha = 0;
    glm::vec3 overlayColor = { 0,0,0 };
    ~Model() = default;
};


namespace Resources {
    Model GetModel(ModelID modelId);
    Mesh* GetMesh(MeshID meshId);
    Mesh* LoadMesh(const char* filePath);
    Texture GetTexture(TextureID textureId);
    Texture LoadTexture(const char* filePath);
    Material* GetMaterial(MaterialID materialId);
    Mesh* MeshList[];
    Texture TextureList[];
    Model* ModelList[];
    Material* MaterialList[];
};