#pragma once

#include "Components.h"

namespace ECS {

	using namespace ECS::Components;

	typedef uint32_t EntityID;

	class Entity {
	public:
		static EntityID NEXTID;

		ComponentMask* componentMask;

		Visual* boardVisual;
		Position* boardPosition;
		CollisionBody* boardCollisionBody;

		Visual* realTimeVisual;
		Position* realTimePosition;
		Momentum* realTimeMomentum;
		Rotation* realTimeRotation;
		Momentum* realTimeRotationalMomentum;
		CollisionBody* realTimeCollisionBody;

		Health* health;
		Damage* damage;
		Power* power;

		BoardSpeed* boardSpeed;
		RealtimeSpeed* realTimeSpeed;

		TeamAffiliation* team;

		TerrainType* terrainType;

		AIStatus* ai;

		EntityID id;

	};
}