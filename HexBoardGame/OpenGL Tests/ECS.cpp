#include "ECS.h"


namespace {
    EntityID nextEntity = 0;
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



ComponentID ECS::ECS_EntityComponents[FAKE_ENTITY_SIZE_STUFF];
BoardPosition* ECS::ECS_BoardPosition[FAKE_ENTITY_SIZE_STUFF];
Transform* ECS::ECS_Transform[FAKE_ENTITY_SIZE_STUFF];
Model* ECS::ECS_Model[FAKE_ENTITY_SIZE_STUFF];


unsigned int ECS::GetEntityCount() { return nextEntity; }

EntityID ECS::CreateEntity() {
    return nextEntity++;
}

EntityID ECS::CreateEntity(ModelID m) {
    return CreateEntity(new Transform(),  Resources::GetModel(m));
}

EntityID ECS::CreateEntity(Transform* t, Model* m) {
    ECS_Transform[nextEntity] = t;
    ECS_Model[nextEntity] = m;
    return nextEntity++;
}

Component* ECS::GetComponent(EntityID eid, ComponentID compid) {
    switch (compid) {
    case ComponentBoardPosition:
        return ECS_BoardPosition[eid];
        break;
    case ComponentTransform:
        return ECS_Transform[eid];
        break;
    case ComponentModel:
        return ECS_Model[eid];
        break;
    }
}

void ECS::SetComponent(EntityID eid, Component* component) {
    switch (component->compID) {
    case ComponentBoardPosition:
        ECS_BoardPosition[eid] = (BoardPosition*)component;
        break;
    case ComponentTransform:
        ECS_Transform[eid] = (Transform*)component;
        break;
    case ComponentModel:
        ECS_Model[eid] = (Model*)component;
        break;  
    default:
        return;
    }
    ECS_EntityComponents[eid] |= component->compID;
}



Model* ECS::GetModel(EntityID eid) {
    return ECS_Model[eid];
}
void ECS::SetModel(EntityID eid, Model* model) {
    ECS_Model[eid] = model;
}

Transform* ECS::GetTransform(EntityID eid) {
    return ECS_Transform[eid];
}
void ECS::SetTransform(EntityID eid, Transform* transform) {
    ECS_Transform[eid] = transform;
}

BoardPosition* ECS::GetBoardPosition(EntityID eid) {
    return ECS_BoardPosition[eid];
}
void ECS::SetBoardPosition(EntityID eid, BoardPosition* boardposition) {
    ECS_BoardPosition[eid] = boardposition;
}