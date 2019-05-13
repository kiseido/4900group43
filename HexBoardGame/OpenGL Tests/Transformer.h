#pragma once
#include "ECS.h"

namespace Transformer {
    void CalcTNet(EntityID eid);

    glm::mat4 *GetTransform(EntityID eid);

    void SetPosition(EntityID eid, glm::vec3 pos);
    void SetPosition(EntityID eid, float x, float y, float z);
    void Translate(EntityID eid, glm::vec3 pos);
    void Translate(EntityID eid, float x, float y, float z);
    void Scale(EntityID eid, glm::vec3 scl);
    void Scale(EntityID eid, float x, float y, float z);
    void SetScale(EntityID eid, glm::vec3 scl);
    void SetScale(EntityID eid, float x, float y, float z);
    void Rotate(EntityID eid, glm::vec3 rot);
    void Rotate(EntityID eid, float x, float y, float z);
    void SetRotation(EntityID eid, glm::vec3 rot);
    void SetRotation(EntityID eid, float x, float y, float z);
    void Reset(EntityID eid);
};
