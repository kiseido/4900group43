#pragma once

#include "Common.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>



namespace ECS {
	typedef int32_t EntityID;
	//typedef uint16_t ComponentMask;

	typedef int32_t Mask_t;
	typedef int64_t LongMask_t;

#define MASKTYPE int32_t
#define LONGMASKTYPE int64_t

	enum ComponentMask : Mask_t {
		BoardVisual = 0b1,
		BoardCollisionBody = 0b1 << 1,
		BoardPosition = 0b1 << 2,

		RealTimeVisual = 0b1 << 3,
		RealTimePosition = 0b1 << 4,
		RealTimeMomentum = 0b1 << 5,
		RealTimeRotation = 0b1 << 6,
		RotationalMomentum = 0b1 << 7,
		RealTimeCollisionBody = 0b1 << 8
	};
	enum TypeMask : Mask_t {
		BoardPieceTypeMask = 0b1,
		RealTimePieceMask = 0b1 << 1,

	};

	enum EntityTypes : Mask_t {
		BoardPieceMask = BoardVisual | BoardCollisionBody | BoardPosition,
		TeamTimePieceMask = RealTimeVisual | RealTimePosition | RealTimeMomentum | RealTimeRotation | RotationalMomentum | RealTimeCollisionBody
	};


	//union EntityMask {
	//	MaskType;
	//	struct {
	//		MaskType mask;
	//		bool hasMask(TypeMask);
	//		void addMask(TypeMask);
	//	};
	//};





	typedef glm::vec3 Position;
	typedef glm::vec3 Rotation;
	typedef glm::vec3 Momentum;

	typedef glm::vec3 CollisionBody;

	typedef int Health;

	typedef char Visual;
	typedef float TimeStamp;

	template <typename ComponentT>
	class ComponentContainer {
	private:
	public:
		std::vector<ComponentT> Components;
		std::unordered_map<EntityID, int> EntityMap;
		ComponentT* getComponent(const EntityID&);
		void setComponent(const EntityID&, const ComponentT&);
	};

	template <typename ComponentT>
	ComponentT* ComponentContainer<ComponentT>::getComponent(const EntityID& id) {
		auto index = EntityMap.find(id);

		if (index == EntityMap.end())
			return nullptr;
		else
			return &Components.at(index->second);
	}

	template <typename ComponentT>
	void ComponentContainer<ComponentT>::setComponent(const EntityID& id, const ComponentT& newElement) {

		int index = EntityMap.at(id);

		if (index == -1) {

		}
		else {

		}
	}


	struct EngineState {
		ComponentContainer<Entity> Entities;

		ComponentContainer<Health> Healths;

		ComponentContainer<Visual> BoardVisuals;
		ComponentContainer<CollisionBody> BoardCollisionBodies;
		ComponentContainer<Position> BoardPositions;

		ComponentContainer<Position> RealTimePositions;
		ComponentContainer<Momentum> Momentums;
		ComponentContainer<Rotation> Rotations;
		ComponentContainer<Momentum> RotationalMomentums;
		ComponentContainer<Visual> RealTimeVisuals;
		ComponentContainer<CollisionBody> RealTimeCollisionBodies;

		TimeStamp WorldTime;
	};

	class Entity {
		static EntityID NEXTID;

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

		//EntityMasks* masks;

		EntityID id;
	};


	class EngineState {
	private:
		std::vector<EngineState> Moments;
		int LastFinishedMoment;
	public:
		EngineState();
		EngineState& getCurrentMoment();
		const EngineState& getLastMoment() const;
		EngineState& NextMoment();
	};

	class System {
		virtual void Run(const EngineState& lastState, EngineState& newState);
	};

	class RTPhysics : System {
		static const int PerPass;
		void ProcessMomentums(const EngineState& lastState, EngineState& newState);
		void ProcessPositions(const EngineState& lastState, EngineState& newState);
		void ProcessRotations(const EngineState& lastState, EngineState& newState);
	public:
		void Run(const EngineState& lastState, EngineState& newState);
	};

	class Board {
		typedef System* WorldSystem;

		EngineState TimeLine;
		std::vector<WorldSystem> Systems;
	public:

		// generate next world state
		// @param amount of time to advance worldstate by
		TimeStamp advanceTime(TimeStamp);
		Entity NewEntity(ComponentMask);
		void setEntityType(ECS_MASKTYPE);
		void setEntityComponents(ECS_MASKTYPE);
	};



#undef ECS_MASKTYPE
}