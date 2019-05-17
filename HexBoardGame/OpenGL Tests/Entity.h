#pragma once

#include "Components.h"

namespace ECS {

	using namespace ECS::Components;

	typedef int32_t EntityID;

	class Entity {
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

		EntityID id;

	};
}