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
BoardPosition* ECS::ECS_BoardPosition[MAX_ENTITY_ARRAY_SIZE];
Transform* ECS::ECS_Transform[MAX_ENTITY_ARRAY_SIZE];
Model* ECS::ECS_Model[MAX_ENTITY_ARRAY_SIZE];


unsigned int ECS::GetEntityCount() { return nextEntity; }

EntityID ECS::CreateEntity() {
    return nextEntity++;
}

EntityID ECS::CreateEntity(ModelID m) {
    return CreateEntity(new Transform(),  Resources::GetModel(m));
}

EntityID ECS::CreateEntity(Transform* t, Model* m) {
    //ECS_Transform[nextEntity] = t;
    //ECS_Model[nextEntity] = m;
    SetComponent(nextEntity, t);
    SetComponent(nextEntity, m);
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
    if (component) {
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
}



Model* ECS::GetModel(EntityID eid) {
    return ECS_Model[eid];
}
void ECS::SetModel(EntityID eid, Model* model) {
    ECS_Model[eid] = model;
}

Transform* ECS::GetTransform(EntityID eid) {
    //return ECS_Transform[eid];
    return (Transform*)GetComponent(eid, ComponentTransform);
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