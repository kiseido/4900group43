#pragma once
#include "Transform.h"
#include "Graphics.h"
#include "Board.h"
#include "Entity.h"
constexpr unsigned int MAX_ENTITY_ARRAY_SIZE = 1024;



namespace ECS
{
    unsigned int GetEntityCount();
    BoardPosition* ECS_BoardPosition[];
    ComponentID ECS_EntityComponents[];
    Transform* ECS_Transform[];
    Model* ECS_Model[];
    

    EntityID CreateEntity(Transform* t, Model* m);
    EntityID CreateEntity(ModelID m);
    EntityID CreateEntity();


    bool HasComponents(EntityID eid, ComponentID components);

    Component* GetComponent(EntityID eid, ComponentID compID);
    void SetComponent(EntityID eid, Component* component);


    Transform* GetTransform(EntityID eid);
    void SetTransform(EntityID eid, Transform* transform);

    Model* GetModel(EntityID eid);
    void SetModel(EntityID eid, Model* model);

    BoardPosition* GetBoardPosition(EntityID eid);
    void SetBoardPosition(EntityID eid, BoardPosition* boardposition);

};
