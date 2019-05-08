#include "CompletelyFakeECS.h"


Transform* CompletelyFakeECS::ECS_Transform[FAKE_ENTITY_SIZE_STUFF];
Model* CompletelyFakeECS::ECS_Model[FAKE_ENTITY_SIZE_STUFF];

unsigned int CompletelyFakeECS::GetEntityCount() { return nextEntity; }

EntityID CompletelyFakeECS::CreateEntity(ModelID m) {
    return CreateEntity(new Transform(),  Resources::GetModel(m));
}

EntityID CompletelyFakeECS::CreateEntity(Transform* t, Model* m) {
    ECS_Transform[nextEntity] = t;
    ECS_Model[nextEntity] = m;

    return nextEntity++;
}

Model* CompletelyFakeECS::GetModel(EntityID eid) {
    return ECS_Model[eid];
}