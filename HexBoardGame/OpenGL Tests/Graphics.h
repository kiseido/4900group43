#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Transform.h"
#include "Component.h"

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

class Mesh {
public:
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


class Material {
public:
    Material();
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
};



class Model : public Component {
public:
    Model(MeshID m, TextureID t);
    Mesh* mesh;
    Material material;
    Texture texture;
    ~Model() = default;
};


namespace Resources {
    Model* GetModel(ModelID modelId);
    Mesh* GetMesh(MeshID meshId);
    Mesh* LoadMesh(const char* filePath);
    Texture GetTexture(TextureID textureId);
    Texture LoadTexture(const char* filePath);
    Mesh* MeshList[];
    Texture TextureList[];
    Model* ModelList[];
};