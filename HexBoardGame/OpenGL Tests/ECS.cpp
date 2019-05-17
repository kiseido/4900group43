#include "ECS.h"


namespace {
    EntityID nextEntity = 1;
    EntityID entityCount = 0;
    std::vector<EntityID> freedEntityIds;
    EntityID GetNextEntity() {
        if (freedEntityIds.size() == 0) {
            return nextEntity++;
        }
        else {
            EntityID popped{ freedEntityIds.back() };
            freedEntityIds.pop_back();
            return popped;
        }
    }
    EntityID GetEntityCount() {
        return nextEntity - freedEntityIds.size();
    }
}


ComponentID ECS::ECS_EntityComponents[MAX_ENTITY_ARRAY_SIZE];
Transform* ECS::ECS_Transform[MAX_ENTITY_ARRAY_SIZE];
Model* ECS::ECS_Model[MAX_ENTITY_ARRAY_SIZE];
BoardPosition* ECS::ECS_BoardPosition[MAX_ENTITY_ARRAY_SIZE];
BoardPiece* ECS::ECS_BoardPiece[MAX_ENTITY_ARRAY_SIZE];


unsigned int ECS::GetEntityCount() { return nextEntity; }

EntityID ECS::CreateEntity() {
    return nextEntity++;
}

EntityID ECS::CreateEntity(ModelID m) {
    return CreateEntity(new Transform(),  Resources::GetModel(m));
}

EntityID ECS::CreateEntity(Transform* t, Model* m) {
    SetTransform(nextEntity, t);
    SetModel(nextEntity, m);
    return nextEntity++;
}


void ECS::AddComponentMask(EntityID eid, ComponentID mask) {
    ECS_EntityComponents[eid] |= mask;
}


bool ECS::HasComponents(EntityID eid, ComponentID components) {
    if (eid > MAX_ENTITY_ARRAY_SIZE) return false;
    return (components & ECS_EntityComponents[eid]) == components;
}

Component* ECS::GetComponent(EntityID eid, ComponentID compid) {
    switch (compid) {
    case ComponentTransform:
        return GetTransform(eid);
        break;
    case ComponentModel:
        return GetModel(eid);
        break;
    case ComponentBoardPosition:
        return GetBoardPosition(eid);
        break;
    case ComponentBoardPiece:
        return GetBoardPiece(eid);
        break;
    }
}


void ECS::SetComponent(EntityID eid, Transform* transform) {
    SetTransform(eid, transform);
}

void ECS::SetComponent(EntityID eid, Model* model) {
    SetModel(eid, model);
}

void ECS::SetComponent(EntityID eid, BoardPosition* boardposition) {
    SetBoardPosition(eid, boardposition);
}

void ECS::SetComponent(EntityID eid, BoardPiece* boardpiece) {
    SetBoardPiece(eid, boardpiece);
}


Transform* ECS::GetTransform(EntityID eid) {
    return ECS_Transform[eid];
}
void ECS::SetTransform(EntityID eid, Transform* transform) {
    ECS_Transform[eid] = transform;
    ECS_EntityComponents[eid] |= ComponentTransform;
}


Model* ECS::GetModel(EntityID eid) {
    return ECS_Model[eid];
}
void ECS::SetModel(EntityID eid, Model* model) {
    ECS_Model[eid] = model;
    ECS_EntityComponents[eid] |= ComponentModel;
}


BoardPosition* ECS::GetBoardPosition(EntityID eid) {
    return ECS_BoardPosition[eid];
}
void ECS::SetBoardPosition(EntityID eid, BoardPosition* boardposition) {
    ECS_BoardPosition[eid] = boardposition;
    ECS_EntityComponents[eid] |= ComponentBoardPosition;
}


BoardPiece* ECS::GetBoardPiece(EntityID eid) {
    return ECS_BoardPiece[eid];
}
void ECS::SetBoardPiece(EntityID eid, BoardPiece* boardpiece) {
    ECS_BoardPiece[eid] = boardpiece;
    ECS_EntityComponents[eid] |= ComponentBoardPiece;
}