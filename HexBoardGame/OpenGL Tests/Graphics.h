#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Transform.h"

typedef GLuint Texture;


enum ModelID {
    GrassTileModel, WaterTileModel, ForestTileModel, RockTileModel, MountainTileModel, DesertTileModel, // Tiles
    Piece1Model, Piece2Model, Piece3Model, Piece4Model, Piece5Model, // Pieces
    MODEL_LIST_SIZE
};

enum TextureID {
    GrassTexture, WaterTexture, ForestTexture, RockTexture, MountainTexture, DesertTexture, // Tiles
    Piece1Texture, Piece2Texture, Piece3Texture, Piece4Texture, Piece5Texture, // Pieces
    TEXTURE_LIST_SIZE
};

enum MeshID {
    HexagonTileMesh, // Tiles
    Piece1Mesh, Piece2Mesh, Piece3Mesh, Piece4Mesh, Piece5Mesh, // Pieces
    MESH_LIST_SIZE
};

class Mesh
{
public:
    Mesh();
    int numVertices;
    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;
    //std::vector<glm::vec3> vertices;
    //std::vector<glm::vec2> texCoords;
    //std::vector<glm::vec3> normalVecs;
    ~Mesh() = default;
};





class Model {
private: 
    Model();
public:
    Model(MeshID m, TextureID t);
    Mesh* mesh;
    Texture texture;
    ~Model() = default;
};


namespace Resources {
    Model* GetModel(ModelID modelId);
    Mesh* GetMesh(MeshID meshId);
    Mesh* LoadMesh(const char* filePath);
    Texture GetTexture(TextureID textureId);
    Mesh* MeshList[];
    Texture TextureList[];
    Model* ModelList[];
};