#include "Transformer.h"


glm::mat4 *Transformer::GetTransform(EntityID eid) {
    Transform *transf = ECS_old::GetTransform(eid);
    CalcTNet(eid); return &transf->tNet;
}



void Transformer::CalcTNet(EntityID eid) {
    Transform *transf = ECS_old::GetTransform(eid);
    if (!transf->change) {
        return;
    }
    transf->tNet = glm::mat4(1.0);
    transf->tNet = glm::translate(transf->tNet, transf->position);
    transf->tNet = glm::rotate(transf->tNet, transf->rotation.x, glm::vec3(1.0, 0.0, 0.0));
    transf->tNet = glm::rotate(transf->tNet, transf->rotation.y, glm::vec3(0.0, 1.0, 0.0));
    transf->tNet = glm::rotate(transf->tNet, transf->rotation.z, glm::vec3(0.0, 0.0, 1.0));
    transf->tNet = glm::scale(transf->tNet, transf->scale);

    Transform *curParent = transf->parent;
    while (curParent != 0) {
        transf->tNet = transf->tNet * curParent->tNet;
        curParent = curParent->parent;
    }

    transf->change = false;
}

void Transformer::SetPosition(EntityID eid, float x, float y, float z) { SetPosition(eid, glm::vec3(x, y, z)); }
void Transformer::SetPosition(EntityID eid, glm::vec3 pos) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->position = pos;
}

void Transformer::Translate(EntityID eid, float x, float y, float z) { Translate(eid, glm::vec3(x, y, z)); }
void Transformer::Translate(EntityID eid, glm::vec3 pos) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->position += pos;
}

void Transformer::Scale(EntityID eid, float x, float y, float z) { Scale(eid, glm::vec3(x, y, z)); }
void Transformer::Scale(EntityID eid, glm::vec3 scl) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->scale.x *= scl.x;
    transf->scale.y *= scl.y;
    transf->scale.z *= scl.z;
}

void Transformer::SetScale(EntityID eid, float x, float y, float z) { SetScale(eid, glm::vec3(x, y, z)); }
void Transformer::SetScale(EntityID eid, glm::vec3 scl) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->scale = scl;
}

void Transformer::Rotate(EntityID eid, float x, float y, float z) { Rotate(eid, glm::vec3(x, y, z)); }
void Transformer::Rotate(EntityID eid, glm::vec3 rot) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->rotation += rot;
}

void Transformer::SetRotation(EntityID eid, float x, float y, float z) { SetRotation(eid, glm::vec3(x, y, z)); }
void Transformer::SetRotation(EntityID eid, glm::vec3 rot) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->rotation = rot;
}

void Transformer::Reset(EntityID eid) {
    Transform *transf = ECS_old::GetTransform(eid);
    transf->change = true;
    transf->position = glm::vec3(0.0);
    transf->scale = glm::vec3(0.0);
    transf->rotation = glm::vec3(0.0);
}