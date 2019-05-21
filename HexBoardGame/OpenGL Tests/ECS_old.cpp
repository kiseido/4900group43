#include "ECS_old.h"


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


ComponentID ECS_old::ECS_EntityComponents[MAX_ENTITY_ARRAY_SIZE];
Transform* ECS_old::ECS_Transform[MAX_ENTITY_ARRAY_SIZE];
Model ECS_old::ECS_Model[MAX_ENTITY_ARRAY_SIZE];
BoardPosition* ECS_old::ECS_BoardPosition[MAX_ENTITY_ARRAY_SIZE];
BoardPiece* ECS_old::ECS_BoardPiece[MAX_ENTITY_ARRAY_SIZE];


unsigned int ECS_old::GetEntityCount() { return nextEntity; }

EntityID ECS_old::CreateEntity() {
    return nextEntity++;
}

EntityID ECS_old::CreateEntity(ModelID m) {
    return CreateEntity(new Transform(),  Resources::GetModel(m));
}

EntityID ECS_old::CreateEntity(Transform* t, Model m) {
    SetTransform(nextEntity, t);
    SetModel(nextEntity, m);
    return nextEntity++;
}


void ECS_old::AddComponentMask(EntityID eid, ComponentID mask) {
    ECS_EntityComponents[eid] |= mask;
}


bool ECS_old::HasComponents(EntityID eid, ComponentID components) {
    if (eid > MAX_ENTITY_ARRAY_SIZE) return false;
    return (components & ECS_EntityComponents[eid]) == components;
}

Component* ECS_old::GetComponent(EntityID eid, ComponentID compid) {
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


void ECS_old::SetComponent(EntityID eid, Transform* transform) {
    SetTransform(eid, transform);
}

void ECS_old::SetComponent(EntityID eid, Model model) {
    SetModel(eid, model);
}

void ECS_old::SetComponent(EntityID eid, BoardPosition* boardposition) {
    SetBoardPosition(eid, boardposition);
}

void ECS_old::SetComponent(EntityID eid, BoardPiece* boardpiece) {
    SetBoardPiece(eid, boardpiece);
}


Transform* ECS_old::GetTransform(EntityID eid) {
    return ECS_Transform[eid];
}
void ECS_old::SetTransform(EntityID eid, Transform* transform) {
    ECS_Transform[eid] = transform;
    ECS_EntityComponents[eid] |= ComponentTransform;
}


Model* ECS_old::GetModel(EntityID eid) {
    return &ECS_Model[eid];
}
void ECS_old::SetModel(EntityID eid, Model model) {
    ECS_Model[eid] = model;
    ECS_EntityComponents[eid] |= ComponentModel;
}


BoardPosition* ECS_old::GetBoardPosition(EntityID eid) {
    return ECS_BoardPosition[eid];
}
void ECS_old::SetBoardPosition(EntityID eid, BoardPosition* boardposition) {
    ECS_BoardPosition[eid] = boardposition;
    ECS_EntityComponents[eid] |= ComponentBoardPosition;
}


BoardPiece* ECS_old::GetBoardPiece(EntityID eid) {
    return ECS_BoardPiece[eid];
}
void ECS_old::SetBoardPiece(EntityID eid, BoardPiece* boardpiece) {
    ECS_BoardPiece[eid] = boardpiece;
    ECS_EntityComponents[eid] |= ComponentBoardPiece;
}