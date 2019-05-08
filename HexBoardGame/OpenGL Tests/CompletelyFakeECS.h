#pragma once
#include "Transform.h"
#include "Graphics.h"
constexpr unsigned int FAKE_ENTITY_SIZE_STUFF = 1024;

typedef unsigned int EntityID;

namespace CompletelyFakeECS
{
    namespace {
        unsigned int nextEntity = 0;
    }
    unsigned int GetEntityCount();
    Transform* ECS_Transform[];
    Model* ECS_Model[];

    EntityID CreateEntity(Transform* t, Model* m);
    EntityID CreateEntity(ModelID m);

    Model* GetModel(EntityID eid);

};

