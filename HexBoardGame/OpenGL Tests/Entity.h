#pragma once

#include "Components.h"

namespace ECS {

	using namespace ECS::Components;

	typedef uint32_t EntityID;

	class Entity {
	public:
		static EntityID NEXTID;

		ComponentMask* componentMask;

		Health* health;
		Damage* damage;
		Power* power;

        Transform* boardTransform;
        Model* boardModel;
		BoardPosition* boardPosition;
		BoardSpeed* boardSpeed;

        Transform* combatTransform;
		Momentum* momentum;
		Momentum* rotationalMomentum;
        Model* combatModel;
		CollisionBody* combatCollisionBody;
        CombatSpeed* combatSpeed;

		TeamAffiliation* team;

		TerrainType* terrainType;

		AIStatus* ai;

		EntityID id;

	};
}