#include "Transformer.h"


glm::mat4 *Transformer::GetTransform(Transform* transf) {
    
    CalcTNet(transf); return &transf->tNet;
}



void Transformer::CalcTNet(Transform* transf) {
    
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

void Transformer::SetPosition(Transform* transf, float x, float y, float z) { SetPosition(transf, glm::vec3(x, y, z)); }
void Transformer::SetPosition(Transform* transf, glm::vec3 pos) {
    
    transf->change = true;
    transf->position = pos;
}

void Transformer::Translate(Transform* transf, float x, float y, float z) { Translate(transf, glm::vec3(x, y, z)); }
void Transformer::Translate(Transform* transf, glm::vec3 pos) {
    
    transf->change = true;
    transf->position += pos;
}

void Transformer::Scale(Transform* transf, float x, float y, float z) { Scale(transf, glm::vec3(x, y, z)); }
void Transformer::Scale(Transform* transf, glm::vec3 scl) {
    
    transf->change = true;
    transf->scale.x *= scl.x;
    transf->scale.y *= scl.y;
    transf->scale.z *= scl.z;
}

void Transformer::SetScale(Transform* transf, float x, float y, float z) { SetScale(transf, glm::vec3(x, y, z)); }
void Transformer::SetScale(Transform* transf, glm::vec3 scl) {
    
    transf->change = true;
    transf->scale = scl;
}

void Transformer::Rotate(Transform* transf, float x, float y, float z) { Rotate(transf, glm::vec3(x, y, z)); }
void Transformer::Rotate(Transform* transf, glm::vec3 rot) {
    
    transf->change = true;
    transf->rotation += rot;
}

void Transformer::SetRotation(Transform* transf, float x, float y, float z) { SetRotation(transf, glm::vec3(x, y, z)); }
void Transformer::SetRotation(Transform* transf, glm::vec3 rot) {
    
    transf->change = true;
    transf->rotation = rot;
}

void Transformer::Reset(Transform* transf) {
    
    transf->change = true;
    transf->position = glm::vec3(0.0);
    transf->scale = glm::vec3(0.0);
    transf->rotation = glm::vec3(0.0);
}