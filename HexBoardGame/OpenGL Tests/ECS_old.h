#pragma once
#include "Transform.h"
#include "Graphics.h"
#include "Board.h"

constexpr unsigned int MAX_ENTITY_ARRAY_SIZE = 1024;



namespace ECS_old
{
    unsigned int GetEntityCount();

    ComponentID ECS_EntityComponents[];
    Transform* ECS_Transform[];
    Model ECS_Model[];
    BoardPosition* ECS_BoardPosition[];
    BoardPiece* ECS_BoardPiece[];

    EntityID CreateEntity(Transform* t, Model m);
    EntityID CreateEntity(ModelID m);
    EntityID CreateEntity();


    bool HasComponents(EntityID eid, ComponentID components);

    void AddComponentMask(EntityID eid, ComponentID mask);
    void RemoveComponentMask(EntityID eid, ComponentID mask);

    Component* GetComponent(EntityID eid, ComponentID compID);
    void SetComponent(EntityID eid, Transform* transform);
    void SetComponent(EntityID eid, Model model);
    void SetComponent(EntityID eid, BoardPosition* boardposition);
    void SetComponent(EntityID eid, BoardPiece* boardpiece);

    Transform* GetTransform(EntityID eid);
    void SetTransform(EntityID eid, Transform* transform);

    Model* GetModel(EntityID eid);
    void SetModel(EntityID eid, Model model);

    BoardPosition* GetBoardPosition(EntityID eid);
    void SetBoardPosition(EntityID eid, BoardPosition* boardposition);

    BoardPiece* GetBoardPiece(EntityID eid);
    void SetBoardPiece(EntityID eid, BoardPiece* boardpiece);
};

