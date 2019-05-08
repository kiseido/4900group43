#include "ResourceImporter.h"
#include <fstream>
#include <sstream>


using namespace std;

int ResourceImporter::MeshImporter::ImportObj(const char *filePath, int& numVert, std::vector<float>& vert, std::vector<float>& tex, std::vector<float>& norm) {
    std::vector<float> vertVals;
    //std::vector<float> triangleVerts;
    //std::vector<float> textureCoords;
    std::vector<float> stVals;
    //std::vector<float> normals;
    std::vector<float> normVals;
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

                vert.push_back(vertVals[vertRef]);
                vert.push_back(vertVals[vertRef + 1]);
                vert.push_back(vertVals[vertRef + 2]);

                tex.push_back(stVals[tcRef]);
                tex.push_back(stVals[tcRef + 1]);

                norm.push_back(normVals[normRef]);
                norm.push_back(normVals[normRef + 1]);
                norm.push_back(normVals[normRef + 2]);
            }
        }
    }

    numVert = vert.size() / 3;

    return 0;
}

int ResourceImporter::TextureImporter::ImportTexture(const char *texImagePath, GLuint& tex)
{
    GLuint textureRef;
    textureRef = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureRef == 0) return -1;
    // ----- mipmap/anisotropic section
    glBindTexture(GL_TEXTURE_2D, textureRef);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat anisoset = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
    }
    // ----- end of mipmap/anisotropic section
    tex = textureRef;
    return 0;
}