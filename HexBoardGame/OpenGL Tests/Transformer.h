#pragma once
#include "Transform.h"

namespace Transformer {
    void CalcTNet(Transform* transf);

    glm::mat4 *GetTransform(Transform* transf);

    void SetPosition(Transform* transf, glm::vec3 pos);
    void SetPosition(Transform* transf, float x, float y, float z);
    void Translate(Transform* transf, glm::vec3 pos);
    void Translate(Transform* transf, float x, float y, float z);
    void Scale(Transform* transf, glm::vec3 scl);
    void Scale(Transform* transf, float x, float y, float z);
    void SetScale(Transform* transf, glm::vec3 scl);
    void SetScale(Transform* transf, float x, float y, float z);
    void Rotate(Transform* transf, glm::vec3 rot);
    void Rotate(Transform* transf, float x, float y, float z);
    void SetRotation(Transform* transf, glm::vec3 rot);
    void SetRotation(Transform* transf, float x, float y, float z);
    void Reset(Transform* transf);
};
