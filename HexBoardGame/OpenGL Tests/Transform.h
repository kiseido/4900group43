#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective


class Transform
{
public:
    Transform();
    ~Transform();

    bool change = true;

    Transform *parent = 0;

    glm::mat4 tNet;
    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(1.0);
    glm::vec3 rotation = glm::vec3(0.0);

private:
};

namespace Transformer {
    void CalcTNet(Transform transf);

    glm::mat4 *GetTransform(Transform transf);

    void SetPosition(Transform transf, glm::vec3 pos);
    void SetPosition(Transform transf, float x, float y, float z);
    void Translate(Transform transf, glm::vec3 pos);
    void Translate(Transform transf, float x, float y, float z);
    void Scale(Transform transf, glm::vec3 scl);
    void Scale(Transform transf, float x, float y, float z);
    void SetScale(Transform transf, glm::vec3 scl);
    void SetScale(Transform transf, float x, float y, float z);
    void Rotate(Transform transf, glm::vec3 rot);
    void Rotate(Transform transf, float x, float y, float z);
    void SetRotation(Transform transf, glm::vec3 rot);
    void SetRotation(Transform transf, float x, float y, float z);
    void Reset(Transform transf);
};